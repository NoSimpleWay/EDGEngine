#pragma once
#include "EUtils.h"
#include <cmath>
#include <irr/irrKlang.h>
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

	std::string EString::upper_charset = "QWERTYUIOPASDFGHJKLZXCVBNM®…÷” ≈Õ√ÿŸ«’⁄‘€¬¿œ–ŒÀƒ∆›ﬂ◊—Ã»“‹¡ﬁ";
	std::string EString::lower_charset = "qwertyuiopasdfghjklzxcvbnm∏ÈˆÛÍÂÌ„¯˘Áı˙Ù˚‚‡ÔÓÎ‰Ê˝ˇ˜ÒÏËÚ¸·˛";

	std::string EString::path_to_poe_folder;

	std::vector<BaseClass*> EString::base_class_list;
	std::vector<ProphecyList*> EString::prophecy_list;

	std::vector<std::string> EString::loot_filter_name_list;
	std::vector<std::string> EString::loot_filter_path_list;

	std::string EString::opened_loot_filter_name;
	std::string EString::opened_loot_filter_path;

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

	void EFile::parse_loot_filter_data(std::string _path)
	{


		StaticData::window_filter_block->filter_block_list.clear();

		ifstream myfile;
		myfile.open(_path);





		string line;
		int line_number = 0;
		int data_order = 0;

		Enums::ParserMode parser_mode = Enums::ParserMode::NOTHING;

		cout << endl << endl << endl;

		FilterBlock* just_created_block = new FilterBlock();

		int error_counts = 0;
		bool show_info_to_console = false;

		EButton* just_created_button = NULL;

		int explicit_group_id = -1;

		while ((getline(myfile, line)) && (line_number < 10000))
		{

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
					if (show_info_to_console) cout << "comment mode activate, now i dont parse data by normal way" << endl;
					parser_mode = Enums::ParserMode::NOTHING;
				}

				if (((line.at(i) != ' ') || (space_is_not_separator)) && (line.at(i) != '\t') && (line.at(i) != '"'))
				{
					subdata += line.at(i);
				}

				if
					(
					(
						((line.at(i) == ' ') && (!space_is_not_separator)) || (line.at(i) == '\t') || (i + 1 >= line.length())
						)
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
									std::cout << "Try get acess to remove button" << std::endl;

									parser_mode = Enums::ParserMode::CLASS;
									just_created_block->is_base_class_active = true;
									just_created_block->plus_class_button_link->is_active = true;
									just_created_block->remove_base_class_button->is_active = true;
								}


								if (subdata == "SetFontSize") { parser_mode = Enums::ParserMode::FONT_SIZE; just_created_block->is_font_size_active = true; }
								if (subdata == "SetTextColor") { parser_mode = Enums::ParserMode::TEXT_COLOR; just_created_block->is_text_color_active = true; }
								if (subdata == "SetBorderColor") { parser_mode = Enums::ParserMode::BORDER_COLOR; just_created_block->is_rama_color_active = true; }
								if (subdata == "SetBackgroundColor") { parser_mode = Enums::ParserMode::BACKGROUND_COLOR; just_created_block->is_bg_color_active = true; }

								if (subdata == "PlayAlertSound") { parser_mode = Enums::ParserMode::ALERT_SOUND; just_created_block->is_alert_sound = true; }
								if (subdata == "CustomAlertSound") { parser_mode = Enums::ParserMode::CUSTOM_ALERT_SOUND; just_created_block->is_custom_alert_sound = true; }
								if (subdata == "PlayEffect") { parser_mode = Enums::ParserMode::RAY; just_created_block->is_ray = true; }
								if (subdata == "MinimapIcon") { parser_mode = Enums::ParserMode::MINIMAP_ICON; just_created_block->is_minimap_icon = true; }

								if (subdata == "BaseType") { parser_mode = Enums::ParserMode::BASETYPE; }

								if (subdata == "ShaperItem") { parser_mode = Enums::ParserMode::IS_SHAPER_ITEM; just_created_block->base_filter_data_active.at(Enums::BaseDataOrder::DATA_SHAPER_ITEM) = true; }
								if (subdata == "ItemLevel") { parser_mode = Enums::ParserMode::ITEM_LEVEL; just_created_block->base_filter_data_active.at(Enums::BaseDataOrder::DATA_ITEM_LEVEL) = true; }
								if (subdata == "HasExplicitMod") { parser_mode = Enums::ParserMode::EXPLICIT_MOD; explicit_group_id++; }
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

							}
						}
						else
						{
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
									class_button->button_size_x = EFont::get_width(EFont::font_arial, subdata) + 5.0f;

									just_created_block->button_list.push_back(class_button);
									just_created_block->base_class_list.push_back(class_button);




								}
							}

							if (parser_mode == Enums::ParserMode::FONT_SIZE)
							{
								//if (data_order == 0) { cout << "activate rarity property" << endl; }
								if (data_order > 0)
								{
									if (show_info_to_console) { cout << "set font size <" << subdata << ">" << endl; }
									just_created_block->font_size = std::stoi(subdata);
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

									if (subdata == "1") { just_created_block->alert_sound_id = Enums::DefaultAlertSound::SOUND_01; }
									if (subdata == "2") { just_created_block->alert_sound_id = Enums::DefaultAlertSound::SOUND_02; }
									if (subdata == "3") { just_created_block->alert_sound_id = Enums::DefaultAlertSound::SOUND_03; }
									if (subdata == "4") { just_created_block->alert_sound_id = Enums::DefaultAlertSound::SOUND_04; }
									if (subdata == "5") { just_created_block->alert_sound_id = Enums::DefaultAlertSound::SOUND_05; }
									if (subdata == "6") { just_created_block->alert_sound_id = Enums::DefaultAlertSound::SOUND_06; }
									if (subdata == "7") { just_created_block->alert_sound_id = Enums::DefaultAlertSound::SOUND_07; }
									if (subdata == "8") { just_created_block->alert_sound_id = Enums::DefaultAlertSound::SOUND_08; }
									if (subdata == "9") { just_created_block->alert_sound_id = Enums::DefaultAlertSound::SOUND_09; }
									if (subdata == "10") { just_created_block->alert_sound_id = Enums::DefaultAlertSound::SOUND_10; }
									if (subdata == "11") { just_created_block->alert_sound_id = Enums::DefaultAlertSound::SOUND_11; }
									if (subdata == "12") { just_created_block->alert_sound_id = Enums::DefaultAlertSound::SOUND_12; }
									if (subdata == "13") { just_created_block->alert_sound_id = Enums::DefaultAlertSound::SOUND_13; }
									if (subdata == "14") { just_created_block->alert_sound_id = Enums::DefaultAlertSound::SOUND_14; }
									if (subdata == "15") { just_created_block->alert_sound_id = Enums::DefaultAlertSound::SOUND_15; }
									if (subdata == "16") { just_created_block->alert_sound_id = Enums::DefaultAlertSound::SOUND_16; }

									if (subdata == "ShAlchemy") { just_created_block->alert_sound_id = Enums::DefaultAlertSound::SOUND_SHAPER_ALCHEMY; }
									if (subdata == "ShBlessed") { just_created_block->alert_sound_id = Enums::DefaultAlertSound::SOUND_SHAPER_BLESSED; }
									if (subdata == "ShChaos") { just_created_block->alert_sound_id = Enums::DefaultAlertSound::SOUND_SHAPER_CHAOS; }
									if (subdata == "ShDivine") { just_created_block->alert_sound_id = Enums::DefaultAlertSound::SOUND_SHAPER_DIVINE; }
									if (subdata == "ShExalted") { just_created_block->alert_sound_id = Enums::DefaultAlertSound::SOUND_SHAPER_EXALTED; }
									if (subdata == "ShFusing") { just_created_block->alert_sound_id = Enums::DefaultAlertSound::SOUND_SHAPER_FUSING; }
									if (subdata == "ShGeneral") { just_created_block->alert_sound_id = Enums::DefaultAlertSound::SOUND_SHAPER_GENERAL; }
									if (subdata == "ShMirror") { just_created_block->alert_sound_id = Enums::DefaultAlertSound::SOUND_SHAPER_MIRROR; }
									if (subdata == "ShRegal") { just_created_block->alert_sound_id = Enums::DefaultAlertSound::SOUND_SHAPER_REGAL; }
									if (subdata == "ShVaal") { just_created_block->alert_sound_id = Enums::DefaultAlertSound::SOUND_SHAPER_VAAL; }
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

								if (data_order == 1) { if (show_info_to_console) { cout << "set ray color <" << subdata << ">" << endl; } just_created_block->ray_color = Enums::GameColors(Helper::get_id_from_game_color_text(subdata)); }
								//if (data_order == 2) { cout << "set alert sound volume <" << subdata << ">" << endl; just_created_block->alert_sound_volume = std::stoi(subdata); }
							}

							if (parser_mode == Enums::ParserMode::BASETYPE)
							{
								//if (data_order == 0) { cout << "activate rarity property" << endl; }
								if (data_order > 0)
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

										just_created_button->description_text = ItemList::item_list.at(item_id)->item_name + " (" + ItemList::item_list.at(item_id)->item_name_ru + ")";
										just_created_button->data_string = ItemList::item_list.at(item_id)->item_name;

										if (just_created_button->button_size_x < 30) { just_created_button->button_size_x = 30; }
									}
									else
									{
										just_created_button->have_icon = true;
										just_created_button->gabarite = DefaultGabarite::gabarite_undefined;

										just_created_button->description_text = "Unknown item (" + subdata + ")";
										just_created_button->data_string = subdata;

										if (just_created_button->button_size_x < 30) { just_created_button->button_size_x = 30; }
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

									cout << "try allocate explicit list at <" << explicit_group_id << ">" << endl;
									EButtonExplicit* explicit_button = new EButtonExplicit(0, 0, 100, 20, Enums::ButtonType::BUTTON_EXPLICIT_FILTER_BLOCK_LIST);
									explicit_button->text = subdata;
									explicit_button->master_block = just_created_block;
									explicit_button->master_window = StaticData::window_filter_block;
									explicit_button->button_size_x = EFont::get_width(EFont::font_arial, subdata) + 5.0f;
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
									prophecy_button->button_size_x = EFont::get_width(EFont::font_arial, subdata) + 5.0f;

									prophecy_button->data_id = -1;

									for (int sr = 0; sr < EString::prophecy_list.size(); sr++)
									{
										if (EString::prophecy_list.at(sr)->base_name == subdata)
										{
											prophecy_button->data_id = sr;
										}
									}

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
	}

	void EFile::save_filter(std::string _path)
	{
		ofstream myfile;
		myfile.open(_path);

		std::string loot_writer;
		loot_writer = "#Created due to DaD Editor (by NoSimpleWay)";
		loot_writer += '\n';

	
		for (FilterBlock* fb:StaticData::window_filter_block->filter_block_list)
		{
			if (fb->is_show)
			{
				loot_writer += "Show";
				loot_writer += '\n';
			}
			else
			{
				loot_writer += "Hide";
				loot_writer += '\n';
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

			if (fb->is_base_class_active)
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

			if (fb->is_font_size_active)
			{
				loot_writer += '\t';
				loot_writer += "SetFontSize ";
				loot_writer += std::to_string(fb->font_size);
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

			if (fb->is_alert_sound)
			{
				loot_writer += '\t';
				loot_writer += "PlayAlertSound ";

				loot_writer += fb->alert_sound_name;
				loot_writer += " ";

				loot_writer += std::to_string(fb->alert_sound_volume);

				loot_writer += '\n';
			}

			if (fb->is_custom_alert_sound)
			{
				loot_writer += '\t';
				loot_writer += "CustomAlertSound ";

				loot_writer += fb->custom_alert_sound_name;

				loot_writer += '\n';
			}

			if (fb->is_ray)
			{
				loot_writer += '\t';
				loot_writer += "PlayAlertSound ";
				loot_writer += EString::game_color_name[fb->ray_color];

				loot_writer += '\n';
			}

			if (fb->is_minimap_icon)
			{
				loot_writer += '\t';
				loot_writer += "MinimapIcon ";
				loot_writer += std::to_string(fb->minimap_icon_size);
				loot_writer += " ";

				loot_writer += EString::game_color_name[fb->minimap_icon_color];
				loot_writer += " ";
				loot_writer += EString::icon_shape_name[fb->minimap_icon_color];

				loot_writer += '\n';
			}

			if (fb->filter_block_items_button_list.size() > 0)
			{
				loot_writer += '\t';
				loot_writer += "BaseType";

				for (EButton* b : fb->filter_block_items_button_list)
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

			if (fb->base_filter_data_bool.at(Enums::BaseDataOrder::DATA_QUALITY))
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


	}
