#include "EUtils.h"
#include <cmath>
#include <irr/irrKlang.h>
#include <experimental\filesystem>
#include <iostream>

float EMath::clamp_value_float(float _v, float _min, float _max)
{
	if (_v < _min) { return _min; }
	if (_v > _max) { return _max; }
	return _v;

	
}

EMath::hsv EMath::rgb2hsv(EMath::rgb in)
{
	EMath::hsv         out;
	double      min, max, delta;

	min = in.r < in.g ? in.r : in.g;
	min = min < in.b ? min : in.b;

	max = in.r > in.g ? in.r : in.g;
	max = max > in.b ? max : in.b;

	out.v = max;                                // v
	delta = max - min;
	if (delta < 0.00001)
	{
		out.s = 0;
		out.h = 0; // undefined, maybe nan?
		return out;
	}
	if (max > 0.0) { // NOTE: if Max is == 0, this divide would cause a crash
		out.s = (delta / max);                  // s
	}
	else {
		// if max is 0, then r = g = b = 0              
		// s = 0, h is undefined
		out.s = 0.0;
		out.h = NAN;                            // its now undefined
		return out;
	}
	if (in.r >= max)                           // > is bogus, just keeps compilor happy
		out.h = (in.g - in.b) / delta;        // between yellow & magenta
	else
		if (in.g >= max)
			out.h = 2.0 + (in.b - in.r) / delta;  // between cyan & yellow
		else
			out.h = 4.0 + (in.r - in.g) / delta;  // between magenta & cyan

	out.h *= 60.0;                              // degrees

	if (out.h < 0.0)
		out.h += 360.0;

	return out;
}


EMath::rgb EMath::hsv2rgb(EMath::hsv in)
{
	double      hh, p, q, t, ff;
	long        i;
	rgb         out;

	if (in.s <= 0.0) {       // < is bogus, just shuts up warnings
		out.r = in.v;
		out.g = in.v;
		out.b = in.v;
		return out;
	}

	hh = in.h;
	if (hh >= 360.0) hh = 0.0;
	hh /= 60.0;
	i = (long)hh;
	ff = hh - i;
	p = in.v * (1.0 - in.s);
	q = in.v * (1.0 - (in.s * ff));
	t = in.v * (1.0 - (in.s * (1.0 - ff)));

	switch (i) {
	case 0:
		out.r = in.v;
		out.g = t;
		out.b = p;
		break;
	case 1:
		out.r = q;
		out.g = in.v;
		out.b = p;
		break;
	case 2:
		out.r = p;
		out.g = in.v;
		out.b = t;
		break;

	case 3:
		out.r = p;
		out.g = q;
		out.b = in.v;
		break;
	case 4:
		out.r = t;
		out.g = p;
		out.b = in.v;
		break;
	case 5:
	default:
		out.r = in.v;
		out.g = p;
		out.b = q;
		break;
	}
	return out;
}

	std::vector<irrklang::ISoundSource*> ESound::default_drop_sound;
	std::vector<irrklang::ISoundSource*> ESound::custom_drop_sound;

	std::vector < std::string > ESound::default_drop_sound_name;
	std::vector < std::string > ESound::custom_drop_sound_name;


	irrklang::ISoundEngine* ESound::engine;

	std::string EString::upper_charset = "QWERTYUIOPASDFGHJKLZXCVBNM¨ÉÖÓÊÅÍÃØÙÇÕÚÔÛÂÀÏĞÎËÄÆİß×ÑÌÈÒÜÁŞ";
	std::string EString::lower_charset = "qwertyuiopasdfghjklzxcvbnm¸éöóêåíãøùçõúôûâàïğîëäæıÿ÷ñìèòüáş";

	std::string EString::path_to_poe_folder;

	std::vector<BaseClass*> EString::base_class_list;
	std::vector<ProphecyList*> EString::prophecy_list;

	std::vector<std::string> EString::loot_filter_name_list;
	std::vector<std::string> EString::loot_filter_path_list;

	std::string EString::to_lower(std::string _s, bool _b)
	{
		std::string result = "";

		for (int zz = 0; zz < _s.length(); zz++)
		{
			for (int yy = 0; yy < upper_charset.length(); yy++)
			{
				//if (_b) { std::cout << upper_charset.at(yy) << "(" << _s.at(zz) << ") "; }

				if (upper_charset.at(yy) == _s.at(zz))
				{
					result += lower_charset.at(yy);
					break;
				}
				else
				{
					if (yy + 1 >= upper_charset.length())
					{
						result += _s.at(zz);
					}
				}
			}
		}

		return result;
	}

	void EString::load_loot_filter_list()
	{
		for (auto& p : std::experimental::filesystem::directory_iterator(EString::path_to_poe_folder))
		{
			std::string loot_filter_name = p.path().u8string();
			//writer << custom_sound << endl;;

			if
				(
					(loot_filter_name.length()>=8)
					&&
					(EString::to_lower(loot_filter_name.substr(loot_filter_name.length() - 7, 7), false) == ".filter")
				)
			{

				//cout <<"It sound!" << '\n'<<'\n';

				EString::loot_filter_path_list.push_back(loot_filter_name);
				EString::loot_filter_name_list.push_back(p.path().filename().u8string().substr(0, p.path().filename().u8string().length() - 7));

				std::cout << "It filter! " << p.path().filename().u8string() << '\n' << '\n';

				//ESound::custom_drop_sound.push_back(ESound::engine->addSoundSourceFromFile(custom_sound.c_str()));
			}
		}
	}

	void ESound::load_custom_sound()
	{
		ESound::custom_drop_sound		.clear();
		ESound::custom_drop_sound_name	.clear();
		//s 17:41:35 31.07.2019
		ESound::custom_drop_sound_name.push_back("NONE");
		ESound::custom_drop_sound.push_back(NULL);

		for (auto& p : std::experimental::filesystem::directory_iterator(EString::path_to_poe_folder))
		{
			std::cout << p.path() << '\n';

			std::string custom_sound = p.path().u8string();
			//writer << custom_sound << endl;;

			if
				(
				(EString::to_lower(custom_sound.substr(custom_sound.length() - 4, 4), false) == ".wav")
					||
					(EString::to_lower(custom_sound.substr(custom_sound.length() - 4, 4), false) == ".mp3")
					)
			{

				//cout <<"It sound!" << '\n'<<'\n';

				ESound::custom_drop_sound_name.push_back(p.path().filename().u8string());
				std::cout << "It sound! " << p.path().filename().u8string() << '\n' << '\n';

				ESound::custom_drop_sound.push_back(ESound::engine->addSoundSourceFromFile(custom_sound.c_str()));
			}
		}
	}

	irrklang::ISoundSource* ESound::get_sound_by_name(std::string _name)
	{
		int sound_id=0;

		for (std::string s : custom_drop_sound_name)
		{
			if (s==_name)
			{
				return custom_drop_sound.at(sound_id);
			}

			sound_id++;
		}

		return custom_drop_sound.at(0);
	}
