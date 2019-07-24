#pragma once
#include <vector>
#include <irr/irrKlang.h>
#include <string>
#include <string>

class EMath
{
public:
	static float clamp_value_float(float _v, float _min, float _max);

	static struct rgb {
		double r;       // a fraction between 0 and 1
		double g;       // a fraction between 0 and 1
		double b;       // a fraction between 0 and 1
	};

	static struct hsv {
		double h;       // angle in degrees
		double s;       // a fraction between 0 and 1
		double v;       // a fraction between 0 and 1
	};

	static hsv rgb2hsv(rgb in);
	static rgb hsv2rgb(hsv in);
};

class ESound
{
public:
	static std::vector<irrklang::ISoundSource*> default_drop_sound;
	static std::vector<irrklang::ISoundSource*> custom_drop_sound;

	static std::vector<std::string> default_drop_sound_name;
	static std::vector<std::string> custom_drop_sound_name;

	static irrklang::ISoundEngine* engine;

	static void load_custom_sound();
	static irrklang::ISoundSource* get_sound_by_name(std::string _name);
	//irrklang::ISoundSource* shootSound = engine->addSoundSourceFromFile("data/cool01.wav");
};

class EString
{
public:
	static std::string upper_charset;
	static std::string lower_charset;

	static std::string to_lower(std::string _s, bool _b);

	static std::string path_to_poe_folder;
};