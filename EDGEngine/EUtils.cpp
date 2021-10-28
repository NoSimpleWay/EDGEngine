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
#include "EColor.h"

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
	
	std::vector< EString::cluster_enchantment_struct* > EString::cluster_enchantment_list;


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

	std::vector<EColor*> EString::loot_pattern_button_color;
	std::vector<EColor*> EString::loot_pattern_text_color;

	std::string EString::icon_color_name[10]
	=
	{
		"Red",
		"Green",
		"Blue",

		"Yellow",
		"White",
		"Cyan",

		"Grey",
		"Orange",
		"Pink",

		"Purple"
	}
	;

	std::string EString::game_color_name[11]
	=
	{
		"Red",
		"Green",
		"Blue",
		"Brown",
		"White",
		"Yellow",

		"Cyan",
		"Grey",
		"Orange",
		"Pink",
		"Purple"
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

			//std::wstring wsTmp((subdata_array[1]).begin(), (subdata_array[1]).end());
			//localisation_text.push_back(wsTmp);

			if (line_id <= 0)
			{
				localisation_text.push_back(to_cyryllic(subdata_array[1], true));
			}
			else
			{
				localisation_text.push_back(to_cyryllic(subdata_array[1], false));
			}

			//std::cout << "KEY (" << subdata_array[0] << ")   VALUE (" << localisation_text.at(localisation_text.size() - 1) << ")" << std::endl;

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

		EString::loot_pattern_button_color.clear();
		EString::loot_pattern_text_color.clear();



		//ofstream myfile_open;
		//myfile_open.open("gemor.txt");

		ifstream myfile;
		myfile.open("data/loot simulator/pattern/" + _text + ".txt");
		string line;

		string subdata;
		string subdata_array[20];

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

			for (int i = 0; i < 10; i++)
			{
				if (subdata_array[i * 2] == "name_en")
				{EString::loot_pattern_name.push_back(subdata_array[i * 2 + 1]);}

				if (subdata_array[i * 2] == "name_ru")
				{EString::loot_pattern_name_ru.push_back(EString::to_cyryllic(subdata_array[i * 2 + 1]));}

				if (subdata_array[i * 2] == "description_en")
				{EString::loot_pattern_description.push_back(subdata_array[i * 2 + 1]);}

				if (subdata_array[i * 2] == "description_ru")
				{EString::loot_pattern_description_ru.push_back(EString::to_cyryllic(subdata_array[i * 2 + 1]));}

				if (subdata_array[i * 2] == "path")
				{EString::loot_pattern_path.push_back(subdata_array[i * 2 + 1]);}

				if (subdata_array[i * 2] == "button_color")
				{
					if (subdata_array[i * 2 + 1] == "RED")		{EString::loot_pattern_button_color.push_back(EColorCollection::RED); };
					if (subdata_array[i * 2 + 1] == "GREEN")	{EString::loot_pattern_button_color.push_back(EColorCollection::GREEN); };
					if (subdata_array[i * 2 + 1] == "BLUE")		{EString::loot_pattern_button_color.push_back(EColorCollection::BLUE); };
					if (subdata_array[i * 2 + 1] == "BLACK")	{EString::loot_pattern_button_color.push_back(EColorCollection::BLACK); };
					if (subdata_array[i * 2 + 1] == "WHITE")	{EString::loot_pattern_button_color.push_back(EColorCollection::WHITE); };
					if (subdata_array[i * 2 + 1] == "YELLOW")	{EString::loot_pattern_button_color.push_back(EColorCollection::YELLOW); };
					if (subdata_array[i * 2 + 1] == "PINK")		{EString::loot_pattern_button_color.push_back(EColorCollection::PINK); };

					//{EString::loot_pattern_button_color.push_back(EColorCollection::CYAN); };
				}

				if (subdata_array[i * 2] == "text_color")
				{
					//std::cout << "color = " << subdata_array[i * 2 + 1] << std::endl;
					if (subdata_array[i * 2 + 1] == "RED")		{EString::loot_pattern_text_color.push_back(EColorCollection::RED); };
					if (subdata_array[i * 2 + 1] == "GREEN")	{EString::loot_pattern_text_color.push_back(EColorCollection::GREEN); };
					if (subdata_array[i * 2 + 1] == "BLUE")		{EString::loot_pattern_text_color.push_back(EColorCollection::BLUE); };
					if (subdata_array[i * 2 + 1] == "BLACK")	{EString::loot_pattern_text_color.push_back(EColorCollection::BLACK); };
					if (subdata_array[i * 2 + 1] == "WHITE")	{EString::loot_pattern_text_color.push_back(EColorCollection::WHITE); };
					if (subdata_array[i * 2 + 1] == "YELLOW")	{EString::loot_pattern_text_color.push_back(EColorCollection::YELLOW); };
					if (subdata_array[i * 2 + 1] == "PINK")		{EString::loot_pattern_text_color.push_back(EColorCollection::PINK); };

					//{EString::loot_pattern_text_color.push_back(EColorCollection::CYAN); };
				}
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
					just_created_pattern_item->item_name = EString::to_cyryllic(subdata_array[i * 2 + 1]);
				}


				if (EString::to_lower(subdata_array[i * 2], false) == "class")
				{
					just_created_pattern_item->base_class = EString::to_cyryllic(subdata_array[i * 2 + 1]);
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

				if (EString::to_lower(subdata_array[i * 2], false) == "cluster_passives_min")
				{
					just_created_pattern_item->min_cluster_passives = std::stoi(subdata_array[i * 2 + 1]);
				}

				if (EString::to_lower(subdata_array[i * 2], false) == "cluster_passives_max")
				{
					just_created_pattern_item->max_cluster_passives = std::stoi(subdata_array[i * 2 + 1]);
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


				if (EString::to_lower(subdata_array[i * 2], false) == "replica_chance")
				{
					just_created_pattern_item->replica_chance = std::stoi(subdata_array[i * 2 + 1]);
				}

				if (EString::to_lower(subdata_array[i * 2], false) == "alternate_quality_chance")
				{
					just_created_pattern_item->alternate_quality_chance = std::stoi(subdata_array[i * 2 + 1]);
				}



				if (EString::to_lower(subdata_array[i * 2], false) == "mirrored_chance")
				{
					just_created_pattern_item->mirrored_chance = std::stoi(subdata_array[i * 2 + 1]);
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

					//cout << "max sockets [" << just_created_pattern_item->random_class << "] = " << just_created_pattern_item->max_sockets << " data (" << subdata_array[i * 2 + 1] << ")" << endl;
					
				}


				if (EString::to_lower(subdata_array[i * 2], false) == "defence_pertencile_min")
				{
					just_created_pattern_item->defence_pertentile_min = std::stoi(subdata_array[i * 2 + 1]);
				}

				if (EString::to_lower(subdata_array[i * 2], false) == "defence_pertencile_max")
				{
					just_created_pattern_item->defence_pertentile_max = std::stoi(subdata_array[i * 2 + 1]);
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

				if (EString::to_lower(subdata_array[i * 2], false) == "uber_blighted_map")
				{
					just_created_pattern_item->uber_blighted_map = true;
				}

				if (EString::to_lower(subdata_array[i * 2], false) == "scourged")
				{
					just_created_pattern_item->scourged = true;
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

				if (EString::to_lower(subdata_array[i * 2], false) == "cluster_enchantment")
				{
					just_created_pattern_item->cluster_enchantment = subdata_array[i * 2 + 1];
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

	std::string EString::icon_shape_name[12]
	=
	{
		"Circle",
		"Diamond",
		"Hexagon",
		"Square",
		"Star",
		"Triangle",

		"Cross",
		"Moon",
		"Raindrop",
		"Kite",
		"Pentagon",
		"UpsideDownHouse"

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

				EString::loot_simulator_pattern_path_list.push_back(UTF8_to_ANSI(loot_filter_name));
				EString::loot_simulator_pattern_name_list.push_back(UTF8_to_ANSI(p.path().filename().u8string().substr(0, p.path().filename().u8string().length() - 8)));

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

				EString::loot_filter_path_list.push_back(UTF8_to_ANSI(loot_filter_name));
				EString::loot_filter_name_list.push_back(UTF8_to_ANSI(p.path().filename().u8string().substr(0, p.path().filename().u8string().length() - 7)));

				//std::cout << "It filter! " << p.path().filename().u8string() << '\n' << '\n';

				//ESound::custom_drop_sound.push_back(ESound::engine->addSoundSourceFromFile(custom_sound.c_str()));
			}
		}
	}

	void ESound::load_custom_sound()
	{
		if (ESound::engine != NULL)
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

				ESound::custom_drop_sound_name.push_back(EString::UTF8_to_ANSI(p.path().filename().u8string()));
				//std::cout << "It sound! " << p.path().filename().u8string() << '\n' << '\n';

				if (ESound::engine != NULL)
				{ESound::custom_drop_sound.push_back(ESound::engine->addSoundSourceFromFile(custom_sound.c_str()));}
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
			(_s == "==") ||
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

	std::string EString::UTF8_to_ANSI(std::string _text, bool _debug)
	{
		char sInvalid[1024];
		strcpy_s(sInvalid, _text.c_str());
		//ÍÓÏÏÂÌÚ‡ËË

		int size = strlen(sInvalid) + 1;
		wchar_t* wsValid = new wchar_t[size];
		char* sValid = new char[size];

		MultiByteToWideChar(CP_UTF8, 0, sInvalid, -1, wsValid, size);
		WideCharToMultiByte(CP_ACP, NULL, wsValid, -1, sValid, size, NULL, NULL);

		//MultiByteToWideChar(CP_UTF8, 0, sInvalid, -1, wsValid, size);
		//WideCharToMultiByte(CP_ACP, NULL, wsValid, -1, sValid, size, NULL, NULL);
		/*if (_debug) std::cout << "### " << _text << std::endl;
		if (_debug) std::cout << "==== INPUT method: MB_COMPOSITE" << std::endl;
		MultiByteToWideChar(CP_UTF8, MB_COMPOSITE, sInvalid, -1, wsValid, size);
			WideCharToMultiByte(CP_ACP, WC_COMPOSITECHECK, wsValid, -1, sValid, size, NULL, NULL);
			if (_debug) std::cout << "convert from [" << _text << "] to [" << sValid << "] using method: {WC_COMPOSITECHECK}" << std::endl;
			
		MultiByteToWideChar(CP_UTF8, MB_COMPOSITE, sInvalid, -1, wsValid, size);
			WideCharToMultiByte(CP_ACP, WC_ERR_INVALID_CHARS, wsValid, -1, sValid, size, NULL, NULL);
			if (_debug) std::cout << "convert from [" << _text << "] to [" << sValid << "] using method: {WC_ERR_INVALID_CHARS}" << std::endl;
			
		MultiByteToWideChar(CP_UTF8, MB_COMPOSITE, sInvalid, -1, wsValid, size);
			WideCharToMultiByte(CP_ACP, WC_NO_BEST_FIT_CHARS, wsValid, -1, sValid, size, NULL, NULL);
			if (_debug) std::cout << "convert from [" << _text << "] to [" << sValid << "] using method: {WC_NO_BEST_FIT_CHARS}" << std::endl;

		if (_debug) std::cout << "==== INPUT method: MB_ERR_INVALID_CHARS" << std::endl;
		MultiByteToWideChar(CP_UTF8, MB_ERR_INVALID_CHARS, sInvalid, -1, wsValid, size);
			WideCharToMultiByte(CP_ACP, WC_COMPOSITECHECK, wsValid, -1, sValid, size, NULL, NULL);
			if (_debug) std::cout << "convert from [" << _text << "] to [" << sValid << "] using method: {WC_COMPOSITECHECK}" << std::endl;
			
		MultiByteToWideChar(CP_UTF8, MB_COMPOSITE, sInvalid, -1, wsValid, size);
			WideCharToMultiByte(CP_ACP, WC_ERR_INVALID_CHARS, wsValid, -1, sValid, size, NULL, NULL);
			if (_debug) std::cout << "convert from [" << _text << "] to [" << sValid << "] using method: {WC_ERR_INVALID_CHARS}" << std::endl;
			
		MultiByteToWideChar(CP_UTF8, MB_COMPOSITE, sInvalid, -1, wsValid, size);
			WideCharToMultiByte(CP_ACP, WC_NO_BEST_FIT_CHARS, wsValid, -1, sValid, size, NULL, NULL);
			if (_debug) std::cout << "convert from [" << _text << "] to [" << sValid << "] using method: {WC_NO_BEST_FIT_CHARS}" << std::endl;

		if (_debug) std::cout << "==== INPUT method: MB_PRECOMPOSED" << std::endl;
		MultiByteToWideChar(CP_UTF8, MB_PRECOMPOSED, sInvalid, -1, wsValid, size);
			WideCharToMultiByte(CP_ACP, WC_COMPOSITECHECK, wsValid, -1, sValid, size, NULL, NULL);
			if (_debug) std::cout << "convert from [" << _text << "] to [" << sValid << "] using method: {WC_COMPOSITECHECK}" << std::endl;
			
		MultiByteToWideChar(CP_UTF8, MB_COMPOSITE, sInvalid, -1, wsValid, size);
			WideCharToMultiByte(CP_ACP, WC_ERR_INVALID_CHARS, wsValid, -1, sValid, size, NULL, NULL);
			if (_debug) std::cout << "convert from [" << _text << "] to [" << sValid << "] using method: {WC_ERR_INVALID_CHARS}" << std::endl;
			
		MultiByteToWideChar(CP_UTF8, MB_COMPOSITE, sInvalid, -1, wsValid, size);
			WideCharToMultiByte(CP_ACP, WC_NO_BEST_FIT_CHARS, wsValid, -1, sValid, size, NULL, NULL);
			if (_debug) std::cout << "convert from [" << _text << "] to [" << sValid << "] using method: {WC_NO_BEST_FIT_CHARS}" << std::endl;

		if (_debug) std::cout << "==== INPUT method: MB_USEGLYPHCHARS" << std::endl;
		MultiByteToWideChar(CP_UTF8, MB_USEGLYPHCHARS, sInvalid, -1, wsValid, size);
			WideCharToMultiByte(CP_ACP, WC_COMPOSITECHECK, wsValid, -1, sValid, size, NULL, NULL);
			if (_debug) std::cout << "convert from [" << _text << "] to [" << sValid << "] using method: {WC_COMPOSITECHECK}" << std::endl;
			
		MultiByteToWideChar(CP_UTF8, MB_COMPOSITE, sInvalid, -1, wsValid, size);
			WideCharToMultiByte(CP_ACP, WC_ERR_INVALID_CHARS, wsValid, -1, sValid, size, NULL, NULL);
			if (_debug) std::cout << "convert from [" << _text << "] to [" << sValid << "] using method: {WC_ERR_INVALID_CHARS}" << std::endl;
			
		MultiByteToWideChar(CP_UTF8, MB_COMPOSITE, sInvalid, -1, wsValid, size);
			WideCharToMultiByte(CP_ACP, WC_NO_BEST_FIT_CHARS, wsValid, -1, sValid, size, NULL, NULL);
			if (_debug) std::cout << "convert from [" << _text << "] to [" << sValid << "] using method: {WC_NO_BEST_FIT_CHARS}" << std::endl;*/

		std::string _t = "";
		for (int i = 0; i < _text.length(); i++)
		{
			int inputed_c = (int)_text.at(i);


			if (inputed_c == 1025) { inputed_c = 168; }
			else
				if (inputed_c == 1105) { inputed_c = 184; }
				else
					if (inputed_c > 255) { inputed_c -= 848; }

			_t += (char)inputed_c;
		}

		return sValid;
	}

	std::string EString::to_cyryllic(std::string _text, bool _degub)
	{

		return _text;
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

		int data_order_start = 0;

		EButton* just_created_button = NULL;

		int explicit_group_id = -1;

		FilterBlock::base_data_button_collection_struct* just_created_base_data_registerer = NULL;

		std::string accumulated_operator = "";

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

						if (show_info_to_console) cout << "[" << std::to_string(parser_mode) << "]--- subdata:'" << subdata << "'" << endl;


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

									just_created_block->red_sockets_group = { 0,0,0,0,0 }; //.at(data_id) 18.02.2020 10:43:35
									just_created_block->green_sockets_group = { 0,0,0,0,0 };
									just_created_block->blue_sockets_group = { 0,0,0,0,0 };
									just_created_block->white_sockets_group = { 0,0,0,0,0 };
									just_created_block->abyss_sockets_group = { 0,0,0,0,0 };
									just_created_block->delve_sockets_group = { 0,0,0,0,0 };
								}

								if (subdata == "Hide")
								{
									just_created_block = new FilterBlock();
									StaticData::window_filter_block->filter_block_list.push_back(just_created_block);
									parser_mode = Enums::ParserMode::HIDE;
									if (show_info_to_console) { cout << "And new block is created! And block is HIDED!" << endl; }

									just_created_block->is_show = false;

									explicit_group_id = -1;

									just_created_block->red_sockets_group = { 0,0,0,0,0 }; //.at(data_id) 18.02.2020 10:43:35
									just_created_block->green_sockets_group = { 0,0,0,0,0 };
									just_created_block->blue_sockets_group = { 0,0,0,0,0 };
									just_created_block->white_sockets_group = { 0,0,0,0,0 };
									just_created_block->abyss_sockets_group = { 0,0,0,0,0 };
									just_created_block->delve_sockets_group = { 0,0,0,0,0 };
								}

								if (subdata == "Continue")
								{
									just_created_block->is_continue = true;
									just_created_block->link_to_continue_button->gabarite = DefaultGabarite::gabarite_button_continue_on;

									parser_mode = Enums::ParserMode::CONTINUE;
								}

								if (subdata == "Corrupted")
								{
									parser_mode = Enums::ParserMode::IS_CORRUPTED; 
								}
								
								if (subdata == "AlternateQuality")
								{
									parser_mode = Enums::ParserMode::ALTERNATIVE_QUALITY;
									//just_created_block->base_filter_data_active.at(Enums::BaseDataOrder::DATA_ALTERNATE_QUALITY) = true;
								}
							
								if (subdata == "Replica")
								{
									parser_mode = Enums::ParserMode::IS_REPLICA;
									//just_created_block->base_filter_data_active.at(Enums::BaseDataOrder::DATA_IS_REPLICA) = true;
								}
								
								if (subdata == "CorruptedMods")
								{
									parser_mode = Enums::ParserMode::CORRUPTED_MODS;
									just_created_base_data_registerer = FilterBlock::add_new_base_attribute("CorruptedMods", just_created_block);
								}

								if (subdata == "LinkedSockets")
								{
									parser_mode = Enums::ParserMode::LINKED_SOCKETS;
									just_created_base_data_registerer = FilterBlock::add_new_base_attribute("LinkedSockets", just_created_block);
								}

								if (subdata == "Rarity")
								{
									parser_mode = Enums::ParserMode::RARITY;
									just_created_base_data_registerer = FilterBlock::add_new_base_attribute("Rarity", just_created_block);
								}

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

								if (subdata == "EnchantmentPassiveNode")
								{
									//std::cout << "Try get acess to remove button" << std::endl;

									parser_mode = Enums::ParserMode::CLUSTER_ENCHANTMENT;

									just_created_block->is_cluster_enchantment_active = true;
									just_created_block->plus_cluster_enchantment_button_link->is_active = true;
									just_created_block->remove_cluster_enchantment_button->is_active = true;
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

								if (subdata == "ShaperItem")
								{
									parser_mode = Enums::ParserMode::IS_SHAPER_ITEM;
									//just_created_block->base_filter_data_active.at(Enums::BaseDataOrder::DATA_SHAPER) = true;
								}
								
								if (subdata == "HasInfluence")
								{
									parser_mode = Enums::ParserMode::IS_HAVE_INFLUENCE_OR;

									just_created_block->influence_mode = FilterBlock::InfluenceMode::IM_ONE_OF;
									just_created_block->link_to_all_or_oneof->bg_color->set(EColorCollection::WHITE);
									just_created_block->link_to_all_or_oneof->text_color->set(EColorCollection::BLACK);

									for (EButton* b : just_created_block->influences_button_list)
									{
										b->is_active = true;
									}
								}
								
								if (subdata == "ItemLevel")
								{
									parser_mode = Enums::ParserMode::ITEM_LEVEL;
									//just_created_block->base_filter_data_active.at(Enums::BaseDataOrder::DATA_ITEM_LEVEL) = true;
									just_created_base_data_registerer = FilterBlock::add_new_base_attribute("ItemLevel", just_created_block);
								}

								if (subdata == "HasExplicitMod")
								{
									parser_mode = Enums::ParserMode::EXPLICIT_MOD; explicit_group_id++;
									just_created_block->is_explicit = true;
								}

								if (subdata == "Identified")
								{
									parser_mode = Enums::ParserMode::IDENTIFIED;
									//just_created_block->is_identified_active = true;
								}

								if (subdata == "ElderItem")
								{
									parser_mode = Enums::ParserMode::IS_ELDER_ITEM;
									//just_created_block->base_filter_data_active.at(Enums::BaseDataOrder::DATA_ELDER) = true;
								}

								if (subdata == "Sockets")
								{
									parser_mode = Enums::ParserMode::SOCKETS;
									accumulated_operator = "=";
									//just_created_block->base_filter_data_active.at(Enums::BaseDataOrder::DATA_SOCKETS) = true;
									//data_order_start = 1;
								}

								if (subdata == "FracturedItem")
								{
									parser_mode = Enums::ParserMode::IS_FRACTURED_ITEM;
									//just_created_block->base_filter_data_active.at(Enums::BaseDataOrder::DATA_FRACTURED) = true;
}
								if (subdata == "DropLevel")
								{
									parser_mode = Enums::ParserMode::DROP_LEVEL;
									//just_created_block->base_filter_data_active.at(Enums::BaseDataOrder::DATA_REQUIRED_LEVEL) = true;
									just_created_base_data_registerer = FilterBlock::add_new_base_attribute("DropLevel", just_created_block);
								}

								if (subdata == "Width")
								{
									parser_mode = Enums::ParserMode::WIDTH;
									//just_created_block->base_filter_data_active.at(Enums::BaseDataOrder::DATA_WIDTH) = true;
									just_created_base_data_registerer = FilterBlock::add_new_base_attribute("Width", just_created_block);
								}
								if (subdata == "Height")
								{
									parser_mode = Enums::ParserMode::HEIGHT;
									//just_created_block->base_filter_data_active.at(Enums::BaseDataOrder::DATA_HEIGHT) = true;
									just_created_base_data_registerer = FilterBlock::add_new_base_attribute("Height", just_created_block);
								}

								if (subdata == "SynthesisedItem")
								{
									parser_mode = Enums::ParserMode::IS_SYNTHESISED_ITEM;
									//just_created_block->base_filter_data_active.at(Enums::BaseDataOrder::DATA_SYNTHESISED) = true;
								}

								if (subdata == "AnyEnchantment")
								{
									parser_mode = Enums::ParserMode::IS_ANY_ENCHANTMENT;
									just_created_block->base_filter_data_active.at(Enums::BaseDataOrder::DATA_ENCHANTMENT) = true;
								}

								if (subdata == "Quality")
								{
									parser_mode = Enums::ParserMode::QUALITY;
									//just_created_block->base_filter_data_active.at(Enums::BaseDataOrder::DATA_QUALITY) = true;
									just_created_base_data_registerer = FilterBlock::add_new_base_attribute("Quality", just_created_block);
								}
								
								if (subdata == "SocketGroup")
								{
									parser_mode = Enums::ParserMode::SOCKET_GROUP;
									accumulated_operator = "=";
									//just_created_block->base_filter_data_active.at(Enums::BaseDataOrder::DATA_SOCKET_GROUP) = true;
									//data_order_start = 1;
								}
								
								if (subdata == "StackSize")
								{
									parser_mode = Enums::ParserMode::STACK_SIZE;
									//just_created_block->base_filter_data_active.at(Enums::BaseDataOrder::DATA_STACK_SIZE) = true;
									just_created_base_data_registerer = FilterBlock::add_new_base_attribute("StackSize", just_created_block);
								}

								if (subdata == "GemLevel")
								{
									parser_mode = Enums::ParserMode::GEM_LEVEL;
									//just_created_block->base_filter_data_active.at(Enums::BaseDataOrder::DATA_GEM_LEVEL) = true;
									just_created_base_data_registerer = FilterBlock::add_new_base_attribute("GemLevel", just_created_block);
								}

								if (subdata == "ElderMap")
								{
									parser_mode = Enums::ParserMode::IS_ELDER_MAP;
									//just_created_block->base_filter_data_active.at(Enums::BaseDataOrder::DATA_ELDER_MAP) = true;
								}

								if (subdata == "ShapedMap")
								{
									parser_mode = Enums::ParserMode::IS_SHAPER_MAP;
									//just_created_block->base_filter_data_active.at(Enums::BaseDataOrder::DATA_SHAPER_MAP) = true;
								}
								if (subdata == "MapTier")
								{
									parser_mode = Enums::ParserMode::MAP_TIER;
									//just_created_block->base_filter_data_active.at(Enums::BaseDataOrder::DATA_MAP_TIER) = true;
									just_created_base_data_registerer = FilterBlock::add_new_base_attribute("MapTier", just_created_block);
								}

								if (subdata == "DisableDropSound") { parser_mode = Enums::ParserMode::DISABLE_DROP_SOUND;  just_created_block->disable_drop_sound = true;}
								if (subdata == "DisableDropSoundIfAlertSound") { parser_mode = Enums::ParserMode::DISABLE_DROP_SOUND_IF_ALERT_SOUND;  just_created_block->disable_drop_sound_if_alert_sound = true;}
								if (subdata == "EnableDropSoundIfAlertSound") { parser_mode = Enums::ParserMode::ENABLE_DROP_SOUND_IF_ALERT_SOUND;  just_created_block->enable_drop_sound_if_alert_sound = true;}


								if (subdata == "Prophecy")
								{
									parser_mode = Enums::ParserMode::PROPHECY;
									just_created_block->is_prophecy_active = true;

									just_created_block->plus_prophecy_button_link->is_active = true;
									just_created_block->remove_prophecy_button->is_active = true;
								}

								if (subdata == "BlightedMap")
								{
									parser_mode = Enums::ParserMode::IS_BLIGHTED_MAP;
									//just_created_block->base_filter_data_active.at(Enums::BaseDataOrder::DATA_BLIGHTED) = true;
								}

								if (subdata == "Mirrored")
								{
									parser_mode = Enums::ParserMode::IS_MIRRORED;
									//just_created_block->base_filter_data_active.at(Enums::BaseDataOrder::DATA_MIRRORED_ITEM) = true; 
								}

								if (subdata == "AreaLevel")
								{
									parser_mode = Enums::ParserMode::AREA_LEVEL;
									//just_created_block->base_filter_data_active.at(Enums::BaseDataOrder::DATA_AREA_LEVEL) = true;
									just_created_base_data_registerer = FilterBlock::add_new_base_attribute("AreaLevel", just_created_block);

								}

								if (subdata == "EnchantmentPassiveNum")
								{
										parser_mode = Enums::ParserMode::CLUSTER_PASSIVES_COUNT;
										//just_created_block->base_filter_data_active.at(Enums::BaseDataOrder::DATA_AREA_LEVEL) = true;
										just_created_base_data_registerer = FilterBlock::add_new_base_attribute("EnchantmentPassiveNum", just_created_block);
								}

								if (subdata == "GemQualityType")
								{
										parser_mode = Enums::ParserMode::ALTERNATE_QUALITY_TYPE;
										//just_created_block->base_filter_data_active.at(Enums::BaseDataOrder::DATA_AREA_LEVEL) = true;
										just_created_base_data_registerer = FilterBlock::add_new_base_attribute("GemQualityType", just_created_block);
								}

								if (subdata == "BaseDefencePercentile")
								{
										parser_mode = Enums::ParserMode::BASE_DEFENCE_PERCENTILE;
										//just_created_block->base_filter_data_active.at(Enums::BaseDataOrder::DATA_AREA_LEVEL) = true;
										just_created_base_data_registerer = FilterBlock::add_new_base_attribute("BaseDefencePercentile", just_created_block);
								}

								if (subdata == "Scourged")
								{
									parser_mode = Enums::ParserMode::IS_SCOURGED;
									//just_created_block->base_filter_data_active.at(Enums::BaseDataOrder::DATA_MIRRORED_ITEM) = true; 
								}

								if (subdata == "UberBlightedMap")
								{
									parser_mode = Enums::ParserMode::IS_UBER_BLIGHT_MAP;
									//just_created_block->base_filter_data_active.at(Enums::BaseDataOrder::DATA_MIRRORED_ITEM) = true; 
								}
								//if (subdata == "EnchantmentPassiveNode") { parser_mode = Enums::ParserMode::CLUSTER_ENCHANTMENT; }
							}
							else
							{
								//cout << "comment data: " << subdata << endl;
								/*if (subdata == "#separator")
								{
									parser_mode = Enums::ParserMode::C_SEPARATOR;

									just_created_separator = new FilterBlockSeparator();
									StaticData::window_filter_block->separator_list.push_back(just_created_separator);


								}*/

								if (subdata == "#header_separator")
								{
									//cout << "SEPARATOR " << subdata << endl;

									for (EButton* b : just_created_block->header_button_list)
									{
										b->is_active = true;
									}

									parser_mode = Enums::ParserMode::C_SEPARATOR;
								}

								if (subdata == "#block_is_disabled")
								{
									just_created_block->disabled = true;
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
								/*if (data_order == 0) {
									just_created_block->link_to_header_separator->is_active = true;
									just_created_block->link_to_header_collapse_separator->is_active = true;
									just_created_block->link_to_header_destroy_separator->is_active = true;
								}*/
								if (data_order == 1) { just_created_block->link_to_header_separator->text = subdata; }

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

									if (EString::convert_text_to_bool(subdata))
									{ 
										just_created_block->special_status_button_list.at(FilterBlock::SpecialStatusList::SSL_CORRUPTED)->gabarite
										= DefaultGabarite::gabarite_switcher_vaaled;

										just_created_block->vector_special_status.at(FilterBlock::SpecialStatusList::SSL_CORRUPTED)
										= FilterBlock::SpecialStatusMode::SSM_ON;
									}
									else
									{ 
										just_created_block->special_status_button_list.at(FilterBlock::SpecialStatusList::SSL_CORRUPTED)->gabarite
										= DefaultGabarite::gabarite_switcher_vaaled_off;

										just_created_block->vector_special_status.at(FilterBlock::SpecialStatusList::SSL_CORRUPTED)
										= FilterBlock::SpecialStatusMode::SSM_OFF;
									}
									//just_created_block->base_filter_data_bool.at(Enums::BoolData::BOOL_CORRUPTION) = EString::convert_text_to_bool(subdata);
								}
							}

							if (parser_mode == Enums::ParserMode::ALTERNATIVE_QUALITY)
							{
								if (data_order == 0)
								{
									if (show_info_to_console) { cout << "activate alternate quality" << endl; }
								}

								if (data_order == 1)
								{
									if (show_info_to_console) { cout << "set alternate quality as as <" << subdata << ">" << endl; }
									//just_created_block->base_filter_data_bool.at(Enums::BoolData::BOOL_ALTERNATE_QUALITY) = EString::convert_text_to_bool(subdata);

									if (EString::convert_text_to_bool(subdata))
									{
										just_created_block->special_status_button_list.at(FilterBlock::SpecialStatusList::SSL_ALTERNATE_QUALITY)->gabarite
										= DefaultGabarite::gabarite_switcher_alternate_gem;

										just_created_block->vector_special_status.at(FilterBlock::SpecialStatusList::SSL_ALTERNATE_QUALITY)
										= FilterBlock::SpecialStatusMode::SSM_ON;
									}
									else
									{
										just_created_block->special_status_button_list.at(FilterBlock::SpecialStatusList::SSL_ALTERNATE_QUALITY)->gabarite
										= DefaultGabarite::gabarite_switcher_alternate_gem_off;

										just_created_block->vector_special_status.at(FilterBlock::SpecialStatusList::SSL_ALTERNATE_QUALITY)
										= FilterBlock::SpecialStatusMode::SSM_OFF;
									}
								}
							}

							if (parser_mode == Enums::ParserMode::IS_REPLICA)
							{
								if (data_order == 0)
								{
									if (show_info_to_console) { cout << "activate replica property" << endl; }
								}

								if (data_order == 1)
								{
									if (show_info_to_console) { cout << "set replica as <" << subdata << ">" << endl; }
									//just_created_block->base_filter_data_bool.at(Enums::BoolData::BOOL_REPLICA) = EString::convert_text_to_bool(subdata);

									
									if (EString::convert_text_to_bool(subdata))
									{
										just_created_block->special_status_button_list.at(FilterBlock::SpecialStatusList::SSL_REPLICA)->gabarite
										= DefaultGabarite::gabarite_switcher_replica;

										just_created_block->vector_special_status.at(FilterBlock::SpecialStatusList::SSL_REPLICA)
										= FilterBlock::SpecialStatusMode::SSM_ON;
									}
									else
									{
										just_created_block->special_status_button_list.at(FilterBlock::SpecialStatusList::SSL_REPLICA)->gabarite
										= DefaultGabarite::gabarite_switcher_replica_off;

										just_created_block->vector_special_status.at(FilterBlock::SpecialStatusList::SSL_REPLICA)
										= FilterBlock::SpecialStatusMode::SSM_OFF;
									}
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
									//if (just_created_base_data_registerer->main_button != NULL)
									//{just_created_base_data_registerer->main_button->text = subdata;}

									//if (just_created_base_data_registerer->condition_button != NULL)
									//{just_created_base_data_registerer->condition_button->text = subdata;}

									if (just_created_base_data_registerer->main_button != NULL)
									{just_created_base_data_registerer->main_button->text = subdata;}

									if (just_created_base_data_registerer->condition_button != NULL)
									{just_created_base_data_registerer->condition_button->text = "=";}
								}

								if ((data_order == 1) && (EString::check_is_condition_symbols(subdata)))
								{
									if (show_info_to_console) { cout << "set links condition as <" << subdata << ">" << endl; }
									//just_created_block->links_condition = subdata;
									if (just_created_base_data_registerer->condition_button != NULL)
									{just_created_base_data_registerer->condition_button->text = subdata;}
								}

								if (data_order == 2)
								{
									if (show_info_to_console) { cout << "set links as <" << subdata << ">" << endl; }
									//just_created_block->links_count = std::stoi(subdata);

									if (just_created_base_data_registerer->main_button != NULL)
									{just_created_base_data_registerer->main_button->text = subdata;}
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
									//just_created_block->item_rarity = subdata;
									//just_created_block->rarity_condition = "=";

									if (just_created_base_data_registerer->main_button != NULL)
									{just_created_base_data_registerer->main_button->text = subdata;}

									if (just_created_base_data_registerer->condition_button != NULL)
									{just_created_base_data_registerer->condition_button->text = "=";}

									if (EString::to_lower(subdata) == "normal") { just_created_base_data_registerer->main_button->selected_element = 0; }
									if (EString::to_lower(subdata) == "magic") { just_created_base_data_registerer->main_button->selected_element = 1; }
									if (EString::to_lower(subdata) == "rare") { just_created_base_data_registerer->main_button->selected_element = 2; }
									if (EString::to_lower(subdata) == "unique") { just_created_base_data_registerer->main_button->selected_element = 3; }
								}

								if ((data_order == 1) && (EString::check_is_condition_symbols(subdata)))
								{
									if (show_info_to_console) { cout << "set rarity condition as <" << subdata << ">" << endl; }
									//just_created_block->rarity_condition = subdata;
									if (just_created_base_data_registerer->condition_button != NULL)
									{just_created_base_data_registerer->condition_button->text = subdata;}


								}

								if (data_order == 2)
								{
									if (show_info_to_console) { cout << "set rarity as <" << subdata << ">" << endl; }
									//just_created_block->item_rarity = subdata;
									if (just_created_base_data_registerer->main_button != NULL)
									{
										just_created_base_data_registerer->main_button->text = subdata;

										if (EString::to_lower(subdata) == "normal")		{ just_created_base_data_registerer->main_button->selected_element = 0;}
										if (EString::to_lower(subdata) == "magic")		{ just_created_base_data_registerer->main_button->selected_element = 1;}
										if (EString::to_lower(subdata) == "rare")		{ just_created_base_data_registerer->main_button->selected_element = 2;}
										if (EString::to_lower(subdata) == "unique")		{ just_created_base_data_registerer->main_button->selected_element = 3;}
									}
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

							if (parser_mode == Enums::ParserMode::CLUSTER_ENCHANTMENT)
							{
								//if (data_order == 0) { cout << "activate rarity property" << endl; }
								if (data_order > 0)
								{
									if (show_info_to_console) { cout << "add new cluster enchantment <" << subdata << ">" << endl; }
									//just_created_block->class_list.push_back(new string(subdata));

									if (subdata != "=" & subdata != "==")
									{
										EButtonExplicit* enchantment_button = new EButtonExplicit(0, 0, 100, 20, Enums::ButtonType::BUTTON_CLUSTER_ENCHANTMENT_FILTER_BLOCK_LIST);
										enchantment_button->text = subdata;
										enchantment_button->data_string = subdata;

										enchantment_button->master_block = just_created_block;
										enchantment_button->master_window = StaticData::window_filter_block;


										just_created_block->button_list.push_back(enchantment_button);
										just_created_block->cluster_enchantment_list.push_back(enchantment_button);

										enchantment_button->data_id = -1;


										for (int i = 0; i < EString::cluster_enchantment_list.size(); i++)
										{
											if ((EString::to_lower(subdata, false) == EString::to_lower(EString::cluster_enchantment_list.at(i)->name, false)) && (enchantment_button->data_id == -1))
											{
												enchantment_button->data_id = i;

												if (EString::active_localisation == Enums::LocalisationList::EN)
												{
													enchantment_button->text = EString::cluster_enchantment_list.at(i)->name;
												}

												if (EString::active_localisation == Enums::LocalisationList::RU)
												{
													enchantment_button->text = EString::cluster_enchantment_list.at(i)->ru_name;
												}
											}
										}

										//class_button->text += " (" + std::to_string(class_button->data_id) + ")";

										enchantment_button->button_size_x = EFont::get_width(EFont::active_font, enchantment_button->text) + 5.0f;
										enchantment_button->button_min_size_x = 30.0f;
									
									}
								
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
									if (subdata == "Red") { just_created_block->minimap_icon_color = Enums::IconColor::RED; }
									if (subdata == "Green") { just_created_block->minimap_icon_color = Enums::IconColor::GREEN; }
									if (subdata == "Blue") { just_created_block->minimap_icon_color = Enums::IconColor::BLUE; }

									//if (subdata == "Brown") { just_created_block->minimap_icon_color = Enums::IconColor::BROWN; }
									if (subdata == "White") { just_created_block->minimap_icon_color = Enums::IconColor::WHITE; }
									if (subdata == "Yellow") { just_created_block->minimap_icon_color = Enums::IconColor::YELLOW; }
									if (subdata == "Cyan") { just_created_block->minimap_icon_color = Enums::IconColor::CYAN; }

									if (subdata == "Grey") { just_created_block->minimap_icon_color = Enums::IconColor::GREY; }
									if (subdata == "Orange") { just_created_block->minimap_icon_color = Enums::IconColor::ORANGE; }
									if (subdata == "Pink") { just_created_block->minimap_icon_color = Enums::IconColor::PINK; }

									if (subdata == "Purple") { just_created_block->minimap_icon_color = Enums::IconColor::PURPLE; }
								}

								if (data_order == 3)
								{
									if (subdata == "Circle") { just_created_block->minimap_icon_shape = Enums::IconShape::CIRCLE; }
									if (subdata == "Diamond") { just_created_block->minimap_icon_shape = Enums::IconShape::DIAMOND; }
									if (subdata == "Hexagon") { just_created_block->minimap_icon_shape = Enums::IconShape::HEXAGON; }
									if (subdata == "Square") { just_created_block->minimap_icon_shape = Enums::IconShape::SQUARE; }
									if (subdata == "Star") { just_created_block->minimap_icon_shape = Enums::IconShape::STAR; }
									if (subdata == "Triangle") { just_created_block->minimap_icon_shape = Enums::IconShape::TRIANGLE; }

									if (subdata == "Cross") { just_created_block->minimap_icon_shape = Enums::IconShape::CROSS; }
									if (subdata == "Moon") { just_created_block->minimap_icon_shape = Enums::IconShape::MOON; }
									if (subdata == "Raindrop") { just_created_block->minimap_icon_shape = Enums::IconShape::RAINDROP; }
									if (subdata == "Kite") { just_created_block->minimap_icon_shape = Enums::IconShape::KITE; }
									if (subdata == "Pentagon") { just_created_block->minimap_icon_shape = Enums::IconShape::PENTAGON; }
									if (subdata == "UpsideDownHouse") { just_created_block->minimap_icon_shape = Enums::IconShape::UPSIDEDOWNHOUSE; }
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

									just_created_block->is_exact_match = true;
									just_created_block->link_to_switch_exact_match->update_localisation();
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

									//((EButtonFilterItem*)just_created_button)->is_full_equal_mode = is_base_type_equal_mode;

									if (is_base_type_equal_mode)
									{
										//((EButtonFilterItem*)just_created_button)->change_color_cheme();
										just_created_button->rama_color->set(EColorCollection::PINK);
									}

									//just_created_button->
									just_created_block->filter_block_items_button_list.push_back(just_created_button);
								}
							}

							if (parser_mode == Enums::ParserMode::IS_SHAPER_ITEM)
							{
								if (data_order == 0) { if (show_info_to_console) { cout << "activate shaper item property" << endl; } }
								if (data_order == 1)
								{
									if (show_info_to_console)
									{
										cout << "set shaper item as <" << subdata << ">" << endl; }
										//just_created_block->base_filter_data_bool.at(Enums::BoolData::BOOL_SHAPER) = EString::convert_text_to_bool(subdata);

									if (just_created_block->influence_mode == FilterBlock::InfluenceMode::IM_IGNORE)
									{just_created_block->influence_mode = FilterBlock::InfluenceMode::IM_ONE_OF;}

									just_created_block->vector_influence.at(FilterBlock::InfluenceList::IL_SHAPER) = true;
									just_created_block->influences_button_list.at(FilterBlock::InfluenceList::IL_SHAPER)->gabarite = DefaultGabarite::gabarite_switcher_influence_shaper;
									just_created_block->influences_button_list.at(FilterBlock::InfluenceList::IL_SHAPER)->rama_color->set(EColorCollection::YELLOW);
									just_created_block->influences_button_list.at(FilterBlock::InfluenceList::IL_SHAPER)->bg_color->set(EColorCollection::WHITE);
								}
							}

							if (parser_mode == Enums::ParserMode::IS_HAVE_INFLUENCE_OR)
							{
								if (data_order == 0)
								{ 
									if (show_info_to_console) { cout << "activate shaper item property" << endl;}

									
								}

								if ((data_order == 1) && (subdata == "=="))
								{
								

									//parser_mode = Enums::ParserMode::IS_HAVE_INFLUENCE_AND;

									if (show_info_to_console) { cout << "change to AND mode. ID=" << std::to_string(parser_mode) << endl; }

									just_created_block->influence_mode = FilterBlock::InfluenceMode::IM_ALL;
									just_created_block->link_to_all_or_oneof->bg_color->set(EColorCollection::WHITE);
									just_created_block->link_to_all_or_oneof->text_color->set(EColorCollection::BLACK);

									for (EButton* b : just_created_block->influences_button_list)
									{
										b->is_active = true;
									}
									//just_created_block->link_to_all_or_oneof->text = EString::localize_it("influence_all");;
								}

								if ((data_order > 0) && (EString::to_lower(subdata) == "shaper"))
								{
									{ cout << "set OR shaper item as <true>" << endl; }
								
									just_created_block->vector_influence.at(FilterBlock::InfluenceList::IL_SHAPER) = true;
									just_created_block->influences_button_list.at(FilterBlock::InfluenceList::IL_SHAPER)->gabarite = DefaultGabarite::gabarite_switcher_influence_shaper;
									just_created_block->influences_button_list.at(FilterBlock::InfluenceList::IL_SHAPER)->rama_color->set(EColorCollection::YELLOW);
									just_created_block->influences_button_list.at(FilterBlock::InfluenceList::IL_SHAPER)->bg_color->set(EColorCollection::WHITE);
									//just_created_block->base_filter_data_active.at(Enums::BaseDataOrder::DATA_OR_SHAPER) = true;
									//just_created_block->base_filter_data_bool.at(Enums::BoolData::BOOL_OR_SHAPER) = true;
								}

								if ((data_order > 0) && (EString::to_lower(subdata) == "elder"))
								{
									if (show_info_to_console) { cout << "set OR elder item as <true>" << endl; }

									just_created_block->vector_influence.at			(FilterBlock::InfluenceList::IL_ELDER) = true;
									just_created_block->influences_button_list.at	(FilterBlock::InfluenceList::IL_ELDER)->gabarite = DefaultGabarite::gabarite_switcher_influence_elder;
									just_created_block->influences_button_list.at	(FilterBlock::InfluenceList::IL_ELDER)->rama_color->set(EColorCollection::YELLOW);
									just_created_block->influences_button_list.at	(FilterBlock::InfluenceList::IL_ELDER)->bg_color->set(EColorCollection::WHITE);

								}

								if ((data_order > 0) && (EString::to_lower(subdata) == "crusader"))
								{
									if (show_info_to_console) { cout << "set OR Crusader item as <true>" << endl; }

									just_created_block->vector_influence.at			(FilterBlock::InfluenceList::IL_CRUSADER) = true;
									just_created_block->influences_button_list.at	(FilterBlock::InfluenceList::IL_CRUSADER)->gabarite = DefaultGabarite::gabarite_switcher_influence_crusader;
									just_created_block->influences_button_list.at	(FilterBlock::InfluenceList::IL_CRUSADER)->rama_color->set(EColorCollection::YELLOW);
									just_created_block->influences_button_list.at	(FilterBlock::InfluenceList::IL_CRUSADER)->bg_color->set(EColorCollection::WHITE);

								}

								if ((data_order > 0) && (EString::to_lower(subdata) == "redeemer"))
								{
									if (show_info_to_console) { cout << "set OR Redeemer item as <true>" << endl; }

									just_created_block->vector_influence.at			(FilterBlock::InfluenceList::IL_REDEEMER) = true;
									just_created_block->influences_button_list.at	(FilterBlock::InfluenceList::IL_REDEEMER)->gabarite = DefaultGabarite::gabarite_switcher_influence_redeemer;
									just_created_block->influences_button_list.at	(FilterBlock::InfluenceList::IL_REDEEMER)->rama_color->set(EColorCollection::YELLOW);
									just_created_block->influences_button_list.at	(FilterBlock::InfluenceList::IL_REDEEMER)->bg_color->set(EColorCollection::WHITE);

								}

								if ((data_order > 0) && (EString::to_lower(subdata) == "hunter"))
								{
									if (show_info_to_console) { cout << "set OR Hunter item as <true>" << endl; }

									just_created_block->vector_influence.at			(FilterBlock::InfluenceList::IL_HUNTER) = true;
									just_created_block->influences_button_list.at	(FilterBlock::InfluenceList::IL_HUNTER)->gabarite = DefaultGabarite::gabarite_switcher_influence_hunter;
									just_created_block->influences_button_list.at	(FilterBlock::InfluenceList::IL_HUNTER)->rama_color->set(EColorCollection::YELLOW);
									just_created_block->influences_button_list.at	(FilterBlock::InfluenceList::IL_HUNTER)->bg_color->set(EColorCollection::WHITE);


								}

								if ((data_order > 0) && (EString::to_lower(subdata) == "warlord"))
								{
									if (show_info_to_console) { cout << "set OR Warlord item as <true>" << endl; }

									just_created_block->vector_influence.at			(FilterBlock::InfluenceList::IL_WARLORD) = true;
									just_created_block->influences_button_list.at	(FilterBlock::InfluenceList::IL_WARLORD)->gabarite = DefaultGabarite::gabarite_switcher_influence_warlord;
									just_created_block->influences_button_list.at	(FilterBlock::InfluenceList::IL_WARLORD)->rama_color->set(EColorCollection::YELLOW);
									just_created_block->influences_button_list.at	(FilterBlock::InfluenceList::IL_WARLORD)->bg_color->set(EColorCollection::WHITE);
								}

								if ((data_order > 0) && (EString::to_lower(subdata) == "none"))
								{
									if (show_info_to_console) { cout << "set OR None item as <true>" << endl; }

									//just_created_block->link_to_all_or_oneof->text = EString::localize_it("influence_none");
									just_created_block->link_to_all_or_oneof->text_color->set(EColorCollection::WHITE);
									just_created_block->link_to_all_or_oneof->bg_color->set(EColorCollection::RED);

									just_created_block->influence_mode = FilterBlock::InfluenceMode::IM_NONE;

									/*
									for (bool infl : just_created_block->vector_influence)
									{
										infl = false;
									}

									for (EButton* b : just_created_block->influences_button_list)
									{
										b->bg_color->set(EColorCollection::DARK_GRAY);
									}*/
									for (EButton* b : just_created_block->influences_button_list)
									{
										b->is_active = false;
									}

									//just_created_block->link_to_all_or_oneof->text = EString::localize_it("influence_none");
								}
							}

							if (parser_mode == Enums::ParserMode::IS_HAVE_INFLUENCE_AND)
							{
								if ((data_order > 0) && (EString::to_lower(subdata) == "shaper"))
								{
									if (show_info_to_console) { cout << "set AND shaper item as <true>" << endl; }

									just_created_block->base_filter_data_active.at(Enums::BaseDataOrder::DATA_AND_SHAPER) = true;
									just_created_block->base_filter_data_bool.at(Enums::BoolData::BOOL_AND_SHAPER) = true;
								}

								if ((data_order > 0) && (EString::to_lower(subdata) == "elder"))
								{
									if (show_info_to_console) { cout << "set AND elder item as <true>" << endl; }

									just_created_block->base_filter_data_active.at(Enums::BaseDataOrder::DATA_AND_ELDER) = true;
									just_created_block->base_filter_data_bool.at(Enums::BoolData::BOOL_AND_ELDER) = true;
								}

								if ((data_order > 0) && (EString::to_lower(subdata) == "crusader"))
								{
									if (show_info_to_console) { cout << "set AND Crusader item as <true>" << endl; }

									just_created_block->base_filter_data_active.at(Enums::BaseDataOrder::DATA_AND_CRUSADER) = true;
									just_created_block->base_filter_data_bool.at(Enums::BoolData::BOOL_AND_CRUSADER) = true;
								}

								if ((data_order > 0) && (EString::to_lower(subdata) == "redeemer"))
								{
									if (show_info_to_console) { cout << "set AND Redeemer item as <true>" << endl; }

									just_created_block->base_filter_data_active.at(Enums::BaseDataOrder::DATA_AND_REDEEMER) = true;
									just_created_block->base_filter_data_bool.at(Enums::BoolData::BOOL_AND_REDEEMER) = true;
								}

								if ((data_order > 0) && (EString::to_lower(subdata) == "hunter"))
								{
									if (show_info_to_console) { cout << "set AND Hunter item as <true>" << endl; }

									just_created_block->base_filter_data_active.at(Enums::BaseDataOrder::DATA_AND_HUNTER) = true;
									just_created_block->base_filter_data_bool.at(Enums::BoolData::BOOL_AND_HUNTER) = true;
								}

								if ((data_order > 0) && (EString::to_lower(subdata) == "warlord"))
								{
									if (show_info_to_console) { cout << "set AND Warlord item as <true>" << endl; }

									just_created_block->base_filter_data_active.at(Enums::BaseDataOrder::DATA_AND_WARLORD) = true;
									just_created_block->base_filter_data_bool.at(Enums::BoolData::BOOL_AND_WARLORD) = true;
								}


								if ((data_order > 0) && (EString::to_lower(subdata) == "none"))
								{
									if (show_info_to_console) { cout << "set AND none item as <true>" << endl; }

									just_created_block->base_filter_data_active.at(Enums::BaseDataOrder::DATA_NO_INFLUENCE_AND) = true;
									just_created_block->base_filter_data_bool.at(Enums::BoolData::BOOL_NO_INFLUENCE_AND) = true;
								}
							}

							if (parser_mode == Enums::ParserMode::ITEM_LEVEL)
							{
								if (data_order == 0) { if (show_info_to_console) { cout << "activate item level" << endl; } }


								if ((data_order == 1) && (!EString::check_is_condition_symbols(subdata)))
								{
									if (show_info_to_console) { cout << "set item level as <" << subdata << "> condition autogenerated" << endl; }
									//just_created_block->item_level = std::stoi(subdata); just_created_block->item_level_condition = "=";

									if (just_created_base_data_registerer->main_button != NULL)
									{just_created_base_data_registerer->main_button->text = subdata;}

									if (just_created_base_data_registerer->condition_button != NULL)
									{just_created_base_data_registerer->condition_button->text = "=";}
								
								}
								
								if ((data_order == 1) && (EString::check_is_condition_symbols(subdata)))
								{
									if (show_info_to_console) { cout << "set item level condition as <" << subdata << "> id of symbol=" << endl; }
									//just_created_block->item_level_condition = subdata;

									if (just_created_base_data_registerer->condition_button != NULL)
									{just_created_base_data_registerer->condition_button->text = subdata;}
								}

								if (data_order == 2)
								{
									if (show_info_to_console)
									{
										cout << "set item_level as <" << subdata << ">" << endl; }
									//just_created_block->item_level = std::stoi(subdata);

									if (just_created_base_data_registerer->main_button != NULL)
									{just_created_base_data_registerer->main_button->text = subdata;}
								}
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
								if (data_order == 1) { if (show_info_to_console)
								{
									cout << "set indetification as <" << subdata << ">" << endl; }
									//just_created_block->base_filter_data_bool.at(Enums::BaseDataOrder::DATA_IDENTIFIED) = EString::convert_text_to_bool(subdata);

								
									if (EString::convert_text_to_bool(subdata))
									{
										just_created_block->special_status_button_list.at(FilterBlock::SpecialStatusList::SSL_IDENTIFIED)->gabarite
										= DefaultGabarite::gabarite_switcher_identified;

										just_created_block->vector_special_status.at(FilterBlock::SpecialStatusList::SSL_IDENTIFIED)
										= FilterBlock::SpecialStatusMode::SSM_ON;
									}
									else
									{
										just_created_block->special_status_button_list.at(FilterBlock::SpecialStatusList::SSL_IDENTIFIED)->gabarite
										= DefaultGabarite::gabarite_switcher_identified_off;

										just_created_block->vector_special_status.at(FilterBlock::SpecialStatusList::SSL_IDENTIFIED)
										= FilterBlock::SpecialStatusMode::SSM_OFF;
									}
								}
							}

							if (parser_mode == Enums::ParserMode::IS_ELDER_ITEM)
							{
								if (data_order == 0) { if (show_info_to_console) { cout << "activate elder item property" << endl; } }
								if (data_order == 1)
								{
									if (show_info_to_console)
									{
										cout << "set elder item as <" << subdata << ">" << endl; }
									//just_created_block->base_filter_data_bool.at(Enums::BoolData::BOOL_ELDER) = EString::convert_text_to_bool(subdata);

									if (just_created_block->influence_mode == FilterBlock::InfluenceMode::IM_IGNORE)
									{just_created_block->influence_mode = FilterBlock::InfluenceMode::IM_ONE_OF;}

									just_created_block->vector_influence.at(FilterBlock::InfluenceList::IL_ELDER) = true;
									just_created_block->influences_button_list.at(FilterBlock::InfluenceList::IL_ELDER)->gabarite = DefaultGabarite::gabarite_switcher_influence_elder;
									just_created_block->influences_button_list.at(FilterBlock::InfluenceList::IL_ELDER)->rama_color->set(EColorCollection::YELLOW);
									just_created_block->influences_button_list.at(FilterBlock::InfluenceList::IL_ELDER)->bg_color->set(EColorCollection::WHITE);
								}
							}

							if (parser_mode == Enums::ParserMode::DROP_LEVEL)
							{
								if (data_order == 0) { if (show_info_to_console) { cout << "activate required level" << endl; } }


								if ((data_order == 1) && (!EString::check_is_condition_symbols(subdata)))
								{
									if (show_info_to_console)
									{
										cout << "set required level as <" << subdata << "> condition autogenerated" << endl; }
									//just_created_block->required_level = std::stoi(subdata); just_created_block->required_level_condition = "=";

									if (just_created_base_data_registerer->main_button != NULL)
									{just_created_base_data_registerer->main_button->text = subdata;}

									if (just_created_base_data_registerer->condition_button != NULL)
									{just_created_base_data_registerer->condition_button->text = "=";}
								}

								if ((data_order == 1) && (EString::check_is_condition_symbols(subdata)))
								{
									if (show_info_to_console) { cout << "set required level condition as <" << subdata << "> id of symbol="  << endl; }
									//just_created_block->required_level_condition = subdata;

									if (just_created_base_data_registerer->condition_button != NULL)
									{just_created_base_data_registerer->condition_button->text = subdata;}
								}

								if (data_order == 2)
								{
									if (show_info_to_console){ cout << "set required level as <" << subdata << ">" << endl; }
									//just_created_block->required_level = std::stoi(subdata);

									if (just_created_base_data_registerer->main_button != NULL)
									{just_created_base_data_registerer->main_button->text = subdata;}
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
									//just_created_block->item_width = std::stoi(subdata);
									//just_created_block->item_width_condition = "=";

									if (just_created_base_data_registerer->main_button != NULL)
									{just_created_base_data_registerer->main_button->text = subdata;}

									if (just_created_base_data_registerer->condition_button != NULL)
									{just_created_base_data_registerer->condition_button->text = "=";}
								}

								if ((data_order == 1) && (EString::check_is_condition_symbols(subdata)))
								{
									if (show_info_to_console) { cout << "set width condition as <" << subdata << ">" << endl; }
									//just_created_block->item_width_condition = subdata;

									if (just_created_base_data_registerer->condition_button != NULL)
									{just_created_base_data_registerer->condition_button->text = subdata;}


								}

								if (data_order == 2)
								{
									if (show_info_to_console) { cout << "set width as <" << subdata << ">" << endl; }
									//just_created_block->item_width = std::stoi(subdata);

									if (just_created_base_data_registerer->main_button != NULL)
									{just_created_base_data_registerer->main_button->text = subdata;}
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
									//just_created_block->item_height = std::stoi(subdata);
									//just_created_block->item_height_condition = "=";

									if (just_created_base_data_registerer->main_button != NULL)
									{just_created_base_data_registerer->main_button->text = subdata;}

									if (just_created_base_data_registerer->condition_button != NULL)
									{just_created_base_data_registerer->condition_button->text = "=";}
								}

								if ((data_order == 1) && (EString::check_is_condition_symbols(subdata)))
								{
									if (show_info_to_console) { cout << "set height condition as <" << subdata << ">" << endl; }
									//just_created_block->item_height_condition = subdata;

									if (just_created_base_data_registerer->condition_button != NULL)
									{just_created_base_data_registerer->condition_button->text = subdata;}
								}

								if (data_order == 2)
								{
									if (show_info_to_console) { cout << "set height as <" << subdata << ">" << endl; }
									//just_created_block->item_height = std::stoi(subdata);

									if (just_created_base_data_registerer->main_button != NULL)
									{just_created_base_data_registerer->main_button->text = subdata;}
								}
							}

							if (parser_mode == Enums::ParserMode::IS_FRACTURED_ITEM)
							{
								if (data_order == 0) { if (show_info_to_console) { cout << "activate fractured item property" << endl; } }
								if (data_order == 1)
								{
									if (show_info_to_console){ cout << "set fractured item as <" << subdata << ">" << endl; }
									//just_created_block->base_filter_data_bool.at(Enums::BoolData::BOOL_FRACTURED) = EString::convert_text_to_bool(subdata);

									
									if (EString::convert_text_to_bool(subdata))
									{
										just_created_block->special_status_button_list.at(FilterBlock::SpecialStatusList::SSL_FRACTURED)->gabarite
										= DefaultGabarite::gabarite_switcher_fractured;

										just_created_block->vector_special_status.at(FilterBlock::SpecialStatusList::SSL_FRACTURED)
										= FilterBlock::SpecialStatusMode::SSM_ON;
									}
									else
									{
										just_created_block->special_status_button_list.at(FilterBlock::SpecialStatusList::SSL_FRACTURED)->gabarite
										= DefaultGabarite::gabarite_switcher_fractured_off;

										just_created_block->vector_special_status.at(FilterBlock::SpecialStatusList::SSL_FRACTURED)
										= FilterBlock::SpecialStatusMode::SSM_OFF;
									}
								}
							}

							if (parser_mode == Enums::ParserMode::IS_SYNTHESISED_ITEM)
							{
								if (data_order == 0) { if (show_info_to_console) { cout << "activate synthesised item property" << endl; } }
								if (data_order == 1) { if (show_info_to_console)
								{
									cout << "set synthesised item as <" << subdata << ">" << endl; }
									//just_created_block->base_filter_data_bool.at(Enums::BoolData::BOOL_SYNTHESISED) = EString::convert_text_to_bool(subdata);


								if (EString::convert_text_to_bool(subdata))
								{
									just_created_block->special_status_button_list.at(FilterBlock::SpecialStatusList::SSL_SYNTHESISED)->gabarite
										= DefaultGabarite::gabarite_switcher_synthesised;

									just_created_block->vector_special_status.at(FilterBlock::SpecialStatusList::SSL_SYNTHESISED)
										= FilterBlock::SpecialStatusMode::SSM_ON;
								}
								else
								{
									just_created_block->special_status_button_list.at(FilterBlock::SpecialStatusList::SSL_SYNTHESISED)->gabarite
										= DefaultGabarite::gabarite_switcher_synthesised_off;

									just_created_block->vector_special_status.at(FilterBlock::SpecialStatusList::SSL_SYNTHESISED)
										= FilterBlock::SpecialStatusMode::SSM_OFF;
								}
								}
							}

							if (parser_mode == Enums::ParserMode::IS_BLIGHTED_MAP)
							{
								if (data_order == 0) { if (show_info_to_console) { cout << "activate blighted map property" << endl; } }
								if (data_order == 1)
								{
									if (show_info_to_console) { cout << "set blighted item as <" << subdata << ">" << endl; }
									//just_created_block->base_filter_data_bool.at(Enums::BoolData::BOOL_BLIGHTED) = EString::convert_text_to_bool(subdata);

									
									if (EString::convert_text_to_bool(subdata))
									{
										just_created_block->special_status_button_list.at(FilterBlock::SpecialStatusList::SSL_BLIGHTED)->gabarite
										= DefaultGabarite::gabarite_switcher_blighted;

										just_created_block->vector_special_status.at(FilterBlock::SpecialStatusList::SSL_BLIGHTED)
										= FilterBlock::SpecialStatusMode::SSM_ON;
									}
									else
									{
										just_created_block->special_status_button_list.at(FilterBlock::SpecialStatusList::SSL_BLIGHTED)->gabarite
										= DefaultGabarite::gabarite_switcher_blighted_off;

										just_created_block->vector_special_status.at(FilterBlock::SpecialStatusList::SSL_BLIGHTED)
										= FilterBlock::SpecialStatusMode::SSM_OFF;
									}
								}
							}

							if (parser_mode == Enums::ParserMode::IS_MIRRORED)
							{
								if (data_order == 0) { if (show_info_to_console) { cout << "activate mirrored item property" << endl; } }
								if (data_order == 1)
								{
									if (show_info_to_console) {cout << "set mirrored item as <" << subdata << ">" << endl; }
									//just_created_block->base_filter_data_bool.at(Enums::BoolData::BOOL_MIRRORED_ITEM) = EString::convert_text_to_bool(subdata);

									
									if (EString::convert_text_to_bool(subdata))
									{
										just_created_block->special_status_button_list.at(FilterBlock::SpecialStatusList::SSL_MIRRORED)->gabarite
										= DefaultGabarite::gabarite_switcher_mirrored;

										just_created_block->vector_special_status.at(FilterBlock::SpecialStatusList::SSL_MIRRORED)
										= FilterBlock::SpecialStatusMode::SSM_ON;
									}
									else
									{
										just_created_block->special_status_button_list.at(FilterBlock::SpecialStatusList::SSL_MIRRORED)->gabarite
										= DefaultGabarite::gabarite_switcher_mirrored_off;

										just_created_block->vector_special_status.at(FilterBlock::SpecialStatusList::SSL_MIRRORED)
										= FilterBlock::SpecialStatusMode::SSM_OFF;
									}
								}
							}

							if (parser_mode == Enums::ParserMode::IS_SCOURGED)
							{
								if (data_order == 0) { if (show_info_to_console) { cout << "activate scourged item property" << endl; } }
								if (data_order == 1)
								{
									if (show_info_to_console) {cout << "set scourged item as <" << subdata << ">" << endl; }
									//just_created_block->base_filter_data_bool.at(Enums::BoolData::BOOL_MIRRORED_ITEM) = EString::convert_text_to_bool(subdata);

									
									if (EString::convert_text_to_bool(subdata))
									{
										just_created_block->special_status_button_list.at(FilterBlock::SpecialStatusList::SSL_SCOURGED)->gabarite
										= DefaultGabarite::gabarite_switcher_scourged;

										just_created_block->vector_special_status.at(FilterBlock::SpecialStatusList::SSL_SCOURGED)
										= FilterBlock::SpecialStatusMode::SSM_ON;
									}
									else
									{
										just_created_block->special_status_button_list.at(FilterBlock::SpecialStatusList::SSL_SCOURGED)->gabarite
										= DefaultGabarite::gabarite_switcher_scourged_off;

										just_created_block->vector_special_status.at(FilterBlock::SpecialStatusList::SSL_SCOURGED)
										= FilterBlock::SpecialStatusMode::SSM_OFF;
									}
								}
							}

							if (parser_mode == Enums::ParserMode::IS_UBER_BLIGHT_MAP)
							{
								if (data_order == 0) { if (show_info_to_console) { cout << "activate uber blight item property" << endl; } }
								if (data_order == 1)
								{
									if (show_info_to_console) { cout << "set uber blight item as <" << subdata << ">" << endl; }
									//just_created_block->base_filter_data_bool.at(Enums::BoolData::BOOL_MIRRORED_ITEM) = EString::convert_text_to_bool(subdata);


									if (EString::convert_text_to_bool(subdata))
									{
										just_created_block->special_status_button_list.at(FilterBlock::SpecialStatusList::SSL_UBER_BLIGHT)->gabarite
											= DefaultGabarite::gabarite_switcher_uber_blight;

										just_created_block->vector_special_status.at(FilterBlock::SpecialStatusList::SSL_UBER_BLIGHT)
											= FilterBlock::SpecialStatusMode::SSM_ON;
									}
									else
									{
										just_created_block->special_status_button_list.at(FilterBlock::SpecialStatusList::SSL_UBER_BLIGHT)->gabarite
											= DefaultGabarite::gabarite_switcher_uber_blight_off;

										just_created_block->vector_special_status.at(FilterBlock::SpecialStatusList::SSL_UBER_BLIGHT)
											= FilterBlock::SpecialStatusMode::SSM_OFF;
									}
								}
							}

							if (parser_mode == Enums::ParserMode::IS_ANY_ENCHANTMENT)
							{
								if (data_order == 0) { if (show_info_to_console) { cout << "activate enchantment item property" << endl; } }
								if (data_order == 1)
								{
									if (show_info_to_console)
									{
										cout << "set enchantment item as <" << subdata << ">" << endl; }
										//just_created_block->base_filter_data_bool.at(Enums::BoolData::BOOL_ANY_ENCHANTMENT) = EString::convert_text_to_bool(subdata);

										if (EString::convert_text_to_bool(subdata))
										{
											just_created_block->special_status_button_list.at(FilterBlock::SpecialStatusList::SSL_ENCHANTED)->gabarite
											= DefaultGabarite::gabarite_switcher_enchant;

											just_created_block->vector_special_status.at(FilterBlock::SpecialStatusList::SSL_ENCHANTED)
											= FilterBlock::SpecialStatusMode::SSM_ON;
										}
										else
										{
											just_created_block->special_status_button_list.at(FilterBlock::SpecialStatusList::SSL_ENCHANTED)->gabarite
											= DefaultGabarite::gabarite_switcher_enchant_off;

											just_created_block->vector_special_status.at(FilterBlock::SpecialStatusList::SSL_ENCHANTED)
											= FilterBlock::SpecialStatusMode::SSM_OFF;
										}
									}
							}

							if (parser_mode == Enums::ParserMode::DISABLE_DROP_SOUND)
							{
								if (data_order == 0) { if (show_info_to_console) { cout << "activate disable drop sound" << endl; } }
								if (data_order == 1)
								{
									if (show_info_to_console)
									{
										cout << "set disable drop sound as <" << subdata << ">" << endl; }
										//just_created_block->base_filter_data_bool.at(Enums::BoolData::BOOL_ANY_ENCHANTMENT) = EString::convert_text_to_bool(subdata);

										if (EString::convert_text_to_bool(subdata))
										{
											just_created_block->disable_drop_sound = true;
										}
										else
										{
											just_created_block->disable_drop_sound = false;
										}
									}
							}

							if (parser_mode == Enums::ParserMode::DISABLE_DROP_SOUND_IF_ALERT_SOUND)
							{
								if (data_order == 0) { if (show_info_to_console) { cout << "activate disable drop sound" << endl; } }
								if (data_order == 1)
								{
									if (show_info_to_console)
									{
										cout << "set disable drop sound as <" << subdata << ">" << endl;
									}
									//just_created_block->base_filter_data_bool.at(Enums::BoolData::BOOL_ANY_ENCHANTMENT) = EString::convert_text_to_bool(subdata);

									if (EString::convert_text_to_bool(subdata))
									{
										just_created_block->disable_drop_sound_if_alert_sound = true;
									}
									else
									{
										just_created_block->disable_drop_sound_if_alert_sound = false;
									}
								}
							}

							if (parser_mode == Enums::ParserMode::ENABLE_DROP_SOUND_IF_ALERT_SOUND)
							{
								if (data_order == 0) { if (show_info_to_console) { cout << "activate disable drop sound" << endl; } }
								if (data_order == 1)
								{
									if (show_info_to_console)
									{
										cout << "set disable drop sound as <" << subdata << ">" << endl;
									}
									//just_created_block->base_filter_data_bool.at(Enums::BoolData::BOOL_ANY_ENCHANTMENT) = EString::convert_text_to_bool(subdata);

									if (EString::convert_text_to_bool(subdata))
									{
										just_created_block->enable_drop_sound_if_alert_sound = true;
									}
									else
									{
										just_created_block->enable_drop_sound_if_alert_sound = false;
									}
								}
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
									//just_created_block->item_quality = std::stoi(subdata);
									//just_created_block->item_quality_condition = "=";

									if (just_created_base_data_registerer->main_button != NULL)
									{just_created_base_data_registerer->main_button->text = subdata;}

									if (just_created_base_data_registerer->condition_button != NULL)
									{just_created_base_data_registerer->condition_button->text = "=";}
								}

								if ((data_order == 1) && (EString::check_is_condition_symbols(subdata)))
								{
									if (show_info_to_console) { cout << "set hqualityeight condition as <" << subdata << ">" << endl; }
									//just_created_block->item_quality_condition = subdata;

									if (just_created_base_data_registerer->condition_button != NULL)
									{just_created_base_data_registerer->condition_button->text = subdata;}
								}

								if (data_order == 2)
								{
									if (show_info_to_console) { cout << "set quality as <" << subdata << ">" << endl; }
									//just_created_block->item_quality = std::stoi(subdata);

									if (just_created_base_data_registerer->main_button != NULL)
									{just_created_base_data_registerer->main_button->text = subdata;}
								}
							}

							if (parser_mode == Enums::ParserMode::SOCKET_GROUP)
							{



								if (data_order == 0)
								{
									if (show_info_to_console) { cout << "activate socket group property" << endl; }
									
								}

								if ((data_order == 1) && (EString::check_is_condition_symbols(subdata)))
								{
									if (show_info_to_console) { cout << "set socket group condition as <" << subdata << ">" << endl; }

									accumulated_operator = subdata;
									//just_created_block->socket_group_condition = subdata;
									//data_order_start = 2;
								}

								if
								(
									(
										(data_order == 1)
										&&
										(!EString::check_is_condition_symbols(subdata))
									)
									||
									(data_order >= 2)
								)
								{
									/*
									for (int socket = 0; socket < subdata.length(); socket++)
									{
										if (subdata.at(socket) == '1') { just_created_block->socket_group_links.at(data_order - data_order_start) = 1; }
										if (subdata.at(socket) == '2') { just_created_block->socket_group_links.at(data_order - data_order_start) = 2; }
										if (subdata.at(socket) == '3') { just_created_block->socket_group_links.at(data_order - data_order_start) = 3; }
										if (subdata.at(socket) == '4') { just_created_block->socket_group_links.at(data_order - data_order_start) = 4; }
										if (subdata.at(socket) == '5') { just_created_block->socket_group_links.at(data_order - data_order_start) = 5; }
										if (subdata.at(socket) == '6') { just_created_block->socket_group_links.at(data_order - data_order_start) = 6; }

										if (subdata.at(socket) == 'R') { just_created_block->red_sockets_group.at(data_order - data_order_start)++; }
										if (subdata.at(socket) == 'G') { just_created_block->green_sockets_group.at(data_order - data_order_start)++; }
										if (subdata.at(socket) == 'B') { just_created_block->blue_sockets_group.at(data_order - data_order_start)++; }
										if (subdata.at(socket) == 'W') { just_created_block->white_sockets_group.at(data_order - data_order_start)++; }
										if (subdata.at(socket) == 'A') { just_created_block->abyss_sockets_group.at(data_order - data_order_start)++; }
										if (subdata.at(socket) == 'D') { just_created_block->delve_sockets_group.at(data_order - data_order_start)++; }
									}
									*/

									just_created_base_data_registerer = FilterBlock::add_new_base_attribute("SocketGroup", just_created_block);
									if (just_created_base_data_registerer->condition_button != NULL)
									{
										just_created_base_data_registerer->condition_button->text = accumulated_operator;
									}

									if (just_created_base_data_registerer->main_button != NULL)
									{
										just_created_base_data_registerer->main_button->text = subdata;
									}

									//{ cout << "set RED as <" << just_created_block->red_sockets.at(data_order - data_order_start) << "> set GREEN as <" << just_created_block->green_sockets.at(data_order - data_order_start) << "> set BLUE as <" << just_created_block->blue_sockets.at(data_order - data_order_start) << "> set WHITE as <" << just_created_block->white_sockets.at(data_order - data_order_start) << ">" << endl; }
									//if (show_info_to_console) { cout << "set RED as <" << just_created_block->red_sockets << "> set GREEN as <" << just_created_block->green_sockets << "> set BLUE as <" << just_created_block->blue_sockets << "> set WHITE as <" << just_created_block->white_sockets << ">" << endl; }
									//just_created_block->item_height = std::stoi(subdata);
									//just_created_block->item_height_condition = "=";
								}


							}

							if (parser_mode == Enums::ParserMode::SOCKETS)
							{
								if (data_order == 0)
								{
									if (show_info_to_console) { cout << "activate sockets property" << endl; }
									data_order_start = 1;
								}

								if ((data_order == 1) && (EString::check_is_condition_symbols(subdata)))
								{
									if (show_info_to_console) { cout << "set sockets condition as <" << subdata << ">" << endl; }
									//just_created_block->socket_condition = subdata;
									//data_order_start = 2;

									accumulated_operator = subdata;
								}

								if
								(
									(
										(data_order == 1)
										&&
										(!EString::check_is_condition_symbols(subdata))
									)
									||
									(data_order >= 2)
								)
								{

									/*for (int socket = 0; socket < subdata.length(); socket++)
									{
										if (subdata.at(socket) == '1') { just_created_block->socket_count.at(data_order - data_order_start) = 1; }
										if (subdata.at(socket) == '2') { just_created_block->socket_count.at(data_order - data_order_start) = 2; }
										if (subdata.at(socket) == '3') { just_created_block->socket_count.at(data_order - data_order_start) = 3; }
										if (subdata.at(socket) == '4') { just_created_block->socket_count.at(data_order - data_order_start) = 4; }
										if (subdata.at(socket) == '5') { just_created_block->socket_count.at(data_order - data_order_start) = 5; }
										if (subdata.at(socket) == '6') { just_created_block->socket_count.at(data_order - data_order_start) = 6; }

										if (subdata.at(socket) == 'R') { just_created_block->red_sockets.at(data_order - data_order_start)++; }
										if (subdata.at(socket) == 'G') { just_created_block->green_sockets.at(data_order - data_order_start)++; }
										if (subdata.at(socket) == 'B') { just_created_block->blue_sockets.at(data_order - data_order_start)++; }
										if (subdata.at(socket) == 'W') { just_created_block->white_sockets.at(data_order - data_order_start)++; }
										if (subdata.at(socket) == 'A') { just_created_block->abyss_sockets.at(data_order - data_order_start)++; }
										if (subdata.at(socket) == 'D') { just_created_block->delve_sockets.at(data_order - data_order_start)++; }
									}*/

									just_created_base_data_registerer = FilterBlock::add_new_base_attribute("Sockets", just_created_block);
									if (just_created_base_data_registerer->condition_button != NULL)
									{
										just_created_base_data_registerer->condition_button->text = accumulated_operator;
									}

									if (just_created_base_data_registerer->main_button != NULL)
									{
										just_created_base_data_registerer->main_button->text = subdata;
									}

									//{ cout << "set RED as <" << just_created_block->red_sockets.at(data_order - data_order_start) << "> set GREEN as <" << just_created_block->green_sockets.at(data_order - data_order_start) << "> set BLUE as <" << just_created_block->blue_sockets.at(data_order - data_order_start) << "> set WHITE as <" << just_created_block->white_sockets.at(data_order - data_order_start) << ">" << endl; }
									//if (show_info_to_console) { cout << "set RED as <" << just_created_block->red_sockets << "> set GREEN as <" << just_created_block->green_sockets << "> set BLUE as <" << just_created_block->blue_sockets << "> set WHITE as <" << just_created_block->white_sockets << ">" << endl; }
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
									//just_created_block->item_stack_size = std::stoi(subdata);
									//just_created_block->item_stack_size_condition = "=";
									if (just_created_base_data_registerer->main_button != NULL)
									{just_created_base_data_registerer->main_button->text = subdata;}

									if (just_created_base_data_registerer->condition_button != NULL)
									{just_created_base_data_registerer->condition_button->text = "=";}
								}

								if ((data_order == 1) && (EString::check_is_condition_symbols(subdata)))
								{
									if (show_info_to_console) { cout << "set stack size condition as <" << subdata << ">" << endl; }
									//just_created_block->item_stack_size_condition = subdata;
									if (just_created_base_data_registerer->condition_button != NULL)
									{just_created_base_data_registerer->condition_button->text = subdata;}
								}

								if (data_order == 2)
								{
									if (show_info_to_console) { cout << "set stack size as <" << subdata << ">" << endl; }
									//just_created_block->item_stack_size = std::stoi(subdata);
									if (just_created_base_data_registerer->main_button != NULL)
									{just_created_base_data_registerer->main_button->text = subdata;}
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
									//just_created_block->gem_level = std::stoi(subdata);
									//just_created_block->gem_level_condition = "=";

									if (just_created_base_data_registerer->main_button != NULL)
									{just_created_base_data_registerer->main_button->text = subdata;}

									if (just_created_base_data_registerer->condition_button != NULL)
									{just_created_base_data_registerer->condition_button->text = "=";}
								}

								if ((data_order == 1) && (EString::check_is_condition_symbols(subdata)))
								{
									if (show_info_to_console) { cout << "set gem level condition as <" << subdata << ">" << endl; }
									//just_created_block->gem_level_condition = subdata;

									if (just_created_base_data_registerer->condition_button != NULL)
									{just_created_base_data_registerer->condition_button->text = subdata;}
								}

								if (data_order == 2)
								{
									if (show_info_to_console) { cout << "set gem level as <" << subdata << ">" << endl; }
								//	just_created_block->gem_level = std::stoi(subdata);
									if (just_created_base_data_registerer->main_button != NULL)
									{just_created_base_data_registerer->main_button->text = subdata;}
								}
							}

							if (parser_mode == Enums::ParserMode::IS_ELDER_MAP)
							{
								if (data_order == 0) { if (show_info_to_console) { cout << "activate elder map property" << endl; } }
								
								if (data_order == 1)
								{
									if (show_info_to_console)
									{
										cout << "set elder map item as <" << subdata << ">" << endl; }
									//just_created_block->base_filter_data_bool.at(Enums::BoolData::BOOL_ELDER_MAP) = EString::convert_text_to_bool(subdata);

									if (just_created_block->influence_mode == FilterBlock::InfluenceMode::IM_IGNORE)
									{just_created_block->influence_mode = FilterBlock::InfluenceMode::IM_ONE_OF;}

									just_created_block->vector_influence.at(FilterBlock::InfluenceList::IL_ELDER) = true;
									just_created_block->influences_button_list.at(FilterBlock::InfluenceList::IL_ELDER)->gabarite = DefaultGabarite::gabarite_switcher_influence_elder;
									just_created_block->influences_button_list.at(FilterBlock::InfluenceList::IL_ELDER)->rama_color->set(EColorCollection::YELLOW);
									just_created_block->influences_button_list.at(FilterBlock::InfluenceList::IL_ELDER)->bg_color->set(EColorCollection::WHITE);
								}
							}

							if (parser_mode == Enums::ParserMode::IS_SHAPER_MAP)
							{
								if (data_order == 0) { if (show_info_to_console) { cout << "activate shaper map property" << endl; } }
								if (data_order == 1)
								{
									if (show_info_to_console) { cout << "set shaper map item as <" << subdata << ">" << endl; }
									//just_created_block->base_filter_data_bool.at(Enums::BoolData::BOOL_SHAPER_MAP) = EString::convert_text_to_bool(subdata);

									if (just_created_block->influence_mode == FilterBlock::InfluenceMode::IM_IGNORE)
									{just_created_block->influence_mode = FilterBlock::InfluenceMode::IM_ONE_OF;}

									just_created_block->vector_influence.at(FilterBlock::InfluenceList::IL_SHAPER) = true;
									just_created_block->influences_button_list.at(FilterBlock::InfluenceList::IL_SHAPER)->gabarite = DefaultGabarite::gabarite_switcher_influence_shaper;
									just_created_block->influences_button_list.at(FilterBlock::InfluenceList::IL_SHAPER)->rama_color->set(EColorCollection::YELLOW);
									just_created_block->influences_button_list.at(FilterBlock::InfluenceList::IL_SHAPER)->bg_color->set(EColorCollection::WHITE);
								}
							}



							if (parser_mode == Enums::ParserMode::MAP_TIER)
							{
								if (data_order == 0)
								{
									if (show_info_to_console) { cout << "activate map tier property" << endl; }
								}

								if ((data_order == 1) && (!EString::check_is_condition_symbols(subdata)))
								{
									if (show_info_to_console) { cout << "set map tier as <" << subdata << ">" << endl; }
									//just_created_block->map_tier = std::stoi(subdata);
									//just_created_block->map_tier_condition = "=";
									if (just_created_base_data_registerer->main_button != NULL)
									{just_created_base_data_registerer->main_button->text = subdata;}

									if (just_created_base_data_registerer->condition_button != NULL)
									{just_created_base_data_registerer->condition_button->text = "=";}
								}

								if ((data_order == 1) && (EString::check_is_condition_symbols(subdata)))
								{
									if (show_info_to_console) { cout << "set map tier condition as < " << subdata << " >" << endl; }
									//just_created_block->map_tier_condition = subdata;
									if (just_created_base_data_registerer->condition_button != NULL)
									{just_created_base_data_registerer->condition_button->text = subdata;}
								}

								if (data_order == 2)
								{
									if (show_info_to_console) { cout << "set maptier as <" << subdata << ">" << endl; }
									//just_created_block->map_tier = std::stoi(subdata);
									if (just_created_base_data_registerer->main_button != NULL)
									{just_created_base_data_registerer->main_button->text = subdata;}
								}
							}

							if (parser_mode == Enums::ParserMode::BASE_DEFENCE_PERCENTILE)
							{
								if (data_order == 0)
								{
									if (show_info_to_console) { cout << "activate base defence property" << endl; }
								}

								if ((data_order == 1) && (!EString::check_is_condition_symbols(subdata)))
								{
									if (show_info_to_console) { cout << "set base defence as <" << subdata << ">" << endl; }
									//just_created_block->map_tier = std::stoi(subdata);
									//just_created_block->map_tier_condition = "=";
									if (just_created_base_data_registerer->main_button != NULL)
									{
										just_created_base_data_registerer->main_button->text = subdata;
									}

									if (just_created_base_data_registerer->condition_button != NULL)
									{
										just_created_base_data_registerer->condition_button->text = "=";
									}
								}

								if ((data_order == 1) && (EString::check_is_condition_symbols(subdata)))
								{
									if (show_info_to_console) { cout << "set base defence condition as < " << subdata << " >" << endl; }
									//just_created_block->map_tier_condition = subdata;
									if (just_created_base_data_registerer->condition_button != NULL)
									{
										just_created_base_data_registerer->condition_button->text = subdata;
									}
								}

								if (data_order == 2)
								{
									if (show_info_to_console) { cout << "set base defence as <" << subdata << ">" << endl; }
									//just_created_block->map_tier = std::stoi(subdata);
									if (just_created_base_data_registerer->main_button != NULL)
									{
										just_created_base_data_registerer->main_button->text = subdata;
									}
								}
							}

							if (parser_mode == Enums::ParserMode::AREA_LEVEL)
							{
								if (data_order == 0)
								{
									if (show_info_to_console) { cout << "activate area level property" << endl; }
								}

								if ((data_order == 1) && (!EString::check_is_condition_symbols(subdata)))
								{
									if (show_info_to_console) { cout << "set area level as <" << subdata << ">" << endl; }
									//just_created_block->area_level = std::stoi(subdata);
									//just_created_block->area_level_condition = "=";
									if (just_created_base_data_registerer->main_button != NULL)
									{just_created_base_data_registerer->main_button->text = subdata;}

									if (just_created_base_data_registerer->condition_button != NULL)
									{just_created_base_data_registerer->condition_button->text = "=";}
								}

								if ((data_order == 1) && (EString::check_is_condition_symbols(subdata)))
								{
									if (show_info_to_console) { cout << "set area level condition as < " << subdata << " >" << endl; }
									//just_created_block->area_level_condition = subdata;
									if (just_created_base_data_registerer->condition_button != NULL)
									{just_created_base_data_registerer->condition_button->text = subdata;}
								}

								if (data_order == 2)
								{
									if (show_info_to_console) { cout << "set area level as <" << subdata << ">" << endl; }
									//just_created_block->area_level = std::stoi(subdata);
									if (just_created_base_data_registerer->main_button != NULL)
									{just_created_base_data_registerer->main_button->text = subdata;}
								}
							}

							if (parser_mode == Enums::ParserMode::CLUSTER_PASSIVES_COUNT)
							{
								if (data_order == 0)
								{
									if (show_info_to_console) { cout << "activate cluster passives count property" << endl; }
								}

								if ((data_order == 1) && (!EString::check_is_condition_symbols(subdata)))
								{
									if (show_info_to_console) { cout << "set cluster passives count as <" << subdata << ">" << endl; }
									//just_created_block->area_level = std::stoi(subdata);
									//just_created_block->area_level_condition = "=";
									if (just_created_base_data_registerer->main_button != NULL)
									{
										just_created_base_data_registerer->main_button->text = subdata;
									}

									if (just_created_base_data_registerer->condition_button != NULL)
									{
										just_created_base_data_registerer->condition_button->text = "=";
									}
								}

								if ((data_order == 1) && (EString::check_is_condition_symbols(subdata)))
								{
									if (show_info_to_console) { cout << "set cluser passives condition as < " << subdata << " >" << endl; }
									//just_created_block->area_level_condition = subdata;
									if (just_created_base_data_registerer->condition_button != NULL)
									{
										just_created_base_data_registerer->condition_button->text = subdata;
									}
								}

								if (data_order == 2)
								{
									if (show_info_to_console) { cout << "set cluster passives as <" << subdata << ">" << endl; }
									//just_created_block->area_level = std::stoi(subdata);
									if (just_created_base_data_registerer->main_button != NULL)
									{
										just_created_base_data_registerer->main_button->text = subdata;
									}
								}
							}

							if (parser_mode == Enums::ParserMode::ALTERNATE_QUALITY_TYPE)
							{
								if (data_order == 0)
								{
									if (show_info_to_console) { cout << "activate cluster passives count property" << endl; }
								}

								if ((data_order == 1) && (!EString::check_is_condition_symbols(subdata)))
								{
									if (show_info_to_console) { cout << "set cluster passives count as <" << subdata << ">" << endl; }
									//just_created_block->area_level = std::stoi(subdata);
									//just_created_block->area_level_condition = "=";
									if (just_created_base_data_registerer->main_button != NULL)
									{
										just_created_base_data_registerer->main_button->text = subdata;

										if (subdata == "Divergent")		{ just_created_base_data_registerer->main_button->selected_element = 0; }
										if (subdata == "Phantasmal")	{ just_created_base_data_registerer->main_button->selected_element = 1; }
										if (subdata == "Anomalous")		{ just_created_base_data_registerer->main_button->selected_element = 2; }
									}

									if (just_created_base_data_registerer->condition_button != NULL)
									{
										just_created_base_data_registerer->condition_button->text = "=";
									}
								}

								if ((data_order == 1) && (EString::check_is_condition_symbols(subdata)))
								{
									if (show_info_to_console) { cout << "set cluser passives condition as < " << subdata << " >" << endl; }
									//just_created_block->area_level_condition = subdata;
									if (just_created_base_data_registerer->condition_button != NULL)
									{
										just_created_base_data_registerer->condition_button->text = subdata;

										if (subdata == "Divergent") { just_created_base_data_registerer->main_button->selected_element = 0; }
										if (subdata == "Phantasmal") { just_created_base_data_registerer->main_button->selected_element = 1; }
										if (subdata == "Anomalous") { just_created_base_data_registerer->main_button->selected_element = 2; }
									}
								}

								if (data_order == 2)
								{
									if (show_info_to_console) { cout << "set cluster passives as <" << subdata << ">" << endl; }
									//just_created_block->area_level = std::stoi(subdata);
									if (just_created_base_data_registerer->main_button != NULL)
									{
										just_created_base_data_registerer->main_button->text = subdata;
									}
								}
							}


							if (parser_mode == Enums::ParserMode::CORRUPTED_MODS)
							{
								if (data_order == 0)
								{
									if (show_info_to_console) { cout << "activate corrupted mods property" << endl; }
								}

								if ((data_order == 1) && (!EString::check_is_condition_symbols(subdata)))
								{
									if (show_info_to_console) { cout << "set corrupted mods as <" << subdata << ">" << endl; }
									
									if (just_created_base_data_registerer->main_button != NULL)
									{just_created_base_data_registerer->main_button->text = subdata;}

									if (just_created_base_data_registerer->condition_button != NULL)
									{just_created_base_data_registerer->condition_button->text = "=";}
									//just_created_block->corrupted_mods_count = std::stoi(subdata);
									//just_created_block->corrupted_mods_condition = "=";
								}

								if ((data_order == 1) && (EString::check_is_condition_symbols(subdata)))
								{
									if (show_info_to_console) { cout << "set corrupted mods condition as < " << subdata << " >" << endl; }

									if (just_created_base_data_registerer->condition_button != NULL)
									{just_created_base_data_registerer->condition_button->text = subdata;}
									//just_created_block->corrupted_mods_condition = subdata;
								}

								if (data_order == 2)
								{
									if (show_info_to_console) { cout << "set corrupted mods as <" << subdata << ">" << endl; }
									if (just_created_base_data_registerer->main_button != NULL)
									{just_created_base_data_registerer->main_button->text = subdata;}
									//just_created_block->corrupted_mods_count = std::stoi(subdata);
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

		for (FilterBlock* fb : StaticData::window_filter_block->filter_block_list)
		{
			fb->is_deactivated = false;
			fb->force_enabled = false;

		}
	

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

		

		for (FilterBlock* fb:StaticData::window_filter_block->filter_block_list)
		if ((!fb->disabled) || (_save_mode == Enums::AutogenSaveMode::SOURCE))
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


			if (fb->link_to_header_separator->is_active)
			{
				loot_writer += "#header_separator";
				loot_writer += ' ';

				loot_writer += '"';
				loot_writer += fb->link_to_header_separator->text;
				loot_writer += '"';

				loot_writer += '\n';
			}


			if (fb->disabled)
			{
				loot_writer += "#block_is_disabled";

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


			if ((fb->is_cluster_enchantment_active) && (fb->cluster_enchantment_list.size() > 0))
			{
				loot_writer += '\t';
				loot_writer += "EnchantmentPassiveNode";

				for (EButton* b : fb->cluster_enchantment_list)
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
					(
						(!fb->autogen_include.at(_save_mode))
						||
						(!fb->is_show)
						
					)
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
				&&
				(fb->is_show)
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
				&&
				(fb->is_show)
			)
			{
				loot_writer += '\t';
				loot_writer += "CustomAlertSound ";

				loot_writer += '"';
				loot_writer += fb->custom_alert_sound_name;
				loot_writer += '"';

				loot_writer += '\n';
			}

			if (fb->disable_drop_sound)
			{
				loot_writer += '\t';
				loot_writer += "DisableDropSound True";
				loot_writer += '\n';
			}

			if (fb->disable_drop_sound_if_alert_sound)
			{
				loot_writer += '\t';
				loot_writer += "DisableDropSoundIfAlertSound True";
				loot_writer += '\n';
			}

			if (fb->enable_drop_sound_if_alert_sound)
			{
				loot_writer += '\t';
				loot_writer += "EnableDropSoundIfAlertSound True";
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
				&&
				(fb->is_show)
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
				&&
				(fb->is_show)
			)
			{
				loot_writer += '\t';
				loot_writer += "MinimapIcon ";
				loot_writer += std::to_string(fb->minimap_icon_size);
				loot_writer += " ";

				loot_writer += EString::icon_color_name[fb->minimap_icon_color];
				loot_writer += " ";
				loot_writer += EString::icon_shape_name[fb->minimap_icon_shape];

				loot_writer += '\n';
			}

			bool have_equal_base_type = false;


			//if (have_equal_base_type)
			if (fb->filter_block_items_button_list.size() > 0)
			{
				loot_writer += '\t';

				if (fb->is_exact_match)
				{loot_writer += "BaseType ==";}
				else
				{loot_writer += "BaseType";}

				for (EButton* b : fb->filter_block_items_button_list)
				//if (((EButtonFilterItem*)b)->is_full_equal_mode)
				{
					loot_writer += ' ';
					loot_writer += '"';
					loot_writer += b->data_string;
					loot_writer += '"';
				}

				loot_writer += '\n';
			}

			bool have_regular_base_type = false;

	

			if
				(
					(fb->vector_influence.at(0))
					||
					(fb->vector_influence.at(1))
					||
					(fb->vector_influence.at(2))
					||
					(fb->vector_influence.at(3))
					||
					(fb->vector_influence.at(4))
					||
					(fb->vector_influence.at(5))
					||
					(fb->influence_mode == FilterBlock::InfluenceMode::IM_NONE)
					)
			{
				loot_writer += '\t';

				if (fb->influence_mode == FilterBlock::InfluenceMode::IM_ALL)
				{
					loot_writer += "HasInfluence ==";
				}
				else
				{
					loot_writer += "HasInfluence";
				}

				if (fb->influence_mode != FilterBlock::InfluenceMode::IM_NONE)
				{
					if (fb->vector_influence.at(FilterBlock::InfluenceList::IL_ELDER))
					{
						loot_writer += " Elder";
					}

					if (fb->vector_influence.at(FilterBlock::InfluenceList::IL_SHAPER))
					{
						loot_writer += " Shaper";
					}

					if (fb->vector_influence.at(FilterBlock::InfluenceList::IL_CRUSADER))
					{
						loot_writer += " Crusader";
					}

					if (fb->vector_influence.at(FilterBlock::InfluenceList::IL_REDEEMER))
					{
						loot_writer += " Redeemer";
					}

					if (fb->vector_influence.at(FilterBlock::InfluenceList::IL_HUNTER))
					{
						loot_writer += " Hunter";
					}

					if (fb->vector_influence.at(FilterBlock::InfluenceList::IL_WARLORD))
					{
						loot_writer += " Warlord";
					}
				}


					if (fb->influence_mode == FilterBlock::InfluenceMode::IM_NONE)
					{
						loot_writer += " None";
					}

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

			
				

			/*
			if (fb->base_filter_data_active.at(Enums::BaseDataOrder::DATA_ELDER_ITEM))
			{
				if (fb->base_filter_data_bool.at(Enums::BoolData::BOOL_AND_ELDER))
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
			}*/


			/*
			if (fb->base_filter_data_active.at(Enums::BaseDataOrder::DATA_SOCKETS))
			{
				loot_writer += '\t';
				loot_writer += "Sockets ";

				loot_writer += fb->socket_condition;
				loot_writer += " ";
				loot_writer += std::to_string(fb->socket_count);

				loot_writer += '\n';
			}*/

				if (fb->vector_special_status.at(FilterBlock::SpecialStatusList::SSL_CORRUPTED) == FilterBlock::SpecialStatusMode::SSM_ON)
				{
					loot_writer += '\t';
					loot_writer += "Corrupted True";
					loot_writer += '\n';
				}

				if (fb->vector_special_status.at(FilterBlock::SpecialStatusList::SSL_CORRUPTED) == FilterBlock::SpecialStatusMode::SSM_OFF)
				{
					loot_writer += '\t';
					loot_writer += "Corrupted False";
					loot_writer += '\n';
				}

			if (fb->vector_special_status.at(FilterBlock::SpecialStatusList::SSL_IDENTIFIED) == FilterBlock::SpecialStatusMode::SSM_ON)
			{
				loot_writer += '\t';
				loot_writer += "Identified True";
				loot_writer += '\n';
			}
				if (fb->vector_special_status.at(FilterBlock::SpecialStatusList::SSL_IDENTIFIED) == FilterBlock::SpecialStatusMode::SSM_OFF)
			{
				loot_writer += '\t';
				loot_writer += "Identified False";
				loot_writer += '\n';
			}
				
				if (fb->vector_special_status.at(FilterBlock::SpecialStatusList::SSL_ENCHANTED) == FilterBlock::SpecialStatusMode::SSM_ON)
				{
					loot_writer += '\t';
					loot_writer += "AnyEnchantment True";
					loot_writer += '\n';
				}
				if (fb->vector_special_status.at(FilterBlock::SpecialStatusList::SSL_ENCHANTED) == FilterBlock::SpecialStatusMode::SSM_OFF)
				{
					loot_writer += '\t';
					loot_writer += "AnyEnchantment False";
					loot_writer += '\n';
				}


				if (fb->vector_special_status.at(FilterBlock::SpecialStatusList::SSL_SYNTHESISED) == FilterBlock::SpecialStatusMode::SSM_ON)
				{
					loot_writer += '\t';
					loot_writer += "SynthesisedItem True";
					loot_writer += '\n';
				}
				if (fb->vector_special_status.at(FilterBlock::SpecialStatusList::SSL_SYNTHESISED) == FilterBlock::SpecialStatusMode::SSM_OFF)
				{
					loot_writer += '\t';
					loot_writer += "SynthesisedItem False";
					loot_writer += '\n';
				}

				if (fb->vector_special_status.at(FilterBlock::SpecialStatusList::SSL_FRACTURED) == FilterBlock::SpecialStatusMode::SSM_ON)
				{
					loot_writer += '\t';
					loot_writer += "FracturedItem True";
					loot_writer += '\n';
				}
				if (fb->vector_special_status.at(FilterBlock::SpecialStatusList::SSL_FRACTURED) == FilterBlock::SpecialStatusMode::SSM_OFF)
				{
					loot_writer += '\t';
					loot_writer += "FracturedItem False";
					loot_writer += '\n';
				}

				if (fb->vector_special_status.at(FilterBlock::SpecialStatusList::SSL_BLIGHTED) == FilterBlock::SpecialStatusMode::SSM_ON)
				{
					loot_writer += '\t';
					loot_writer += "BlightedMap True";
					loot_writer += '\n';
				}
				if (fb->vector_special_status.at(FilterBlock::SpecialStatusList::SSL_BLIGHTED) == FilterBlock::SpecialStatusMode::SSM_OFF)
				{
					loot_writer += '\t';
					loot_writer += "BlightedMap False";
					loot_writer += '\n';
				}


				if (fb->vector_special_status.at(FilterBlock::SpecialStatusList::SSL_ALTERNATE_QUALITY) == FilterBlock::SpecialStatusMode::SSM_ON)
				{
					loot_writer += '\t';
					loot_writer += "AlternateQuality True";
					loot_writer += '\n';
				}
				if (fb->vector_special_status.at(FilterBlock::SpecialStatusList::SSL_ALTERNATE_QUALITY) == FilterBlock::SpecialStatusMode::SSM_OFF)
				{
					loot_writer += '\t';
					loot_writer += "AlternateQuality False";
					loot_writer += '\n';
				}

				if (fb->vector_special_status.at(FilterBlock::SpecialStatusList::SSL_REPLICA) == FilterBlock::SpecialStatusMode::SSM_ON)
				{
					loot_writer += '\t';
					loot_writer += "Replica True";
					loot_writer += '\n';
				}
				if (fb->vector_special_status.at(FilterBlock::SpecialStatusList::SSL_REPLICA) == FilterBlock::SpecialStatusMode::SSM_OFF)
				{
					loot_writer += '\t';
					loot_writer += "Replica False";
					loot_writer += '\n';
				}

				if (fb->vector_special_status.at(FilterBlock::SpecialStatusList::SSL_MIRRORED) == FilterBlock::SpecialStatusMode::SSM_ON)
				{
					loot_writer += '\t';
					loot_writer += "Mirrored True";
					loot_writer += '\n';
				}
				if (fb->vector_special_status.at(FilterBlock::SpecialStatusList::SSL_MIRRORED) == FilterBlock::SpecialStatusMode::SSM_OFF)
				{
					loot_writer += '\t';
					loot_writer += "Mirrored False";
					loot_writer += '\n';
				}

				if (fb->vector_special_status.at(FilterBlock::SpecialStatusList::SSL_SCOURGED) == FilterBlock::SpecialStatusMode::SSM_ON)
				{
					loot_writer += '\t';
					loot_writer += "Scourged True";
					loot_writer += '\n';
				}
				if (fb->vector_special_status.at(FilterBlock::SpecialStatusList::SSL_SCOURGED) == FilterBlock::SpecialStatusMode::SSM_OFF)
				{
					loot_writer += '\t';
					loot_writer += "Scourged False";
					loot_writer += '\n';
				}

				if (fb->vector_special_status.at(FilterBlock::SpecialStatusList::SSL_UBER_BLIGHT) == FilterBlock::SpecialStatusMode::SSM_ON)
				{
					loot_writer += '\t';
					loot_writer += "UberBlightedMap True";
					loot_writer += '\n';
				}

				if (fb->vector_special_status.at(FilterBlock::SpecialStatusList::SSL_UBER_BLIGHT) == FilterBlock::SpecialStatusMode::SSM_OFF)
				{
					loot_writer += '\t';
					loot_writer += "UberBlightedMap False";
					loot_writer += '\n';
				}

				for (FilterBlock::base_data_button_collection_struct* bdbcl : fb->FilterBlock::base_data_button_collection_list)
				{
					if (*FilterBlock::filter_block_data_attribute_registerer.at(bdbcl->target_id)->button_type == Enums::FilterBlockButtonType::FBBT_DROP_LIST_RARITY)
					{
						loot_writer += '\t';

						//base data name
						loot_writer += *FilterBlock::filter_block_data_attribute_registerer.at(bdbcl->target_id)->data_name;
						loot_writer += ' ';

						//condition operator
						loot_writer += bdbcl->condition_button->text;
						loot_writer += ' ';

						//drop list rarity value
						loot_writer += bdbcl->main_button->drop_text_base.at(bdbcl->main_button->selected_element);
						loot_writer += '\n';
					}

					if
					(
						(*FilterBlock::filter_block_data_attribute_registerer.at(bdbcl->target_id)->button_type == Enums::FilterBlockButtonType::FBBT_INPUT_FIELD)
						||
						(*FilterBlock::filter_block_data_attribute_registerer.at(bdbcl->target_id)->button_type == Enums::FilterBlockButtonType::FBBT_INPUT_FIELD_ANY)
					)
					{
						loot_writer += '\t';
						//base data name
						loot_writer += *FilterBlock::filter_block_data_attribute_registerer.at(bdbcl->target_id)->data_name;
						loot_writer += ' ';

						//condition operator
						loot_writer += bdbcl->condition_button->text;
						loot_writer += ' ';

						//main button text
						loot_writer += bdbcl->main_button->text;
						loot_writer += '\n';
					}
					
					if (*FilterBlock::filter_block_data_attribute_registerer.at(bdbcl->target_id)->button_type == Enums::FilterBlockButtonType::FBBT_DROP_LIST_ALTERNATE_QUALITY)
					{
						loot_writer += '\t';

						//base data name
						loot_writer += *FilterBlock::filter_block_data_attribute_registerer.at(bdbcl->target_id)->data_name;
						loot_writer += ' ';

						//drop list rarity value
						loot_writer += bdbcl->main_button->drop_text_base.at(bdbcl->main_button->selected_element);
						loot_writer += '\n';
					}


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


			if (fb->is_continue)
			{
				loot_writer += "Continue";
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



	std::vector< EBaseData::base_data_registerer* > EBaseData::base_data_registerer_list;
