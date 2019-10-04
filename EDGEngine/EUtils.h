#pragma once
#include <vector>
#include <irr/irrKlang.h>
#include "BaseClass.h"
#include "ProphecyList.h"
#include "LabEnchantment.h"
#include "NotablePassive.h"

#include <string>


class EMath
{
public:
	static float clamp_value_float(float _v, float _min, float _max);
	static float clamp_value_int(int _v, int _min, int _max);

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

	static irrklang::ISoundSource* flip_sound;

	static std::vector<std::string> default_drop_sound_name;
	static std::vector<std::string> default_drop_sound_original_name;

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

	static void load_localisation(std::string _text);
	static void load_loot_pattern(std::string _text);

	static std::string to_lower(std::string _s);

	static std::string to_lower(std::string _s, bool _b);

	static void load_loot_simulator_pattern_list();

	static std::string path_to_poe_folder;

	static std::vector<LabEnchantment*> enchantment_list;
	static std::vector<BaseClass*> base_class_list;

	static std::vector<ProphecyList*> prophecy_list;

	static void load_loot_filter_list();

	static bool convert_text_to_bool(std::string _text);

	static bool check_is_condition_symbols(std::string _s);

	static int find_item_by_full_name(std::string _name);

	static std::vector<std::string> loot_simulator_pattern_name_list;
	static std::vector<std::string> loot_simulator_pattern_path_list;


	static std::vector<std::string> loot_filter_name_list;
	static std::vector<std::string> loot_filter_path_list;

	static std::vector <std::string> path_list;

	static std::string opened_loot_filter_name;
	static std::string opened_loot_filter_path;

	static std::string game_color_name[6];
	static std::string icon_shape_name[6];

	static std::vector<std::string> localisation_key;
	static std::vector<std::string> localisation_text;
	


	static std::string localize_it(std::string _text);

	static Enums::LocalisationList active_localisation;

	static std::string to_cyrillic(std::string _text);

	static void save_config();
	static void load_config();

	static bool font_is_configued;
	static bool localisation_is_configued;

	static std::vector <std::string> notable_passives_name;
	static std::vector <std::string> notable_passives_description;

	static std::vector <std::string> notable_passives_ru_name;
	static std::vector <std::string> notable_passives_ru_description;

	static std::vector <NotablePassive*> notable_list;

	static std::vector < std::string> oil_name_list;

};

class EFile
{
public:
	static void parse_loot_filter_data(std::string _path);
	static void save_filter(std::string _path, Enums::AutogenSaveMode _save_mode, bool _ignore_autogen);
	//static void save_filter(std::string _path);
};



