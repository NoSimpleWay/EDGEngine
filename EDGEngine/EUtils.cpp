#pragma once
#include "EUtils.h"
#include <cmath>
#include <irr/irrKlang.h>

#define _SILENCE_EXPERIMENTAL_FILESYSTEM_DEPRECATION_WARNING
#include <experimental\filesystem>
#include <iostream>
#include <fstream>
#include "FilterBlock.h"
#include "ConsoleColor.h"
#include "StaticData.h"
#include "EButtonFilterItem.h"

using namespace std;

float EMath::clamp_value_float(float _v, float _min, float _max)
{
	if (_v < _min) { return _min; }
	if (_v > _max) { return _max; }
	return _v;

	
}

float EMath::clamp_value_int(int _v, int _min, int _max)
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

	irrklang::ISoundSource* ESound::flip_sound;

	std::vector < std::string > ESound::default_drop_sound_name;
	std::vector < std::string > ESound::default_drop_sound_original_name;

	std::vector < std::string > ESound::custom_drop_sound_name;


	irrklang::ISoundEngine* ESound::engine;

	std::string EString::upper_charset = "QWERTYUIOPASDFGHJKLZXCVBNM®…÷” ≈Õ√ÿŸ«’⁄‘€¬¿œ–ŒÀƒ∆›ﬂ◊—Ã»“‹¡ﬁ";
	std::string EString::lower_charset = "qwertyuiopasdfghjklzxcvbnm∏ÈˆÛÍÂÌ„¯˘Áı˙Ù˚‚‡ÔÓÎ‰Ê˝ˇ˜ÒÏËÚ¸·˛";

	std::string EString::path_to_poe_folder;

	Enums::LocalisationList EString::active_localisation = Enums::LocalisationList::EN;

	std::vector<BaseClass*> EString::base_class_list;
	std::vector<LabEnchantment*> EString::enchantment_list;
	std::vector<ProphecyList*> EString::prophecy_list;

	std::vector<std::string> EString::loot_filter_name_list;
	std::vector<std::string> EString::loot_simulator_pattern_name_list;

	std::vector<std::string> EString::loot_filter_path_list;
	std::vector<std::string> EString::loot_simulator_pattern_path_list;

	std::vector <std::string> EString::path_list;

	std::string EString::opened_loot_filter_name;
	std::string EString::opened_loot_filter_path;

	std::vector<std::string> EString::localisation_key;
	std::vector<std::string> EString::localisation_text;

	std::vector <std::string> EString::notable_passives_name;
	std::vector <std::string> EString::notable_passives_description;

	std::vector <std::string> EString::notable_passives_ru_name;
	std::vector <std::string> EString::notable_passives_ru_description;

	std::vector <NotablePassive*> EString::notable_list;

	std::vector <std::string> EString::oil_name_list =
	{
		"oil_name_clear",
		"oil_name_sepia",
		"oil_name_amber",
		"oil_name_verdant",
		"oil_name_teal",
		"oil_name_azure",
		"oil_name_violet",
		"oil_name_crimson",
		"oil_name_black",
		"oil_name_opalescent",
		"oil_name_silver",
		"oil_name_golden"
	};

	std::vector <std::string> EString::loot_pattern_name;
	std::vector <std::string> EString::loot_pattern_name_ru;

	std::vector <std::string> EString::loot_pattern_description;
	std::vector <std::string> EString::loot_pattern_description_ru;

	std::vector <std::string> EString::loot_pattern_path;

	std::string EString::game_color_name[6]
	=
	{
		"Red",
		"Green",
		"Blue",
		"Brown",
		"White",
		"Yellow"
	}
	;

	void EString::load_localisation(std::string _text)
	{
		EString::localisation_key.clear();
		EString::localisation_text.clear();

		//ofstream myfile_open;
		//myfile_open.open("gemor.txt");

		ifstream myfile;
		myfile.open("data/localisation/" + _text + ".txt");
		string line;

		string subdata;
		string subdata_array[4];

		int line_id = 0;
		int data_order;


		//cout << EMath::rgb::r << endl;


		while ((getline(myfile, line)) && (line_id < 1000))
		{

			data_order = 0;
			subdata = "";

			for (int i = 0; i < line.length(); i++)
			{


				if (line.at(i) != '\t')
				{
					subdata += line.at(i);
				}

				if ((line.at(i) == '\t') || (i + 1 >= line.length()))
				{
					subdata_array[data_order] = subdata;
					subdata = "";
					data_order++;
				}

			}


			localisation_key.push_back(subdata_array[0]);

			localisation_text.push_back(to_cyrillic(subdata_array[1]));

			//std::cout << "KEY (" << subdata_array[0] << ")   VALUE (" << subdata_array[1] << std::endl;

			line_id++;
		}

		int wtf = 0;
		for (BaseClass* b : base_class_list)
		{
			//cout << "[" << wtf << "] base class name: " << b->base_name << " ru name: " << b->ru_name << endl;
			wtf++;
		}
	}

	void EString::load_loot_pattern_list(std::string _text)
	{
		EString::loot_pattern_description.clear();
		EString::loot_pattern_description_ru.clear();

		EString::loot_pattern_name.clear();
		EString::loot_pattern_name_ru.clear();

		EString::loot_pattern_path.clear();



		//ofstream myfile_open;
		//myfile_open.open("gemor.txt");

		ifstream myfile;
		myfile.open("data/loot simulator/pattern/" + _text + ".txt");
		string line;

		string subdata;
		string subdata_array[14];

		int line_id = 0;
		int data_order;


		//cout << EMath::rgb::r << endl;


		while ((getline(myfile, line)) && (line_id < 1000))
		{

			data_order = 0;
			subdata = "";

			for (int i = 0; i < line.length(); i++)
			{


				if (line.at(i) != '\t')
				{
					subdata += line.at(i);
				}

				if ((line.at(i) == '\t') || (i + 1 >= line.length()))
				{
					subdata_array[data_order] = subdata;
					subdata = "";
					data_order++;
				}

			}

			for (int i = 0; i < 6; i++)
			{
				if (subdata_array[i * 2] == "name_en")
				{EString::loot_pattern_name.push_back(subdata_array[i * 2 + 1]);}

				if (subdata_array[i * 2] == "name_ru")
				{EString::loot_pattern_name_ru.push_back(EString::to_cyrillic(subdata_array[i * 2 + 1]));}

				if (subdata_array[i * 2] == "description_en")
				{EString::loot_pattern_description.push_back(subdata_array[i * 2 + 1]);}

				if (subdata_array[i * 2] == "description_ru")
				{EString::loot_pattern_description_ru.push_back(EString::to_cyrillic(subdata_array[i * 2 + 1]));}

				if (subdata_array[i * 2] == "path")
				{EString::loot_pattern_path.push_back(subdata_array[i * 2 + 1]);}
			}

			//std::cout << "KEY (" << subdata_array[0] << ")   VALUE (" << subdata_array[1] << std::endl;

			line_id++;
		}

		int wtf = 0;
		for (BaseClass* b : base_class_list)
		{
			//cout << "[" << wtf << "] base class name: " << b->base_name << " ru name: " << b->ru_name << endl;
			wtf++;
		}
	}

	void EString::load_loot_pattern(std::string _text)
	{
		//StaticData::window_loot_simulator->pattern_item_list
		StaticData::window_loot_simulator->pattern_item_list.clear();

		LootPatternItem* just_created_pattern_item;

		//ofstream myfile_open;
		//myfile_open.open("gemor.txt");

		ifstream myfile;
		myfile.open("data/loot simulator/pattern/" + _text + ".pattern");
		string line;

		string subdata;
		string subdata_array[50];

		int line_id = 0;
		int data_order;


		//cout << EMath::rgb::r << endl;


		while ((getline(myfile, line)) && (line_id < 1000))
		{
			just_created_pattern_item = new LootPatternItem();
			StaticData::window_loot_simulator->pattern_item_list.push_back(just_created_pattern_item);

			//std::cout << "LOOT pattern element push!" << std::endl;

			data_order = 0;
			subdata = "";

			for (int i=0; i<50; i++)
			{
				subdata_array[i] = "";
			}

			for (int i = 0; i < line.length(); i++)
			{
				if (line.at(i) != '\t')
				{
					subdata += line.at(i);
				}

				if ((line.at(i) == '\t') || (i + 1 >= line.length()))
				{
					subdata_array[data_order] = subdata;
					subdata = "";
					data_order++;
				}
			}

			for (int i = 0; i < 24; i++)
			{
				if (EString::to_lower(subdata_array[i * 2], false) == "item_name")
				{
					just_created_pattern_item->item_name = EString::to_cyrillic(subdata_array[i * 2 + 1]);
				}


				if (EString::to_lower(subdata_array[i * 2], false) == "class")
				{
					just_created_pattern_item->base_class = EString::to_cyrillic(subdata_array[i * 2 + 1]);
				}


				if (EString::to_lower(subdata_array[i * 2], false) == "legacy")
				{
					just_created_pattern_item->is_legacy = true;
				}


				if (EString::to_lower(subdata_array[i * 2], false) == "quality_min")
				{
					just_created_pattern_item->min_quality = std::stoi(subdata_array[i * 2 + 1]);
				}


				if (EString::to_lower(subdata_array[i * 2], false) == "quality_max")
				{
					just_created_pattern_item->max_quality = std::stoi(subdata_array[i * 2 + 1]);
				}


				if (EString::to_lower(subdata_array[i * 2], false) == "gem_level_min")
				{
					just_created_pattern_item->min_gem_level = std::stoi(subdata_array[i * 2 + 1]);
				}


				if (EString::to_lower(subdata_array[i * 2], false) == "gem_level_max")
				{
					just_created_pattern_item->max_gem_level = std::stoi(subdata_array[i * 2 + 1]);
				}

				if (EString::to_lower(subdata_array[i * 2], false) == "item_level_min")
				{
					
					just_created_pattern_item->min_item_level = std::stoi(subdata_array[i * 2 + 1]);

					//std::cout << "min item level=" << just_created_pattern_item->min_item_level << std::endl;
				}


				if (EString::to_lower(subdata_array[i * 2], false) == "item_level_max")
				{
					just_created_pattern_item->max_item_level = std::stoi(subdata_array[i * 2 + 1]);

					//std::cout << "max item level=" << just_created_pattern_item->max_item_level << std::endl;
				}


				if (EString::to_lower(subdata_array[i * 2], false) == "links_min")
				{
					just_created_pattern_item->min_links = std::stoi(subdata_array[i * 2 + 1]);
				}


				if (EString::to_lower(subdata_array[i * 2], false) == "links_max")
				{
					just_created_pattern_item->max_links = std::stoi(subdata_array[i * 2 + 1]);
				}

				if (EString::to_lower(subdata_array[i * 2], false) == "map_tier_min")
				{
					just_created_pattern_item->min_map_tier = std::stoi(subdata_array[i * 2 + 1]);
				}


				if (EString::to_lower(subdata_array[i * 2], false) == "map_tier_max")
				{
					just_created_pattern_item->max_map_tier = std::stoi(subdata_array[i * 2 + 1]);
				}


				if (EString::to_lower(subdata_array[i * 2], false) == "red_sockets_weight")
				{
					just_created_pattern_item->red_weight = std::stoi(subdata_array[i * 2 + 1]);
				}


				if (EString::to_lower(subdata_array[i * 2], false) == "green_sockets_weight")
				{
					just_created_pattern_item->green_weight = std::stoi(subdata_array[i * 2 + 1]);
				}


				if (EString::to_lower(subdata_array[i * 2], false) == "blue_sockets_weight")
				{
					just_created_pattern_item->blue_weight = std::stoi(subdata_array[i * 2 + 1]);
				}


				if (EString::to_lower(subdata_array[i * 2], false) == "white_sockets_weight")
				{
					just_created_pattern_item->white_weight = std::stoi(subdata_array[i * 2 + 1]);
				}


				if (EString::to_lower(subdata_array[i * 2], false) == "corruption_chance")
				{
					just_created_pattern_item->corruption_chance = std::stoi(subdata_array[i * 2 + 1]);
				}


				if (EString::to_lower(subdata_array[i * 2], false) == "shaper_item_weight")
				{
					just_created_pattern_item->shaper_item_weight = std::stoi(subdata_array[i * 2 + 1]);
				}


				if (EString::to_lower(subdata_array[i * 2], false) == "elder_item_weight")
				{
					just_created_pattern_item->elder_item_weight = std::stoi(subdata_array[i * 2 + 1]);
				}


				if (EString::to_lower(subdata_array[i * 2], false) == "normal_item_weight")
				{
					just_created_pattern_item->normal_item_weight = std::stoi(subdata_array[i * 2 + 1]);
				}


				if (EString::to_lower(subdata_array[i * 2], false) == "sockets_min")
				{
					just_created_pattern_item->min_sockets = std::stoi(subdata_array[i * 2 + 1]);
				}


				if (EString::to_lower(subdata_array[i * 2], false) == "sockets_max")
				{
					just_created_pattern_item->max_sockets = std::stoi(subdata_array[i * 2 + 1]);

					cout << "max sockets [" << just_created_pattern_item->random_class << "] = " << just_created_pattern_item->max_sockets << " data (" << subdata_array[i * 2 + 1] << ")" << endl;
					
				}

				if (EString::to_lower(subdata_array[i * 2], false) == "count")
				{
					just_created_pattern_item->count = std::stoi(subdata_array[i * 2 + 1]);
				}

				if (EString::to_lower(subdata_array[i * 2], false) == "random_class")
				{
					just_created_pattern_item->random_class = subdata_array[i * 2 + 1];
				}

				if (EString::to_lower(subdata_array[i * 2], false) == "random_subclass")
				{
					just_created_pattern_item->random_subclass = subdata_array[i * 2 + 1];
				}

				if (EString::to_lower(subdata_array[i * 2], false) == "shaped_map")
				{
					just_created_pattern_item->shaped_map = true;
				}

				if (EString::to_lower(subdata_array[i * 2], false) == "elder_map")
				{
					just_created_pattern_item->elder_map = true;
				}
				if (EString::to_lower(subdata_array[i * 2], false) == "blighted_map")
				{
					just_created_pattern_item->blighted_map = true;
				}

				if (EString::to_lower(subdata_array[i * 2], false) == "random_category")
				{
					just_created_pattern_item->random_category = subdata_array[i * 2 + 1];
				}

				if (EString::to_lower(subdata_array[i * 2], false) == "random_cost_group")
				{
					just_created_pattern_item->random_cost_group = subdata_array[i * 2 + 1];
				}

				if (EString::to_lower(subdata_array[i * 2], false) == "prophecy_name")
				{
					just_created_pattern_item->prophecy_name = subdata_array[i * 2 + 1];
				}

				if (EString::to_lower(subdata_array[i * 2], false) == "base_class")
				{
					just_created_pattern_item->base_class = subdata_array[i * 2 + 1];
				}

				if (EString::to_lower(subdata_array[i * 2], false) == "enchantment")
				{
					just_created_pattern_item->enchantment = subdata_array[i * 2 + 1];
				}

				if (EString::to_lower(subdata_array[i * 2], false) == "explicit")
				{
					just_created_pattern_item->explicit_list.push_back(subdata_array[i * 2 + 1]);
				}

				if (EString::to_lower(subdata_array[i * 2], false) == "rarity_min")
				{
					if (subdata_array[i * 2 + 1] == EString::to_lower("normal", false)) { just_created_pattern_item->min_rarity = 0; }
					if (subdata_array[i * 2 + 1] == EString::to_lower("magic", false)) { just_created_pattern_item->min_rarity = 1; }
					if (subdata_array[i * 2 + 1] == EString::to_lower("rare", false)) { just_created_pattern_item->min_rarity = 2; }
					if (subdata_array[i * 2 + 1] == EString::to_lower("unique", false)) { just_created_pattern_item->min_rarity = 3; }
				}


				if (EString::to_lower(subdata_array[i * 2], false) == "rarity_max")
				{
					if (subdata_array[i * 2 + 1] == EString::to_lower("normal", false)) { just_created_pattern_item->max_rarity = 0; }
					if (subdata_array[i * 2 + 1] == EString::to_lower("magic", false)) { just_created_pattern_item->max_rarity = 1; }
					if (subdata_array[i * 2 + 1] == EString::to_lower("rare", false)) { just_created_pattern_item->max_rarity = 2; }
					if (subdata_array[i * 2 + 1] == EString::to_lower("unique", false)) { just_created_pattern_item->max_rarity = 3; }
				}
			}
			

			line_id++;
		}
	}

	bool EString::font_is_configued = false;
	bool EString::localisation_is_configued = false;

	std::string EString::icon_shape_name[6]
	=
	{
		"Circle",
		"Diamond",
		"Hexagon",
		"Square",
		"Star",
		"Triangle"
	}
	;

	/*
	std::string EString::compare_strings(std::string _s1, std::string _s2)
	{

	}
	*/

	std::string EString::to_lower(std::string _s)
	{
		return to_lower(_s, false);
	}

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

	void EString::load_loot_simulator_pattern_list()
	{
		EString::loot_simulator_pattern_name_list.clear();
		EString::loot_simulator_pattern_path_list.clear();

		for (auto& p : std::experimental::filesystem::directory_iterator("data/loot simulator/pattern/"))
		{
			std::string loot_filter_name = p.path().u8string();
			//writer << custom_sound << endl;;

			cout << "file: " << loot_filter_name << endl;

			if
			(
				(loot_filter_name.length() >= 9)
				&&
				(EString::to_lower(loot_filter_name.substr(loot_filter_name.length() - 8, 8), false) == ".pattern")
			)
			{

				//cout <<"It sound!" << '\n'<<'\n';

				EString::loot_simulator_pattern_path_list.push_back(to_cyrillic(loot_filter_name));
				EString::loot_simulator_pattern_name_list.push_back(to_cyrillic(p.path().filename().u8string().substr(0, p.path().filename().u8string().length() - 8)));

				//std::cout << "It filter! " << p.path().filename().u8string() << '\n' << '\n';

				//ESound::custom_drop_sound.push_back(ESound::engine->addSoundSourceFromFile(custom_sound.c_str()));
			}
		}
	}

	void EString::load_loot_filter_list()
	{
		EString::loot_filter_path_list.clear();
		EString::loot_filter_name_list.clear();
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

				EString::loot_filter_path_list.push_back(to_cyrillic(loot_filter_name));
				EString::loot_filter_name_list.push_back(to_cyrillic(p.path().filename().u8string().substr(0, p.path().filename().u8string().length() - 7)));

				//std::cout << "It filter! " << p.path().filename().u8string() << '\n' << '\n';

				//ESound::custom_drop_sound.push_back(ESound::engine->addSoundSourceFromFile(custom_sound.c_str()));
			}
		}
	}

	void ESound::load_custom_sound()
	{
		for (irrklang::ISoundSource* sound : ESound::custom_drop_sound)
		{
			ESound::engine->removeSoundSource(sound);
		}

		ESound::custom_drop_sound		.clear();
		ESound::custom_drop_sound_name	.clear();
		//s 17:41:35 31.07.2019
		ESound::custom_drop_sound_name.push_back("NONE");
		ESound::custom_drop_sound.push_back(NULL);

		for (auto& p : std::experimental::filesystem::directory_iterator(EString::path_to_poe_folder))
		{
			//std::cout << p.path() << '\n';

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

				ESound::custom_drop_sound_name.push_back(EString::to_cyrillic(p.path().filename().u8string()));
				//std::cout << "It sound! " << p.path().filename().u8string() << '\n' << '\n';

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

		return ESound::flip_sound;
		//return custom_drop_sound.at(0);
	}

	bool EString::convert_text_to_bool(std::string _text)
	{
		if (_text == "True")
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	bool EString::check_is_condition_symbols(std::string _s)
	{
		if
			(
			(_s == "<=") ||
				(_s == "<") ||
				(_s == "=") ||
				(_s == ">") ||
				(_s == ">=")
				)
		{
			return true;
		}

		return false;
	}

	int EString::find_item_by_full_name(string _name)
	{

		for (int i = 0; i < ItemList::item_list.size(); i++)
		{
			if (ItemList::item_list.at(i)->item_name == _name) { return i; }
		}

		return -1;
	}

	std::string EString::localize_it(std::string _text)
	{
		int vector_id = 0;

		for (std::string s : localisation_key)
		{
			if (_text == s) { return localisation_text.at(vector_id); }

			vector_id++;
		}

		return _text;
	}

	std::string EString::to_cyrillic(std::string _text)
	{
		char sInvalid[1024];
		strcpy_s(sInvalid, _text.c_str());
		//ÍÓÏÏÂÌÚ‡ËË

		int size = strlen(sInvalid) + 1;
		wchar_t* wsValid = new wchar_t[size];
		char* sValid = new char[size];

		MultiByteToWideChar(CP_UTF8, 0, sInvalid, -1, wsValid, size);
		WideCharToMultiByte(CP_ACP, NULL, wsValid, -1, sValid, size, NULL, NULL);

		return sValid;
	}

	void EString::save_config()
	{
		ofstream writer;
		writer.open("config.txt");

		writer << EFont::active_font->name << std::endl;

		if (EString::active_localisation == Enums::LocalisationList::EN)
		{ writer << "EN" << std::endl; }
		
		if (EString::active_localisation == Enums::LocalisationList::RU)
		{ writer << "RU" << std::endl; }

		writer.close();
		//button_list.push_back(new EButton());
	}

	void EString::load_config()
	{
		ifstream reader;
		reader.open("config.txt");

		if (reader.is_open())
		{
			string line;
			getline(reader, line);

			for (EFont* f : EFont::font_list)
			{
				if (f->name == line)
				{
					EFont::active_font = f;

					font_is_configued = true;
				}
			}

			getline(reader, line);
			cout << "Reader localisation: " << line << endl;

			if (line == "EN") {	EString::active_localisation = Enums::LocalisationList::EN;	localisation_is_configued = true; EString::load_localisation("EN"); }
			if (line == "RU") {	EString::active_localisation = Enums::LocalisationList::RU;	localisation_is_configued = true; EString::load_localisation("RU"); }



			reader.close();
		}
		//button_list.push_back(new EButton());
	}

	void EFile::parse_loot_filter_data(std::string _path)
	{

		//StaticData::window_filter_block->unsave_change = false;

		for (FilterBlock* fb : StaticData::window_filter_block->filter_block_list)
		{
			delete fb;
		}

		StaticData::window_filter_block->filter_block_list.clear();

		for (FilterBlockSeparator* sep : StaticData::window_filter_block->separator_list)
		{
			sep->link_to_caption_text->need_remove = true;
			sep->link_to_collapse->need_remove = true;
			sep->link_to_remove->need_remove = true;
		}
		StaticData::window_filter_block->separator_list.clear();

		ifstream myfile;
		myfile.open(_path);
		cout << "open: " << _path << endl;




		string line;
		int line_number = 0;
		int data_order = 0;

		Enums::ParserMode parser_mode = Enums::ParserMode::NOTHING;

		cout << endl << endl << endl;

		FilterBlock* just_created_block = new FilterBlock();
		FilterBlockSeparator* just_created_separator = NULL;

		int error_counts = 0;
		bool show_info_to_console = false;

		

		EButton* just_created_button = NULL;

		int explicit_group_id = -1;

		while ((getline(myfile, line)) && (line_number < 10000))
		{
			bool is_base_type_equal_mode = false;
			//std::cout << "array is " << sizeof(condition_names)  << " length" << std::endl;

			bool comment_mode = false;
			string subdata = "";
			data_order = 0;
			parser_mode = Enums::ParserMode::NOTHING;



			bool space_is_not_separator = false;


			if (show_info_to_console)
			{
				cout << "#################" << endl;
				cout << green << "___what readed: '" << blue << line << "'" << white << endl;
				cout << "#################" << endl << endl;
			}

			for (int i = 0; i < line.length(); i++)
			{
				if (line.at(i) == '"') { space_is_not_separator = !space_is_not_separator; }
				if (line.at(i) == '#')
				{
					comment_mode = true;
					//cout << "comment mode activate, now i dont parse data by normal way" << endl;
					parser_mode = Enums::ParserMode::NOTHING;

					subdata = "";
				}

				if (((line.at(i) != ' ') || (space_is_not_separator)) && (line.at(i) != '\t') && (line.at(i) != '"'))
				{
					subdata += line.at(i);
				}

				if
					(
						((line.at(i) == ' ') && (!space_is_not_separator)) || (line.at(i) == '\t') || (i + 1 >= line.length())
					)
				{

					if (subdata.length() > 0)
					{
						//if ((i >= line.length())&&(line.at(i)!=' ')) { subdata += line.at(i); }

						if (show_info_to_console) cout << "--- subdata:'" << subdata << "'" << endl;


						if (parser_mode == Enums::ParserMode::NOTHING)
						{
							if (!comment_mode)
							{
								/*for (EButtonDropCondition* b : base_filter_condition_list)
								{
									b->incoming_data(this);
								}*/

								if (subdata == "Show")
								{
									just_created_block = new FilterBlock();
									StaticData::window_filter_block->filter_block_list.push_back(just_created_block);
									parser_mode = Enums::ParserMode::SHOW;
									if (show_info_to_console) { cout << "And new block is created! And block is SHOWED!" << endl; }

									just_created_block->is_show = true;

									explicit_group_id = -1;
								}

								if (subdata == "Hide")
								{
									just_created_block = new FilterBlock();
									StaticData::window_filter_block->filter_block_list.push_back(just_created_block);
									parser_mode = Enums::ParserMode::HIDE;
									if (show_info_to_console) { cout << "And new block is created! And block is HIDED!" << endl; }

									just_created_block->is_show = false;

									explicit_group_id = -1;
								}

								if (subdata == "Corrupted") { parser_mode = Enums::ParserMode::IS_CORRUPTED; just_created_block->base_filter_data_active.at(Enums::BaseDataOrder::DATA_CORRUPTED) = true; }
								if (subdata == "LinkedSockets") { parser_mode = Enums::ParserMode::LINKED_SOCKETS; just_created_block->base_filter_data_active.at(Enums::BaseDataOrder::DATA_LINKS) = true; }
								if (subdata == "Rarity") { parser_mode = Enums::ParserMode::RARITY; just_created_block->base_filter_data_active.at(Enums::BaseDataOrder::DATA_RARITY) = true; }
								if (subdata == "Class")
								{
									//std::cout << "Try get acess to remove button" << std::endl;

									parser_mode = Enums::ParserMode::CLASS;
									just_created_block->is_base_class_active = true;
									just_created_block->plus_class_button_link->is_active = true;
									just_created_block->remove_base_class_button->is_active = true;
								}

								if (subdata == "HasEnchantment")
								{
									//std::cout << "Try get acess to remove button" << std::endl;

									parser_mode = Enums::ParserMode::HAS_ENCHANTMENT;

									just_created_block->is_enchantment_active = true;
									just_created_block->plus_enchantment_button_link->is_active = true;
									just_created_block->remove_enchantment_button->is_active = true;
								}

								if (subdata == "SetFontSize") { parser_mode = Enums::ParserMode::FONT_SIZE; just_created_block->is_font_size_active = true; }
								if (subdata == "SetTextColor") { parser_mode = Enums::ParserMode::TEXT_COLOR; just_created_block->is_text_color_active = true; }
								if (subdata == "SetBorderColor") { parser_mode = Enums::ParserMode::BORDER_COLOR; just_created_block->is_rama_color_active = true; }
								if (subdata == "SetBackgroundColor") { parser_mode = Enums::ParserMode::BACKGROUND_COLOR; just_created_block->is_bg_color_active = true; }

								if (subdata == "PlayAlertSound") { parser_mode = Enums::ParserMode::ALERT_SOUND; just_created_block->is_alert_sound = true; just_created_block->is_positional_sound = false; }
								if (subdata == "PlayAlertSoundPositional") { parser_mode = Enums::ParserMode::ALERT_SOUND; just_created_block->is_alert_sound = true;  just_created_block->is_positional_sound = true;}

								if (subdata == "CustomAlertSound") { parser_mode = Enums::ParserMode::CUSTOM_ALERT_SOUND; just_created_block->is_custom_alert_sound = true; }
								if (subdata == "PlayEffect") { parser_mode = Enums::ParserMode::RAY; just_created_block->is_ray = true; just_created_block->ray_is_temp = false; }
								if (subdata == "MinimapIcon") { parser_mode = Enums::ParserMode::MINIMAP_ICON; just_created_block->is_minimap_icon = true; }

								if (subdata == "BaseType") { parser_mode = Enums::ParserMode::BASETYPE; }

								if (subdata == "ShaperItem") { parser_mode = Enums::ParserMode::IS_SHAPER_ITEM; just_created_block->base_filter_data_active.at(Enums::BaseDataOrder::DATA_SHAPER_ITEM) = true; }
								if (subdata == "ItemLevel") { parser_mode = Enums::ParserMode::ITEM_LEVEL; just_created_block->base_filter_data_active.at(Enums::BaseDataOrder::DATA_ITEM_LEVEL) = true; }
								if (subdata == "HasExplicitMod") { parser_mode = Enums::ParserMode::EXPLICIT_MOD; explicit_group_id++;  just_created_block->is_explicit = true; }
								if (subdata == "Identified") { parser_mode = Enums::ParserMode::IDENTIFIED; just_created_block->is_identified_active = true; }
								if (subdata == "ElderItem") { parser_mode = Enums::ParserMode::IS_ELDER_ITEM; just_created_block->base_filter_data_active.at(Enums::BaseDataOrder::DATA_ELDER_ITEM) = true; }
								if (subdata == "Sockets") { parser_mode = Enums::ParserMode::SOCKETS; just_created_block->base_filter_data_active.at(Enums::BaseDataOrder::DATA_SOCKETS) = true; }
								if (subdata == "FracturedItem") { parser_mode = Enums::ParserMode::IS_FRACTURED_ITEM; just_created_block->base_filter_data_active.at(Enums::BaseDataOrder::DATA_FRACTURED) = true; }
								if (subdata == "DropLevel") { parser_mode = Enums::ParserMode::DROP_LEVEL; just_created_block->base_filter_data_active.at(Enums::BaseDataOrder::DATA_REQUIRED_LEVEL) = true; }

								if (subdata == "Width") { parser_mode = Enums::ParserMode::WIDTH; just_created_block->base_filter_data_active.at(Enums::BaseDataOrder::DATA_WIDTH) = true; }
								if (subdata == "Height") { parser_mode = Enums::ParserMode::HEIGHT; just_created_block->base_filter_data_active.at(Enums::BaseDataOrder::DATA_HEIGHT) = true; }

								if (subdata == "SynthesisedItem") { parser_mode = Enums::ParserMode::IS_SYNTHESISED_ITEM; just_created_block->base_filter_data_active.at(Enums::BaseDataOrder::DATA_SYNTHESISED) = true; }
								if (subdata == "AnyEnchantment") { parser_mode = Enums::ParserMode::IS_ANY_ENCHANTMENT; just_created_block->base_filter_data_active.at(Enums::BaseDataOrder::DATA_ENCHANTMENT) = true; }

								if (subdata == "Quality") { parser_mode = Enums::ParserMode::QUALITY; just_created_block->base_filter_data_active.at(Enums::BaseDataOrder::DATA_QUALITY) = true; }
								if (subdata == "SocketGroup") { parser_mode = Enums::ParserMode::SOCKET_GROUP; just_created_block->base_filter_data_active.at(Enums::BaseDataOrder::DATA_SOCKET_GROUP) = true; }
								if (subdata == "StackSize") { parser_mode = Enums::ParserMode::STACK_SIZE; just_created_block->base_filter_data_active.at(Enums::BaseDataOrder::DATA_STACK_SIZE) = true; }
								if (subdata == "GemLevel") { parser_mode = Enums::ParserMode::GEM_LEVEL; just_created_block->base_filter_data_active.at(Enums::BaseDataOrder::DATA_GEM_LEVEL) = true; }

								if (subdata == "ElderMap") { parser_mode = Enums::ParserMode::IS_ELDER_MAP; just_created_block->base_filter_data_active.at(Enums::BaseDataOrder::DATA_ELDER_MAP) = true; }
								if (subdata == "ShapedMap") { parser_mode = Enums::ParserMode::IS_SHAPER_MAP; just_created_block->base_filter_data_active.at(Enums::BaseDataOrder::DATA_SHAPER_MAP) = true; }
								if (subdata == "MapTier") { parser_mode = Enums::ParserMode::MAP_TIER; just_created_block->base_filter_data_active.at(Enums::BaseDataOrder::DATA_MAP_TIER) = true; }

								if (subdata == "DisableDropSound") { parser_mode = Enums::ParserMode::DISABLE_DROP_SOUND; just_created_block->disable_drop_sound = true; }
								if (subdata == "Prophecy")
								{
									parser_mode = Enums::ParserMode::PROPHECY;
									just_created_block->is_prophecy_active = true;

									just_created_block->plus_prophecy_button_link->is_active = true;
									just_created_block->remove_prophecy_button->is_active = true;
								}

								if (subdata == "BlightedMap") { parser_mode = Enums::ParserMode::IS_BLIGHTED_MAP; just_created_block->base_filter_data_active.at(Enums::BaseDataOrder::DATA_BLIGHTED) = true; }

							}
							else
							{
								//cout << "comment data: " << subdata << endl;
								if (subdata == "#separator")
								{
									parser_mode = Enums::ParserMode::C_SEPARATOR;

									just_created_separator = new FilterBlockSeparator();
									StaticData::window_filter_block->separator_list.push_back(just_created_separator);


								}

								if (subdata == "#autogen")
								{
									parser_mode = Enums::ParserMode::C_AUTOGEN;
								}
							}
						}
						else
						{

							if (parser_mode == Enums::ParserMode::C_AUTOGEN)
							{
								//cout << "order: " << to_string(data_order) << " subdata: " << subdata << endl;
								if (data_order == 0) {}

								if (data_order == 1)
								{
									if (subdata == "true") {just_created_block->autogen_include.at(0) = true;} else { just_created_block->autogen_include.at(0) = false; }
								}

								if (data_order == 2)
								{
									if (subdata == "true") {just_created_block->autogen_include.at(1) = true;} else { just_created_block->autogen_include.at(1) = false; }
								}

								if (data_order == 3)
								{
									if (subdata == "true") {just_created_block->autogen_include.at(2) = true;} else { just_created_block->autogen_include.at(2) = false; }
								}

								if (data_order == 4)
								{
									if (subdata == "true") {just_created_block->autogen_include.at(3) = true;} else { just_created_block->autogen_include.at(3) = false; }
								}

								if (data_order == 5)
								{
									if (subdata == "true") {just_created_block->autogen_include.at(4) = true;} else { just_created_block->autogen_include.at(4) = false; }
								}
							}

							if (parser_mode == Enums::ParserMode::C_SEPARATOR)
							{
								//cout << "order: " << to_string(data_order) << " subdata: " << subdata << endl;
								if (data_order == 0) {  }
								if (data_order == 1) { just_created_separator->separator_start = std::stoi(subdata); }
								if (data_order == 2) { just_created_separator->separator_end = std::stoi(subdata); }
								if (data_order == 3)
								{
									if (subdata == "true")
									{just_created_separator->is_collapsed = true;}
									else
									{just_created_separator->is_collapsed = false;}

								}
								if (data_order == 4)
								{
									just_created_separator->link_to_caption_text->text = subdata;
									just_created_separator->name = subdata;
								}

							}

							if (parser_mode == Enums::ParserMode::IS_CORRUPTED)
							{
								if (data_order == 0)
								{
									if (show_info_to_console) { cout << "activate corrupted property" << endl; }
								}

								if (data_order == 1)
								{
									if (show_info_to_console) { cout << "set corruption as <" << subdata << ">" << endl; }
									just_created_block->base_filter_data_bool.at(Enums::BoolData::BOOL_CORRUPTION) = EString::convert_text_to_bool(subdata);
								}
							}

							if (parser_mode == Enums::ParserMode::LINKED_SOCKETS)
							{
								if (data_order == 0)
								{
									if (show_info_to_console) { cout << "activate links property" << endl; }
								}

								if ((data_order == 1) && (!EString::check_is_condition_symbols(subdata)))
								{
									if (show_info_to_console) { cout << "set links as <" << subdata << ">" << endl; }
									just_created_block->links_count = std::stoi(subdata);
									just_created_block->links_condition = "=";
								}

								if ((data_order == 1) && (EString::check_is_condition_symbols(subdata)))
								{
									if (show_info_to_console) { cout << "set links condition as <" << subdata << ">" << endl; }
									just_created_block->links_condition = subdata;
								}

								if (data_order == 2)
								{
									if (show_info_to_console) { cout << "set links as <" << subdata << ">" << endl; }
									just_created_block->links_count = std::stoi(subdata);
								}
							}

							if (parser_mode == Enums::ParserMode::RARITY)
							{
								if (data_order == 0)
								{
									if (show_info_to_console) { cout << "activate rarity property" << endl; }
								}

								if ((data_order == 1) && (!EString::check_is_condition_symbols(subdata)))
								{
									if (show_info_to_console) { cout << "set rarity as <" << subdata << ">" << endl; }
									just_created_block->item_rarity = subdata;
									just_created_block->rarity_condition = "=";
								}

								if ((data_order == 1) && (EString::check_is_condition_symbols(subdata)))
								{
									if (show_info_to_console) { cout << "set rarity condition as <" << subdata << ">" << endl; }
									just_created_block->rarity_condition = subdata;
								}

								if (data_order == 2)
								{
									if (show_info_to_console) { cout << "set rarity as <" << subdata << ">" << endl; }
									just_created_block->item_rarity = subdata;
								}
							}


							if (parser_mode == Enums::ParserMode::CLASS)
							{
								//if (data_order == 0) { cout << "activate rarity property" << endl; }
								if (data_order > 0)
								{
									if (show_info_to_console) { cout << "add new base class <" << subdata << ">" << endl; }
									//just_created_block->class_list.push_back(new string(subdata));

									EButtonExplicit* class_button = new EButtonExplicit(0, 0, 100, 20, Enums::ButtonType::BUTTON_CLASS_FILTER_BLOCK_LIST);
									class_button->text = subdata;
									class_button->data_string = subdata;

									class_button->master_block = just_created_block;
									class_button->master_window = StaticData::window_filter_block;
									

									just_created_block->button_list.push_back(class_button);
									just_created_block->base_class_list.push_back(class_button);

									class_button->data_id = -1;

									for (int i = 0; i < EString::base_class_list.size(); i++)
									{
										if ((EString::to_lower(subdata, false) == EString::to_lower(EString::base_class_list.at(i)->base_name, false)) && (class_button->data_id == -1))
										{
											class_button->data_id = i;

											if (EString::active_localisation == Enums::LocalisationList::EN)
											{class_button->text = EString::base_class_list.at(i)->base_name;}

											if (EString::active_localisation == Enums::LocalisationList::RU)
											{class_button->text = EString::base_class_list.at(i)->ru_name;}
										}
									}

									//class_button->text += " (" + std::to_string(class_button->data_id) + ")";

									class_button->button_size_x = EFont::get_width(EFont::active_font, class_button->text) + 5.0f;
									class_button->button_min_size_x = 30.0f;
								}
							}

							if (parser_mode == Enums::ParserMode::HAS_ENCHANTMENT)
							{
								//if (data_order == 0) { cout << "activate rarity property" << endl; }
								if (data_order > 0)
								{
									if (show_info_to_console) { cout << "add new enchantment <" << subdata << ">" << endl; }
									//just_created_block->class_list.push_back(new string(subdata));

									EButtonExplicit* enchantment_button = new EButtonExplicit(0, 0, 100, 20, Enums::ButtonType::BUTTON_ENCHANTMENT_FILTER_BLOCK_LIST);
									enchantment_button->text = subdata;
									enchantment_button->data_string = subdata;

									enchantment_button->master_block = just_created_block;
									enchantment_button->master_window = StaticData::window_filter_block;


									just_created_block->button_list.push_back(enchantment_button);
									just_created_block->enchantment_list.push_back(enchantment_button);

									enchantment_button->data_id = -1;

									
									for (int i = 0; i < EString::enchantment_list.size(); i++)
									{
										if ((EString::to_lower(subdata, false) == EString::to_lower(EString::enchantment_list.at(i)->base_name, false)) && (enchantment_button->data_id == -1))
										{
											enchantment_button->data_id = i;

											if (EString::active_localisation == Enums::LocalisationList::EN)
											{
												enchantment_button->text = EString::enchantment_list.at(i)->base_name;
											}

											if (EString::active_localisation == Enums::LocalisationList::RU)
											{
												enchantment_button->text = EString::enchantment_list.at(i)->ru_name;
											}
										}
									}

									//class_button->text += " (" + std::to_string(class_button->data_id) + ")";

									enchantment_button->button_size_x = EFont::get_width(EFont::active_font, enchantment_button->text) + 5.0f;
									enchantment_button->button_min_size_x = 30.0f;
								}
							}

							if (parser_mode == Enums::ParserMode::FONT_SIZE)
							{
								//if (data_order == 0) { cout << "activate rarity property" << endl; }
								if (data_order > 0)
								{
									if (show_info_to_console) { cout << "set font size <" << subdata << ">" << endl; }
									just_created_block->font_size = EMath::clamp_value_int(std::stoi(subdata),18,45);
								}
							}

							if (parser_mode == Enums::ParserMode::TEXT_COLOR)
							{
								if (data_order == 0) { if (show_info_to_console) { cout << "activate text color property" << endl; } }

								if (data_order == 1) { if (show_info_to_console) { cout << "set font color (red) <" << subdata << ">" << endl; } just_created_block->text_color_red = std::stoi(subdata); }
								if (data_order == 2) { if (show_info_to_console) { cout << "set font color (green) <" << subdata << ">" << endl; } just_created_block->text_color_green = std::stoi(subdata); }
								if (data_order == 3) { if (show_info_to_console) { cout << "set font color (blue) <" << subdata << ">" << endl; } just_created_block->text_color_blue = std::stoi(subdata); }
								if (data_order == 4) { if (show_info_to_console) { cout << "set font color (alpha) <" << subdata << ">" << endl; } just_created_block->text_color_alpha = std::stoi(subdata); }
							}

							if (parser_mode == Enums::ParserMode::BORDER_COLOR)
							{
								if (data_order == 0) { if (show_info_to_console) { cout << "activate border color property" << endl; } }
								if (data_order == 1) { if (show_info_to_console) { cout << "set border color (red) <" << subdata << ">" << endl; } just_created_block->rama_red = std::stoi(subdata); }
								if (data_order == 2) { if (show_info_to_console) { cout << "set border color (green) <" << subdata << ">" << endl; } just_created_block->rama_green = std::stoi(subdata); }
								if (data_order == 3) { if (show_info_to_console) { cout << "set border color (blue) <" << subdata << ">" << endl; } just_created_block->rama_blue = std::stoi(subdata); }
								if (data_order == 4) { if (show_info_to_console) { cout << "set border color (alpha) <" << subdata << ">" << endl; } just_created_block->rama_alpha = std::stoi(subdata); }
							}

							if (parser_mode == Enums::ParserMode::BACKGROUND_COLOR)
							{
								if (data_order == 0) { if (show_info_to_console) { cout << "activate background color property" << endl; } }
								if (data_order == 1) { if (show_info_to_console) { cout << "set background color (red) <" << subdata << ">" << endl; } just_created_block->bg_red = std::stoi(subdata); }
								if (data_order == 2) { if (show_info_to_console) { cout << "set background color (green) <" << subdata << ">" << endl; } just_created_block->bg_green = std::stoi(subdata); }
								if (data_order == 3) { if (show_info_to_console) { cout << "set background color (blue) <" << subdata << ">" << endl; } just_created_block->bg_blue = std::stoi(subdata); }
								if (data_order == 4) { if (show_info_to_console) { cout << "set background color (alpha) <" << subdata << ">" << endl; } just_created_block->bg_alpha = std::stoi(subdata); }
							}

							if (parser_mode == Enums::ParserMode::ALERT_SOUND)
							{
								if (data_order == 0) { if (show_info_to_console) { cout << "activate alert sound property" << endl; } }
								if (data_order == 1)
								{
									if (show_info_to_console) { cout << "set alert sound name <" << subdata << ">" << endl; }

									just_created_block->alert_sound_name = subdata;

									if ((subdata == "01") || (subdata == "1")) { just_created_block->alert_sound_id = Enums::DefaultAlertSound::SOUND_01; }
									if ((subdata == "02") || (subdata == "2")) { just_created_block->alert_sound_id = Enums::DefaultAlertSound::SOUND_02; }
									if ((subdata == "03") || (subdata == "3")) { just_created_block->alert_sound_id = Enums::DefaultAlertSound::SOUND_03; }
									if ((subdata == "04") || (subdata == "4")) { just_created_block->alert_sound_id = Enums::DefaultAlertSound::SOUND_04; }
									if ((subdata == "05") || (subdata == "5")) { just_created_block->alert_sound_id = Enums::DefaultAlertSound::SOUND_05; }
									if ((subdata == "06") || (subdata == "6")) { just_created_block->alert_sound_id = Enums::DefaultAlertSound::SOUND_06; }
									if ((subdata == "07") || (subdata == "7")) { just_created_block->alert_sound_id = Enums::DefaultAlertSound::SOUND_07; }
									if ((subdata == "08") || (subdata == "8")) { just_created_block->alert_sound_id = Enums::DefaultAlertSound::SOUND_08; }
									if ((subdata == "09") || (subdata == "9")) { just_created_block->alert_sound_id = Enums::DefaultAlertSound::SOUND_09; }
									if (subdata == "10") { just_created_block->alert_sound_id = Enums::DefaultAlertSound::SOUND_10; }
									if (subdata == "11") { just_created_block->alert_sound_id = Enums::DefaultAlertSound::SOUND_11; }
									if (subdata == "12") { just_created_block->alert_sound_id = Enums::DefaultAlertSound::SOUND_12; }
									if (subdata == "13") { just_created_block->alert_sound_id = Enums::DefaultAlertSound::SOUND_13; }
									if (subdata == "14") { just_created_block->alert_sound_id = Enums::DefaultAlertSound::SOUND_14; }
									if (subdata == "15") { just_created_block->alert_sound_id = Enums::DefaultAlertSound::SOUND_15; }
									if (subdata == "16") { just_created_block->alert_sound_id = Enums::DefaultAlertSound::SOUND_16; }

									if (EString::to_lower(subdata) == "shalchemy") { just_created_block->alert_sound_id = Enums::DefaultAlertSound::SOUND_SHAPER_ALCHEMY; }
									if (EString::to_lower(subdata) == "shblessed") { just_created_block->alert_sound_id = Enums::DefaultAlertSound::SOUND_SHAPER_BLESSED; }
									if (EString::to_lower(subdata) == "shchaos") { just_created_block->alert_sound_id = Enums::DefaultAlertSound::SOUND_SHAPER_CHAOS; }
									if (EString::to_lower(subdata) == "shdivine") { just_created_block->alert_sound_id = Enums::DefaultAlertSound::SOUND_SHAPER_DIVINE; }
									if (EString::to_lower(subdata) == "shexalted") { just_created_block->alert_sound_id = Enums::DefaultAlertSound::SOUND_SHAPER_EXALTED; }
									if (EString::to_lower(subdata) == "shfusing") { just_created_block->alert_sound_id = Enums::DefaultAlertSound::SOUND_SHAPER_FUSING; }
									if (EString::to_lower(subdata) == "shgeneral") { just_created_block->alert_sound_id = Enums::DefaultAlertSound::SOUND_SHAPER_GENERAL; }
									if (EString::to_lower(subdata) == "shmirror") { just_created_block->alert_sound_id = Enums::DefaultAlertSound::SOUND_SHAPER_MIRROR; }
									if (EString::to_lower(subdata) == "shregal") { just_created_block->alert_sound_id = Enums::DefaultAlertSound::SOUND_SHAPER_REGAL; }
									if (EString::to_lower(subdata) == "shvaal") { just_created_block->alert_sound_id = Enums::DefaultAlertSound::SOUND_SHAPER_VAAL; }

									if (just_created_block->alert_sound_id == Enums::DefaultAlertSound::SOUND_NONE)
									{
										cout << red << "=================================================" << endl;
										cout << red << "ERROR: undefined sound id: " << yellow << "" << subdata << endl;
										cout << red << "=================================================" << endl << white;

										error_counts++;

										//just_created_block->alert_sound_id = Enums::DefaultAlertSound::SOUND_01;
										just_created_block->is_alert_sound = false;
									}
								
								}

								if (data_order == 2) { if (show_info_to_console) { cout << "set alert sound volume <" << subdata << ">" << endl; } just_created_block->alert_sound_volume = std::stoi(subdata); }
							}

							if (parser_mode == Enums::ParserMode::CUSTOM_ALERT_SOUND)
							{
								if (data_order == 0) { if (show_info_to_console) { cout << "activate custom alert sound property" << endl; } }
								if (data_order == 1)
								{
									just_created_block->custom_alert_sound_name = subdata;
								}
							}

							if (parser_mode == Enums::ParserMode::MINIMAP_ICON)
							{
								if (data_order == 0) { if (show_info_to_console) { cout << "activate minimap icon" << endl; } }

								if (data_order == 1)
								{
									just_created_block->minimap_icon_size = Enums::IconSize(std::stoi(subdata));
								}

								if (data_order == 2)
								{
									if (subdata == "Red") { just_created_block->minimap_icon_color = Enums::GameColors::RED; }
									if (subdata == "Green") { just_created_block->minimap_icon_color = Enums::GameColors::GREEN; }
									if (subdata == "Blue") { just_created_block->minimap_icon_color = Enums::GameColors::BLUE; }

									if (subdata == "Brown") { just_created_block->minimap_icon_color = Enums::GameColors::BROWN; }
									if (subdata == "White") { just_created_block->minimap_icon_color = Enums::GameColors::WHITE; }
									if (subdata == "Yellow") { just_created_block->minimap_icon_color = Enums::GameColors::YELLOW; }
								}

								if (data_order == 3)
								{
									if (subdata == "Circle") { just_created_block->minimap_icon_shape = Enums::IconShape::CIRCLE; }
									if (subdata == "Diamond") { just_created_block->minimap_icon_shape = Enums::IconShape::DIAMOND; }
									if (subdata == "Hexagon") { just_created_block->minimap_icon_shape = Enums::IconShape::HEXAGON; }
									if (subdata == "Square") { just_created_block->minimap_icon_shape = Enums::IconShape::SQUARE; }
									if (subdata == "Star") { just_created_block->minimap_icon_shape = Enums::IconShape::STAR; }
									if (subdata == "Triangle") { just_created_block->minimap_icon_shape = Enums::IconShape::TRIANGLE; }
									
								}
							}

							if (parser_mode == Enums::ParserMode::RAY)
							{
								if (data_order == 0) { if (show_info_to_console) { cout << "activate ray property" << endl; } }

								if (data_order == 1)
								{
									if (show_info_to_console) { cout << "set ray color <" << subdata << ">" << endl; }
								
									//std::cout << "subdata: " << subdata << "   ray id: " << Helper::get_id_from_game_color_text(subdata) << std::endl;
									just_created_block->ray_color = Enums::GameColors(Helper::get_id_from_game_color_text(subdata));
								}

								if (data_order == 2)
								{
									if (show_info_to_console) { cout << "ray additional parameter <" << subdata << ">" << endl; }

									if (subdata == "Temp")
									{
										just_created_block->ray_is_temp = true;
									}
								}
								//if (data_order == 2) { cout << "set alert sound volume <" << subdata << ">" << endl; just_created_block->alert_sound_volume = std::stoi(subdata); }
							}

							if (parser_mode == Enums::ParserMode::BASETYPE)
							{
								//if (data_order == 0) { cout << "activate rarity property" << endl; }
								//if ((data_order == 1) && (subdata == "=="))
								//{
								//	parser_mode = Enums::ParserMode::BASETYPE_EQUAL;
								//}
								if ((data_order == 1)&&(subdata == "=="))
								{
									is_base_type_equal_mode = true;
								}

								if ((data_order > 0)&&(subdata != "=="))
								{
									if (show_info_to_console) { cout << "add new base type <" << subdata << ">" << endl; }

									just_created_button = new EButtonFilterItem(0, 0, 45, 45);

									just_created_button->master_block = just_created_block;
									just_created_button->master_window = StaticData::window_filter_block;

									just_created_button->description_text = subdata;

									int item_id = EString::find_item_by_full_name(subdata);

									if (item_id >= 0)
									{
										just_created_button->have_icon = true;
										just_created_button->gabarite = ItemList::item_list.at(item_id)->gabarite;
										//just_created_button->button_size_x = ItemList::item_list.at(item_id)->gabarite->size_x / 2.0f;
										//just_created_button->button_size_y = ItemList::item_list.at(item_id)->gabarite->size_y / 2.0f;

										if (EString::active_localisation == Enums::LocalisationList::EN)
										{just_created_button->description_text = ItemList::item_list.at(item_id)->item_name;}

										if (EString::active_localisation == Enums::LocalisationList::RU)
										{just_created_button->description_text = ItemList::item_list.at(item_id)->item_name_ru + " (" + ItemList::item_list.at(item_id)->item_name + ")";}

										just_created_button->data_string = ItemList::item_list.at(item_id)->item_name;

										if (just_created_button->button_size_x < 30) { just_created_button->button_size_x = 30; }

										just_created_button->data_id = item_id;

										
									}
									else
									{
										just_created_button->have_icon = true;
										just_created_button->gabarite = DefaultGabarite::gabarite_undefined;

										just_created_button->description_text = "Unknown item (" + subdata + ")";
										just_created_button->data_string = subdata;

										if (just_created_button->button_size_x < 30) { just_created_button->button_size_x = 30; }

										just_created_button->data_id = -1;
									}

									((EButtonFilterItem*)just_created_button)->is_full_equal_mode = is_base_type_equal_mode;

									if (is_base_type_equal_mode)
									{
										((EButtonFilterItem*)just_created_button)->change_color_cheme();
									}

									//just_created_button->
									just_created_block->filter_block_items_button_list.push_back(just_created_button);
								}
							}

							if (parser_mode == Enums::ParserMode::IS_SHAPER_ITEM)
							{
								if (data_order == 0) { if (show_info_to_console) { cout << "activate shaper item property" << endl; } }
								if (data_order == 1) { if (show_info_to_console) { cout << "set shaper item as <" << subdata << ">" << endl; } just_created_block->base_filter_data_bool.at(Enums::BoolData::BOOL_SHAPER_ITEM) = EString::convert_text_to_bool(subdata); }
							}

							if (parser_mode == Enums::ParserMode::ITEM_LEVEL)
							{
								if (data_order == 0) { if (show_info_to_console) { cout << "activate item level" << endl; } }


								if ((data_order == 1) && (!EString::check_is_condition_symbols(subdata))) { if (show_info_to_console) { cout << "set item level as <" << subdata << "> condition autogenerated" << endl; } just_created_block->item_level = std::stoi(subdata); just_created_block->item_level_condition = "="; }
								if ((data_order == 1) && (EString::check_is_condition_symbols(subdata))) { if (show_info_to_console) { cout << "set item level condition as <" << subdata << "> id of symbol=" << endl; } just_created_block->item_level_condition = subdata; }

								if (data_order == 2) { if (show_info_to_console) { cout << "set item_level as <" << subdata << ">" << endl; } just_created_block->item_level = std::stoi(subdata); }
							}

							if (parser_mode == Enums::ParserMode::EXPLICIT_MOD)
							{
								//if (data_order == 0) { cout << "activate rarity property" << endl; }
								if (data_order > 0)
								{
									if (show_info_to_console) { cout << "add new explicit mod <" << subdata << ">" << endl; }
									just_created_block->explicit_mod_list.push_back(new string(subdata));

									//cout << "try allocate explicit list at <" << explicit_group_id << ">" << endl;
									EButtonExplicit* explicit_button = new EButtonExplicit(0, 0, 100, 20, Enums::ButtonType::BUTTON_EXPLICIT_FILTER_BLOCK_LIST);

									explicit_button->text = subdata;
									explicit_button->data_string = subdata;

									explicit_button->master_block = just_created_block;
									explicit_button->master_window = StaticData::window_filter_block;

									explicit_button->button_size_x = EFont::get_width(EFont::active_font, subdata) + 5.0f;
									explicit_button->button_min_size_x = 30.0f;

									just_created_block->explicit_list.at(explicit_group_id)->button_list.push_back(explicit_button);
									just_created_block->button_list.push_back(explicit_button);
									just_created_block->explicit_list.at(explicit_group_id)->is_active = true;



									just_created_block->explicit_list.at(explicit_group_id)->button_close->is_active = true;
									just_created_block->explicit_list.at(explicit_group_id)->button_add->is_active = true;


								}
							}

							if (parser_mode == Enums::ParserMode::IDENTIFIED)
							{
								if (data_order == 0) { if (show_info_to_console) { cout << "activate indetify property" << endl; } }
								if (data_order == 1) { if (show_info_to_console) { cout << "set indetification as <" << subdata << ">" << endl; } just_created_block->base_filter_data_bool.at(Enums::BaseDataOrder::DATA_IDENTIFIED) = EString::convert_text_to_bool(subdata); }
							}

							if (parser_mode == Enums::ParserMode::IS_ELDER_ITEM)
							{
								if (data_order == 0) { if (show_info_to_console) { cout << "activate elder item property" << endl; } }
								if (data_order == 1) { if (show_info_to_console) { cout << "set elder item as <" << subdata << ">" << endl; } just_created_block->base_filter_data_bool.at(Enums::BoolData::BOOL_ELDER_ITEM) = EString::convert_text_to_bool(subdata); }
							}

							if (parser_mode == Enums::ParserMode::DROP_LEVEL)
							{
								if (data_order == 0) { if (show_info_to_console) { cout << "activate required level" << endl; } }


								if ((data_order == 1) && (!EString::check_is_condition_symbols(subdata))) { if (show_info_to_console) { cout << "set required level as <" << subdata << "> condition autogenerated" << endl; } just_created_block->required_level = std::stoi(subdata); just_created_block->required_level_condition = "="; }
								if ((data_order == 1) && (EString::check_is_condition_symbols(subdata))) { if (show_info_to_console) { cout << "set required level condition as <" << subdata << "> id of symbol="  << endl; } just_created_block->required_level_condition = subdata; }

								if (data_order == 2) { if (show_info_to_console) { cout << "set required level as <" << subdata << ">" << endl; } just_created_block->required_level = std::stoi(subdata); }
							}

							if (parser_mode == Enums::ParserMode::SOCKETS)
							{
								if (data_order == 0)
								{
									if (show_info_to_console) { cout << "activate sockets property" << endl; }
								}

								if ((data_order == 1) && (!EString::check_is_condition_symbols(subdata)))
								{
									if (show_info_to_console) { cout << "set sockets as <" << subdata << ">" << endl; }
									just_created_block->socket_count = std::stoi(subdata);
									just_created_block->socket_condition = "=";
								}

								if ((data_order == 1) && (EString::check_is_condition_symbols(subdata)))
								{
									if (show_info_to_console) { cout << "set sockets condition as <" << subdata << ">" << endl; }
									just_created_block->socket_condition = subdata;
								}

								if (data_order == 2)
								{
									if (show_info_to_console) { cout << "set sockets as <" << subdata << ">" << endl; }
									just_created_block->socket_count = std::stoi(subdata);
								}
							}

							if (parser_mode == Enums::ParserMode::WIDTH)
							{
								if (data_order == 0)
								{
									if (show_info_to_console) { cout << "activate width property" << endl; }
								}

								if ((data_order == 1) && (!EString::check_is_condition_symbols(subdata)))
								{
									if (show_info_to_console) { cout << "set width as <" << subdata << ">" << endl; }
									just_created_block->item_width = std::stoi(subdata);
									just_created_block->item_width_condition = "=";
								}

								if ((data_order == 1) && (EString::check_is_condition_symbols(subdata)))
								{
									if (show_info_to_console) { cout << "set width condition as <" << subdata << ">" << endl; }
									just_created_block->item_width_condition = subdata;
								}

								if (data_order == 2)
								{
									if (show_info_to_console) { cout << "set width as <" << subdata << ">" << endl; }
									just_created_block->item_width = std::stoi(subdata);
								}
							}

							if (parser_mode == Enums::ParserMode::HEIGHT)
							{
								if (data_order == 0)
								{
									if (show_info_to_console) { cout << "activate height property" << endl; }
								}

								if ((data_order == 1) && (!EString::check_is_condition_symbols(subdata)))
								{
									if (show_info_to_console) { cout << "set height as <" << subdata << ">" << endl; }
									just_created_block->item_height = std::stoi(subdata);
									just_created_block->item_height_condition = "=";
								}

								if ((data_order == 1) && (EString::check_is_condition_symbols(subdata)))
								{
									if (show_info_to_console) { cout << "set height condition as <" << subdata << ">" << endl; }
									just_created_block->item_height_condition = subdata;
								}

								if (data_order == 2)
								{
									if (show_info_to_console) { cout << "set height as <" << subdata << ">" << endl; }
									just_created_block->item_height = std::stoi(subdata);
								}
							}

							if (parser_mode == Enums::ParserMode::IS_FRACTURED_ITEM)
							{
								if (data_order == 0) { if (show_info_to_console) { cout << "activate fractured item property" << endl; } }
								if (data_order == 1) { if (show_info_to_console) { cout << "set fractured item as <" << subdata << ">" << endl; } just_created_block->base_filter_data_bool.at(Enums::BoolData::BOOL_FRACTURED) = EString::convert_text_to_bool(subdata); }
							}

							if (parser_mode == Enums::ParserMode::IS_SYNTHESISED_ITEM)
							{
								if (data_order == 0) { if (show_info_to_console) { cout << "activate synthesised item property" << endl; } }
								if (data_order == 1) { if (show_info_to_console) { cout << "set synthesised item as <" << subdata << ">" << endl; } just_created_block->base_filter_data_bool.at(Enums::BoolData::BOOL_SYNTHESISED) = EString::convert_text_to_bool(subdata); }
							}

							if (parser_mode == Enums::ParserMode::IS_BLIGHTED_MAP)
							{
								if (data_order == 0) { if (show_info_to_console) { cout << "activate blighted map property" << endl; } }
								if (data_order == 1) { if (show_info_to_console) { cout << "set blighted item as <" << subdata << ">" << endl; } just_created_block->base_filter_data_bool.at(Enums::BoolData::BOOL_BLIGHTED) = EString::convert_text_to_bool(subdata); }
							}

							if (parser_mode == Enums::ParserMode::IS_ANY_ENCHANTMENT)
							{
								if (data_order == 0) { if (show_info_to_console) { cout << "activate enchantment item property" << endl; } }
								if (data_order == 1) { if (show_info_to_console) { cout << "set enchantment item as <" << subdata << ">" << endl; } just_created_block->base_filter_data_bool.at(Enums::BoolData::BOOL_ANY_ENCHANTMENT) = EString::convert_text_to_bool(subdata); }
							}

							if (parser_mode == Enums::ParserMode::QUALITY)
							{
								if (data_order == 0)
								{
									if (show_info_to_console) { cout << "activate quality property" << endl; }
								}

								if ((data_order == 1) && (!EString::check_is_condition_symbols(subdata)))
								{
									if (show_info_to_console) { cout << "set quality as <" << subdata << ">" << endl; }
									just_created_block->item_quality = std::stoi(subdata);
									just_created_block->item_quality_condition = "=";
								}

								if ((data_order == 1) && (EString::check_is_condition_symbols(subdata)))
								{
									if (show_info_to_console) { cout << "set hqualityeight condition as <" << subdata << ">" << endl; }
									just_created_block->item_quality_condition = subdata;
								}

								if (data_order == 2)
								{
									if (show_info_to_console) { cout << "set quality as <" << subdata << ">" << endl; }
									just_created_block->item_quality = std::stoi(subdata);
								}
							}

							if (parser_mode == Enums::ParserMode::SOCKET_GROUP)
							{
								if (data_order == 0)
								{
									if (show_info_to_console) { cout << "activate socket group property" << endl; }
								}

								if (data_order == 1)
								{
									just_created_block->red_sockets = 0;
									just_created_block->green_sockets = 0;
									just_created_block->blue_sockets = 0;
									just_created_block->white_sockets = 0;

									for (int socket = 0; socket < subdata.length(); socket++)
									{
										if (subdata.at(socket) == 'R') { just_created_block->red_sockets++; }
										if (subdata.at(socket) == 'G') { just_created_block->green_sockets++; }
										if (subdata.at(socket) == 'B') { just_created_block->blue_sockets++; }
										if (subdata.at(socket) == 'W') { just_created_block->white_sockets++; }
									}

									if (show_info_to_console) { cout << "set RED as <" << just_created_block->red_sockets << "> set GREEN as <" << just_created_block->green_sockets << "> set BLUE as <" << just_created_block->blue_sockets << "> set WHITE as <" << just_created_block->white_sockets << ">" << endl; }
									//just_created_block->item_height = std::stoi(subdata);
									//just_created_block->item_height_condition = "=";
								}


							}

							if (parser_mode == Enums::ParserMode::STACK_SIZE)
							{
								if (data_order == 0)
								{
									if (show_info_to_console) { cout << "activate stack size property" << endl; }
								}

								if ((data_order == 1) && (!EString::check_is_condition_symbols(subdata)))
								{
									if (show_info_to_console) { cout << "set stack size as <" << subdata << ">" << endl; }
									just_created_block->item_stack_size = std::stoi(subdata);
									just_created_block->item_stack_size_condition = "=";
								}

								if ((data_order == 1) && (EString::check_is_condition_symbols(subdata)))
								{
									if (show_info_to_console) { cout << "set stack size condition as <" << subdata << ">" << endl; }
									just_created_block->item_stack_size_condition = subdata;
								}

								if (data_order == 2)
								{
									if (show_info_to_console) { cout << "set stack size as <" << subdata << ">" << endl; }
									just_created_block->item_stack_size = std::stoi(subdata);
								}
							}

							if (parser_mode == Enums::ParserMode::GEM_LEVEL)
							{
								if (data_order == 0)
								{
									if (show_info_to_console) { cout << "activate gem level property" << endl; }
								}

								if ((data_order == 1) && (!EString::check_is_condition_symbols(subdata)))
								{
									if (show_info_to_console) { cout << "set gem level as <" << subdata << ">" << endl; }
									just_created_block->gem_level = std::stoi(subdata);
									just_created_block->gem_level_condition = "=";
								}

								if ((data_order == 1) && (EString::check_is_condition_symbols(subdata)))
								{
									if (show_info_to_console) { cout << "set gem level condition as <" << subdata << ">" << endl; }
									just_created_block->gem_level_condition = subdata;
								}

								if (data_order == 2)
								{
									if (show_info_to_console) { cout << "set gem level as <" << subdata << ">" << endl; }
									just_created_block->gem_level = std::stoi(subdata);
								}
							}

							if (parser_mode == Enums::ParserMode::IS_ELDER_MAP)
							{
								if (data_order == 0) { if (show_info_to_console) { cout << "activate elder map property" << endl; } }
								if (data_order == 1) { if (show_info_to_console) { cout << "set elder map item as <" << subdata << ">" << endl; } just_created_block->base_filter_data_bool.at(Enums::BoolData::BOOL_ELDER_MAP) = EString::convert_text_to_bool(subdata); }
							}

							if (parser_mode == Enums::ParserMode::IS_SHAPER_MAP)
							{
								if (data_order == 0) { if (show_info_to_console) { cout << "activate shaper map property" << endl; } }
								if (data_order == 1) { if (show_info_to_console) { cout << "set shaper map item as <" << subdata << ">" << endl; } just_created_block->base_filter_data_bool.at(Enums::BoolData::BOOL_SHAPER_MAP) = EString::convert_text_to_bool(subdata); }
							}

							if (parser_mode == Enums::ParserMode::MAP_TIER)
							{
								if (data_order == 0)
								{
									if (show_info_to_console) { cout << "activate map tier property" << endl; }
								}

								if ((data_order == 1) && (!EString::check_is_condition_symbols(subdata)))
								{
									if (show_info_to_console) { cout << "set gem level as <" << subdata << ">" << endl; }
									just_created_block->map_tier = std::stoi(subdata);
									just_created_block->map_tier_condition = "=";
								}

								if ((data_order == 1) && (EString::check_is_condition_symbols(subdata)))
								{
									if (show_info_to_console) { cout << "set map tier condition as < " << subdata << " >" << endl; }
									just_created_block->map_tier_condition = subdata;
								}

								if (data_order == 2)
								{
									if (show_info_to_console) { cout << "set gem level as <" << subdata << ">" << endl; }
									just_created_block->map_tier = std::stoi(subdata);
								}
							}

							if (parser_mode == Enums::ParserMode::PROPHECY)
							{
								//if (data_order == 0) { cout << "activate rarity property" << endl; }
								if (data_order > 0) {
									if (show_info_to_console)
									{
										cout << "add new prophecy mod <" << subdata << ">" << endl;
									}
									EButtonExplicit* prophecy_button = new EButtonExplicit(0, 0, 100, 20, Enums::ButtonType::BUTTON_PROPHECY_FILTER_BLOCK_LIST);
									prophecy_button->text = subdata;
									prophecy_button->data_string = subdata;

									prophecy_button->master_block = just_created_block;
									prophecy_button->master_window = StaticData::window_filter_block;
								

									prophecy_button->data_id = -1;

									for (int sr = 0; sr < EString::prophecy_list.size(); sr++)
									{
										if (EString::prophecy_list.at(sr)->base_name == subdata)
										{
											prophecy_button->data_id = sr;

											if (EString::active_localisation == Enums::LocalisationList::EN)
											{prophecy_button->text = EString::prophecy_list.at(sr)->base_name;}

											if (EString::active_localisation == Enums::LocalisationList::RU)
											{prophecy_button->text = EString::prophecy_list.at(sr)->ru_name;}
										}
									}

									prophecy_button->button_size_x = EFont::get_width(EFont::active_font, prophecy_button->text) + 5.0f;
									prophecy_button->button_min_size_x = 30.0f;

									just_created_block->button_list.push_back(prophecy_button);
									just_created_block->prophecy_list.push_back(prophecy_button);
								}


							}


						}

						data_order++;
						if ((data_order == 1) && (parser_mode == Enums::ParserMode::NOTHING) && (!comment_mode))
						{
							cout << red << "=================================================" << endl;
							cout << red << "ERROR: undefined property: " << yellow << "" << subdata << endl;
							cout << red << "=================================================" << endl << white;

							error_counts++;
						}

						subdata = "";
					}
					else
					{
						if (show_info_to_console) { cout << "--EMPTY SUBDATA#" << endl; }
					}
				}
			}
			if (show_info_to_console) { cout << endl << endl; }

			line_number++;
		}

		for (FilterBlock* f : StaticData::window_filter_block->filter_block_list)
		{
			f->data_change();
		}

		for (FilterBlockSeparator* sep : StaticData::window_filter_block->separator_list)
		{
			
				for (int i = sep->separator_start; i <= sep->separator_end; i++)
				{
					StaticData::window_filter_block->filter_block_list.at(i)->hided_by_separator = sep->is_collapsed;
				}
		}

		if (error_counts <= 0) { cout << green << "Error count:0" << endl;; }
		else
		{
			cout << red << "Error count:" << yellow << error_counts << white << endl;;
		}
		myfile.close();

		//std::cout << "try update localisation" << std::endl;
		StaticData::window_filter_block->update_localisation();
		StaticData::window_filter_block->unsave_change = false;
		/*
		StaticData::window_loot_simulator->manual_event();
		StaticData::window_loot_simulator->is_active = true;
		*/

		for (int i = 0; i < StaticData::window_filter_block->filter_block_list.size(); i++)
		{
			StaticData::window_filter_block->filter_block_list.at(i)->order_id = i;
		}

		StaticData::window_filter_block->recalculate_filter_block_separator();
	}

	void EFile::save_filter(std::string _path, Enums::AutogenSaveMode _save_mode, bool _ignore_autogen)
	{
		StaticData::window_filter_block->unsave_change = false;
		//std::experimental::filesystem::copy(_path, _path); // copy file

		ofstream myfile;
		myfile.open(_path);

		std::string loot_writer;
		loot_writer = "#Created due to DaD Editor (by NoSimpleWay)";
		loot_writer += '\n';
		loot_writer += '\n';
		loot_writer += '\n';

		std::string string_for_autogen_data = "";

		for (FilterBlockSeparator* sep : StaticData::window_filter_block->separator_list)
		{
			loot_writer += "#separator ";
			loot_writer +=std::to_string(sep->separator_start);
			loot_writer += " ";
			loot_writer += std::to_string(sep->separator_end);
			

			if (sep->is_collapsed)
			{loot_writer +=" true";}
			else
			{loot_writer +=" false";}

			loot_writer += " ";
			loot_writer += '"';
			loot_writer += sep->link_to_caption_text->text;
			loot_writer += '"';

			loot_writer += '\n';
		}

		for (FilterBlock* fb:StaticData::window_filter_block->filter_block_list)
		{
			loot_writer += '\n';
			loot_writer += '\n';


			//if ((fb->autogen_include.at(_save_mode)) || (_ignore_autogen))
			if
			(
				(fb->is_show)
				&&
				(
					(fb->autogen_include.at(_save_mode))
					||
					(_ignore_autogen)
				)
			)
			{
				loot_writer += "Show";
				loot_writer += '\n';
			}
			else
			{
				loot_writer += "Hide";
				loot_writer += '\n';
			}

			if (_save_mode == Enums::AutogenSaveMode::SOURCE)
			{
				loot_writer += "#autogen ";

				if (fb->autogen_include.at(0)) { loot_writer += "true "; }
				else { loot_writer += "false "; }

				if (fb->autogen_include.at(1)) { loot_writer += "true "; }
				else { loot_writer += "false "; }

				if (fb->autogen_include.at(2)) { loot_writer += "true "; }
				else { loot_writer += "false "; }

				if (fb->autogen_include.at(3)) { loot_writer += "true "; }
				else { loot_writer += "false "; }

				if (fb->autogen_include.at(4)) { loot_writer += "true\n"; }
				else { loot_writer += "false\n"; }
			}

			if (fb->base_filter_data_active.at(Enums::BaseDataOrder::DATA_CORRUPTED))
			{
				if (fb->base_filter_data_bool.at(Enums::BoolData::BOOL_CORRUPTION))
				{
					loot_writer += '\t';
					loot_writer += "Corrupted True";
					loot_writer += '\n';
				}
				else
				{
					loot_writer += '\t';
					loot_writer += "Corrupted False";
					loot_writer += '\n';
				}
			}
			
			if (fb->base_filter_data_active.at(Enums::BaseDataOrder::DATA_LINKS))
			{
				loot_writer += '\t';
				loot_writer += "LinkedSockets ";
				loot_writer += fb->links_condition;
				loot_writer += " ";
				loot_writer += std::to_string(fb->links_count);

				loot_writer += '\n';
			}

			if (fb->base_filter_data_active.at(Enums::BaseDataOrder::DATA_RARITY))
			{
				loot_writer += '\t';
				loot_writer += "Rarity ";
				loot_writer += fb->rarity_condition;
				loot_writer += " ";
				loot_writer += fb->item_rarity;

				loot_writer += '\n';
			}

			if ((fb->is_base_class_active) && (fb->base_class_list.size() > 0))
			{
				loot_writer += '\t';
				loot_writer += "Class";

				for (EButton* b : fb->base_class_list)
				{
					loot_writer += " ";
					loot_writer += '"';
					loot_writer += b->data_string;
					loot_writer += '"';
				}

				loot_writer += '\n';
			}

			if ((fb->is_enchantment_active) && (fb->enchantment_list.size() > 0))
			{
				loot_writer += '\t';
				loot_writer += "HasEnchantment";

				for (EButton* b : fb->enchantment_list)
				{
					loot_writer += " ";
					loot_writer += '"';
					loot_writer += b->data_string;
					loot_writer += '"';
				}

				loot_writer += '\n';
			}

			if (fb->is_font_size_active)
			{
				loot_writer += '\t';
				loot_writer += "SetFontSize ";

				string_for_autogen_data = std::to_string(fb->font_size);

				if
				(
					(!fb->autogen_include.at(_save_mode))
					&&
					(!_ignore_autogen)
				)
				{
					string_for_autogen_data = "16";
				}

				loot_writer += string_for_autogen_data;


				loot_writer += '\n';
			}

			if (fb->is_text_color_active)
			{
				loot_writer += '\t';
				loot_writer += "SetTextColor ";

				loot_writer += std::to_string(fb->text_color_red);
				loot_writer += " ";

				loot_writer += std::to_string(fb->text_color_green);
				loot_writer += " ";

				loot_writer += std::to_string(fb->text_color_blue);
				loot_writer += " ";

				loot_writer += std::to_string(fb->text_color_alpha);

				loot_writer += '\n';
			}

			if (fb->is_rama_color_active)
			{
				loot_writer += '\t';
				loot_writer += "SetBorderColor ";

				loot_writer += std::to_string(fb->rama_red);
				loot_writer += " ";

				loot_writer += std::to_string(fb->rama_green);
				loot_writer += +" ";

				loot_writer += std::to_string(fb->rama_blue);
				loot_writer += " ";

				loot_writer += std::to_string(fb->rama_alpha);

				loot_writer += '\n';
			}
			if (fb->is_bg_color_active)
			{
				loot_writer += '\t';
				loot_writer += "SetBackgroundColor ";

				loot_writer += std::to_string(fb->bg_red);
				loot_writer += " ";

				loot_writer += std::to_string(fb->bg_green);
				loot_writer += " ";

				loot_writer += std::to_string(fb->bg_blue);
				loot_writer += " ";

				loot_writer += std::to_string(fb->bg_alpha);

				loot_writer += '\n';
			}

			if
			(
				(fb->is_alert_sound)
				&&
				(
					(fb->autogen_include.at(_save_mode))
					||
					(_ignore_autogen)
				)
			)
			{
				loot_writer += '\t';
				if (fb->is_positional_sound)
				{loot_writer += "PlayAlertSound ";}
				else
				{loot_writer += "PlayAlertSoundPositional ";}

				loot_writer += fb->alert_sound_name;
				loot_writer += " ";

				loot_writer += std::to_string(fb->alert_sound_volume);

				loot_writer += '\n';
			}

			if
			(
				fb->is_custom_alert_sound
				&&
				(
					(fb->autogen_include.at(_save_mode))
					||
					(_ignore_autogen)
				)
			)
			{
				loot_writer += '\t';
				loot_writer += "CustomAlertSound ";

				loot_writer += '"';
				loot_writer += fb->custom_alert_sound_name;
				loot_writer += '"';

				loot_writer += '\n';
			}

			if
			(
				fb->is_ray
				&&
				(
					(fb->autogen_include.at(_save_mode))
					||
					(_ignore_autogen)
				)
			)
			{
				loot_writer += '\t';
				loot_writer += "PlayEffect ";

				
				loot_writer += EString::game_color_name[fb->ray_color];

				loot_writer += '\n';
			}


			if
			(
				fb->is_minimap_icon
				&&
				(
					(fb->autogen_include.at(_save_mode))
					||
					(_ignore_autogen)
				)
			)
			{
				loot_writer += '\t';
				loot_writer += "MinimapIcon ";
				loot_writer += std::to_string(fb->minimap_icon_size);
				loot_writer += " ";

				loot_writer += EString::game_color_name[fb->minimap_icon_color];
				loot_writer += " ";
				loot_writer += EString::icon_shape_name[fb->minimap_icon_shape];

				loot_writer += '\n';
			}

			bool have_equal_base_type = false;

			for (EButton* b : fb->filter_block_items_button_list)
			{
				if (((EButtonFilterItem*)b)->is_full_equal_mode)
				{
					have_equal_base_type = true;
				}
			}

			if (have_equal_base_type)
			{
				loot_writer += '\t';
				loot_writer += "BaseType ==";

				for (EButton* b : fb->filter_block_items_button_list)
				if (((EButtonFilterItem*)b)->is_full_equal_mode)
				{
					loot_writer += ' ';
					loot_writer += '"';
					loot_writer += b->data_string;
					loot_writer += '"';
				}

				loot_writer += '\n';
			}

			bool have_regular_base_type = false;

			for (EButton* b : fb->filter_block_items_button_list)
			{
				if (!((EButtonFilterItem*)b)->is_full_equal_mode)
				{
					have_regular_base_type = true;
				}
			}

			if ((have_regular_base_type) && (fb->filter_block_items_button_list.size() > 0))
			{
				loot_writer += '\t';
				loot_writer += "BaseType";

				for (EButton* b : fb->filter_block_items_button_list)
				if (!((EButtonFilterItem*)b)->is_full_equal_mode)
				{
					loot_writer += ' ';
					loot_writer += '"';
					loot_writer += b->data_string;
					loot_writer += '"';
				}

				loot_writer += '\n';
			}

			if (fb->base_filter_data_active.at(Enums::BaseDataOrder::DATA_SHAPER_ITEM))
			{
				if (fb->base_filter_data_bool.at(Enums::BoolData::BOOL_SHAPER_ITEM))
				{
					loot_writer += '\t';
					loot_writer += "ShaperItem True";
					loot_writer += '\n';
				}
				else
				{
					loot_writer += '\t';
					loot_writer += "ShaperItem False";
					loot_writer += '\n';
				}
			}

			if (fb->base_filter_data_active.at(Enums::BaseDataOrder::DATA_ITEM_LEVEL))
			{
				loot_writer += '\t';
				loot_writer += "ItemLevel ";

				loot_writer += fb->item_level_condition;
				loot_writer += " ";
				loot_writer += std::to_string(fb->item_level);

				loot_writer += '\n';
			}

			for (ExplicitGroup* ex : fb->explicit_list)
			{
				if ((ex->is_active)&&(ex->button_list.size()>0))
				{
					loot_writer += '\t';
					loot_writer += "HasExplicitMod";

					for (EButton* b : ex->button_list)
					{
						loot_writer += ' ';
						loot_writer += '"';
						loot_writer += b->text;
						loot_writer += '"';
					}

					loot_writer += '\n';
				}
			}

			if (fb->base_filter_data_active.at(Enums::BaseDataOrder::DATA_IDENTIFIED))
			{
				if (fb->base_filter_data_bool.at(Enums::BoolData::BOOL_IDENTIFIED))
				{
					loot_writer += '\t';
					loot_writer += "Identified True";
					loot_writer += '\n';
				}
				else
				{
					loot_writer += '\t';
					loot_writer += "Identified False";
					loot_writer += '\n';
				}
			}

			if (fb->base_filter_data_active.at(Enums::BaseDataOrder::DATA_ELDER_ITEM))
			{
				if (fb->base_filter_data_bool.at(Enums::BoolData::BOOL_ELDER_ITEM))
				{
					loot_writer += '\t';
					loot_writer += "ElderItem True";
					loot_writer += '\n';
				}
				else
				{
					loot_writer += '\t';
					loot_writer += "ElderItem False";
					loot_writer += '\n';
				}
			}

			if (fb->base_filter_data_active.at(Enums::BaseDataOrder::DATA_REQUIRED_LEVEL))
			{
				loot_writer += '\t';
				loot_writer += "DropLevel ";

				loot_writer += fb->required_level_condition;
				loot_writer += " ";
				loot_writer += std::to_string(fb->required_level);

				loot_writer += '\n';
			}

			if (fb->base_filter_data_active.at(Enums::BaseDataOrder::DATA_SOCKETS))
			{
				loot_writer += '\t';
				loot_writer += "Sockets ";

				loot_writer += fb->socket_condition;
				loot_writer += " ";
				loot_writer += std::to_string(fb->socket_count);

				loot_writer += '\n';
			}


			if (fb->base_filter_data_active.at(Enums::BaseDataOrder::DATA_FRACTURED))
			{
				if (fb->base_filter_data_bool.at(Enums::BoolData::BOOL_FRACTURED))
				{
					loot_writer += '\t';
					loot_writer += "FracturedItem True";
					loot_writer += '\n';
				}
				else
				{
					loot_writer += '\t';
					loot_writer += "FracturedItem False";
					loot_writer += '\n';
				}
			}

			if (fb->base_filter_data_active.at(Enums::BaseDataOrder::DATA_WIDTH))
			{
				loot_writer += '\t';
				loot_writer += "Width ";

				loot_writer += fb->item_width_condition;
				loot_writer += " ";
				loot_writer += std::to_string(fb->item_width);

				loot_writer += '\n';
			}

			if (fb->base_filter_data_active.at(Enums::BaseDataOrder::DATA_HEIGHT))
			{
				loot_writer += '\t';
				loot_writer += "Height ";

				loot_writer += fb->item_height_condition;
				loot_writer += " ";
				loot_writer += std::to_string(fb->item_height);

				loot_writer += '\n';
			}

			if (fb->base_filter_data_active.at(Enums::BaseDataOrder::DATA_SYNTHESISED))
			{
				if (fb->base_filter_data_bool.at(Enums::BoolData::BOOL_SYNTHESISED))
				{
					loot_writer += '\t';
					loot_writer += "SynthesisedItem True";
					loot_writer += '\n';
				}
				else
				{
					loot_writer += '\t';
					loot_writer += "SynthesisedItem False";
					loot_writer += '\n';
				}
			}

			if (fb->base_filter_data_active.at(Enums::BaseDataOrder::DATA_BLIGHTED))
			{
				if (fb->base_filter_data_bool.at(Enums::BoolData::BOOL_BLIGHTED))
				{
					loot_writer += '\t';
					loot_writer += "BlightedMap True";
					loot_writer += '\n';
				}
				else
				{
					loot_writer += '\t';
					loot_writer += "BlightedMap False";
					loot_writer += '\n';
				}
			}

			if (fb->base_filter_data_active.at(Enums::BaseDataOrder::DATA_ENCHANTMENT))
			{
				if (fb->base_filter_data_bool.at(Enums::BoolData::BOOL_ANY_ENCHANTMENT))
				{
					loot_writer += '\t';
					loot_writer += "AnyEnchantment True";
					loot_writer += '\n';
				}
				else
				{
					loot_writer += '\t';
					loot_writer += "AnyEnchantment False";
					loot_writer += '\n';
				}
			}

			if (fb->base_filter_data_active.at(Enums::BaseDataOrder::DATA_QUALITY))
			{
				loot_writer += '\t';
				loot_writer += "Quality ";

				loot_writer += fb->item_quality_condition;
				loot_writer += " ";
				loot_writer += std::to_string(fb->item_quality);

				loot_writer += '\n';
			}

			if (fb->base_filter_data_active.at(Enums::BaseDataOrder::DATA_SOCKET_GROUP))
			{
				loot_writer += '\t';
				loot_writer += "SocketGroup ";

				for (int i = 0; i < fb->red_sockets; i++)		{ loot_writer += "R"; }
				for (int i = 0; i < fb->green_sockets; i++)		{ loot_writer += "G"; }
				for (int i = 0; i < fb->blue_sockets; i++)		{ loot_writer += "B"; }
				for (int i = 0; i < fb->white_sockets; i++)		{ loot_writer += "W"; }

				loot_writer += '\n';
			}

			if (fb->base_filter_data_active.at(Enums::BaseDataOrder::DATA_GEM_LEVEL))
			{
				loot_writer += '\t';
				loot_writer += "GemLevel ";

				loot_writer += fb->gem_level_condition;
				loot_writer += " ";
				loot_writer += std::to_string(fb->gem_level);

				loot_writer += '\n';
			}

			if (fb->base_filter_data_active.at(Enums::BaseDataOrder::DATA_ELDER_MAP))
			{
				if (fb->base_filter_data_bool.at(Enums::BoolData::BOOL_ELDER_MAP))
				{
					loot_writer += '\t';
					loot_writer += "ElderMap True";
					loot_writer += '\n';
				}
				else
				{
					loot_writer += '\t';
					loot_writer += "ElderMap False";
					loot_writer += '\n';
				}
			}

			if (fb->base_filter_data_active.at(Enums::BaseDataOrder::DATA_SHAPER_MAP))
			{
				if (fb->base_filter_data_bool.at(Enums::BoolData::BOOL_SHAPER_MAP))
				{
					loot_writer += '\t';
					loot_writer += "ShapedMap True";
					loot_writer += '\n';
				}
				else
				{
					loot_writer += '\t';
					loot_writer += "ShapedMap False";
					loot_writer += '\n';
				}
			}

			if (fb->base_filter_data_active.at(Enums::BaseDataOrder::DATA_MAP_TIER))
			{
				loot_writer += '\t';
				loot_writer += "MapTier ";

				loot_writer += fb->map_tier_condition;
				loot_writer += " ";
				loot_writer += std::to_string(fb->map_tier);

				loot_writer += '\n';
			}

			if (fb->is_prophecy_active)
			{
				loot_writer += '\t';
				loot_writer += "Prophecy";

				for (EButton* b : fb->prophecy_list)
				{
					loot_writer += " ";
					loot_writer += '"';
					loot_writer += b->data_string;
					loot_writer += '"';
				}

				loot_writer += '\n';
			}

			if (fb->base_filter_data_active.at(Enums::BaseDataOrder::DATA_STACK_SIZE))
			{
				loot_writer += '\t';
				loot_writer += "StackSize ";

				loot_writer += fb->item_stack_size_condition;
				loot_writer += " ";
				loot_writer += std::to_string(fb->item_stack_size);

				loot_writer += '\n';
			}

		}

		myfile << loot_writer;
		myfile.close();

		/*
		myfile.open("D:\\c++\\EDGEngine\\x64\\Debug\\EDGEngine.exe");
		if (myfile.is_open())
		{
			std::cout << "OPENED EDGEengine" << std::endl;
		}
			myfile << "OLOLO";
		myfile.close();
		*/


	}
