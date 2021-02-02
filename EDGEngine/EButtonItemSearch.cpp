#pragma once

#define _CRT_SECURE_NO_WARNINGS

#include "EButtonItemSearch.h"
#include "StaticData.h"
#include "EUtils.h"
#include <fstream>
#include <direct.h>
#include <ctime>



EButtonItemSearch::EButtonItemSearch(float _x, float _y, float _sx, float _sy, Enums::ButtonType _type) : EButton(_x, _y, _sx, _sy)
{
	is_active = false;
	have_icon = true;
	have_text = false;
	have_description = true;

	position_mode_x = Enums::PositionMode::LEFT;
	position_mode_y = Enums::PositionMode::UP;

	master_position = Enums::PositionMaster::WINDOW;

	description_text = "";

	have_rama = true;

	rama_color->set(0.2f, 0.15f, 0.05f, 0.6f);
	bg_color->set(EColorCollection::BLACK);
	text_color->set(EColorCollection::WHITE);

	button_type = _type;

	dynamic_input_width = true;
}

void EButtonItemSearch::click_event()
{
	if (button_type == Enums::ButtonType::BUTTON_SEARCH_ITEM)
	{
		StaticData::window_find_item->is_active = false;
		StaticData::window_find_item->target_button->description_text = description_text;
		StaticData::window_find_item->target_button->gabarite = gabarite;

		StaticData::window_find_item->target_button->data_id = data_id;
		StaticData::window_find_item->target_button->data_string = data_string;

		if (StaticData::window_find_item->target_button->master_window == StaticData::window_manual_loot)
		{
			for (DADItem* item : ItemList::item_list)
			{
				if (item->item_name == data_string)
				{
					std::string class_text = item->base_class;

					/*if (EString::active_localisation == Enums::LocalisationList::RU)
					{
						for (BaseClass* c : EString::base_class_list)
						{
							if (c->base_name == class_text) { StaticData::window_manual_loot->link_to_class_button->text = c->ru_name; }
						}
					}
					else*/
					{StaticData::window_manual_loot->link_to_class_button->text = class_text;}

					StaticData::window_manual_loot->link_to_height->text	= std::to_string(item->height);
					StaticData::window_manual_loot->link_to_width->text		= std::to_string(item->width);
				}
			}

			
		}

		//StaticData::window_find_item->input_button->text = "";
	}

	if (button_type == Enums::ButtonType::BUTTON_SEARCH_DEFAULT_SOUND)
	{

		StaticData::window_find_item->is_active = false;

		if (data_id >= 1)
		{
			StaticData::window_find_item->master_block->alert_sound_id = Enums::DefaultAlertSound(data_id);
			StaticData::window_find_item->master_block->alert_sound_name = data_string;

			StaticData::window_find_item->master_block->is_alert_sound = true;

			master_block->sound_button_link->activate();
		}
		else
		{
			if ((!master_block->is_alert_sound)&&(!master_block->is_custom_alert_sound))
			{
				master_block->sound_button_link->deactivate();
			}

			master_block->is_alert_sound = false;

			master_block->alert_sound_id = Enums::DefaultAlertSound(0);
			master_block->alert_sound_name = "";
		}

		master_block->is_custom_alert_sound = false;
		master_block->custom_alert_sound_name = "";
	}

	if (button_type == Enums::ButtonType::BUTTON_SEARCH_BASE_CLASS)
	{
		StaticData::window_find_item->target_button->text = text;
		StaticData::window_find_item->target_button->data_string = data_string;
		StaticData::window_find_item->target_button->data_id = data_id;

		if (StaticData::window_find_item->target_button->master_window == StaticData::window_manual_loot)
		{
			StaticData::window_find_item->target_button->text = data_string;
		}

		StaticData::window_find_item->target_button->button_size_x = EFont::get_width(EFont::active_font, text) + 5.0f;

		StaticData::window_find_item->is_active = false;
	}

	if (button_type == Enums::ButtonType::BUTTON_SEARCH_ENCHANTMENT)
	{
		StaticData::window_find_item->target_button->text = text;
		StaticData::window_find_item->target_button->data_string = data_string;
		StaticData::window_find_item->target_button->data_id = data_id;


		StaticData::window_find_item->target_button->button_size_x = EFont::get_width(EFont::active_font, text) + 5.0f;

		StaticData::window_find_item->is_active = false;
	}

	if (button_type == Enums::ButtonType::BUTTON_SEARCH_CLUSTER_ENCHANTMENT)
	{
		StaticData::window_find_item->target_button->text = text;
		StaticData::window_find_item->target_button->data_string = data_string;
		StaticData::window_find_item->target_button->data_id = data_id;


		StaticData::window_find_item->target_button->button_size_x = EFont::get_width(EFont::active_font, text) + 5.0f;

		StaticData::window_find_item->is_active = false;
	}

	if (button_type == Enums::ButtonType::BUTTON_SEARCH_PROPHECY)
	{
		StaticData::window_find_item->target_button->text = text;
		StaticData::window_find_item->target_button->data_string = data_string;
		StaticData::window_find_item->target_button->data_id = data_id;


		StaticData::window_find_item->target_button->button_size_x = EFont::get_width(EFont::active_font, text ) + 5.0f;

		StaticData::window_find_item->is_active = false;
	}

	if (button_type == Enums::ButtonType::BUTTON_SEARCH_CUSTOM_SOUND)
	{

		StaticData::window_find_item->is_active = false;

		if (data_id >= 1)
		{
			StaticData::window_find_item->master_block->custom_alert_sound_name = text;
			StaticData::window_find_item->master_block->is_custom_alert_sound = true;

			master_block->sound_button_link->activate();
		}
		else
		{
			if ((!master_block->is_alert_sound)&&(!master_block->is_custom_alert_sound))
			{
				master_block->sound_button_link->deactivate();
			}

			master_block->is_custom_alert_sound = false;

			master_block->custom_alert_sound_name = "";
		}

		master_block->is_alert_sound = false;
		master_block->alert_sound_id = Enums::DefaultAlertSound::SOUND_NONE;
		master_block->alert_sound_name = "";
	}

	if (button_type == Enums::ButtonType::BUTTON_SEARCH_LOOT_FILTER)
	{
		EString::opened_loot_filter_path = EString::loot_filter_path_list.at(data_id);

		StaticData::window_main->tab_list.at(StaticData::active_tab)->text = text;
		StaticData::window_main->tab_list.at(StaticData::active_tab)->button_min_size_x = 30;

		EString::path_list.at(StaticData::active_tab) = EString::opened_loot_filter_path;

		EFile::parse_loot_filter_data(EString::loot_filter_path_list.at(data_id));
		StaticData::window_find_item->is_active = false;
		StaticData::window_filter_block->is_active = true;

		for (int i = 0; i < 87; i++)
		for (int j = 0; j < 125; j++)
		{
			StaticData::window_loot_simulator->free_space[j][i] = true;
		}

		for (LootItem* _l : StaticData::window_loot_simulator->main_loot_item_list)
		{
			StaticData::window_loot_simulator->find_filter_block(_l, StaticData::window_filter_block, false);
		}

		for (LootItem* _l : StaticData::window_loot_simulator->main_loot_item_list)
		{
			StaticData::window_loot_simulator->place(_l);
		}

		EFont::active_font->scale = 1.0f;

		std::string sss = "1234567890";

		/*
		ofstream copier;
		copier.open(EString::path_to_poe_folder + "copy\\S.filter");
		copier << sss;
		copier.close();*/

		time_t now = time(0);
		tm* ltm = localtime(&now);
		//_CRT_SECURE_NO_WARNINGS;
		std::string path_to_copy = EString::path_to_poe_folder + "copies";
		_mkdir(path_to_copy.c_str());

		std::ifstream src(EString::loot_filter_path_list.at(data_id), std::ios::binary);
		std::ofstream dst
		(
			EString::path_to_poe_folder
			+
			"copies\\"
			+
			text
			+
			" "
			+
			std::to_string(ltm->tm_mday)
			+
			"-"
			+
			std::to_string(ltm->tm_mon + 1)
			+
			"-"
			+
			std::to_string(1900 + ltm->tm_year)
			+
			" "
			+
			std::to_string(ltm->tm_hour)
			+
			"="
			+
			std::to_string(ltm->tm_min)
			+
			"="
			+
			std::to_string(ltm->tm_sec)
			+
			".filter"
			, std::ios::binary
		);

		dst << src.rdbuf();

	//	EFile::save_filter(EString::path_to_poe_folder + "/reserve_copy/" + text + "_copy.filter");
	}

	if (button_type == Enums::ButtonType::BUTTON_SEARCH_LOOT_SIMULATOR_PATTERN)
	{
		StaticData::window_find_item->is_active = false;

		//std::cout << "try open loot pattern: " << 
		EString::load_loot_pattern(EString::loot_simulator_pattern_name_list.at(data_id));

		StaticData::window_loot_simulator->manual_event();
	}
	//StaticData::window_find_item->fill_search_array();

}

void EButtonItemSearch::right_click_event()
{
	if (button_type == Enums::ButtonType::BUTTON_SEARCH_DEFAULT_SOUND)
	{
		if
		(
			(data_id >= 1)
			&&
			(data_id < ESound::default_drop_sound_name.size())
			&&
			(ESound::engine != NULL)
		)
		{
			ESound::default_drop_sound.at(data_id)->setDefaultVolume(StaticData::window_filter_block->sound_volume);
			ESound::engine->play2D(ESound::default_drop_sound.at(data_id));
		}
	}

	if (button_type == Enums::ButtonType::BUTTON_SEARCH_CUSTOM_SOUND)
	{
		if
		(
			(data_id >= 1)
			&&
			(data_id < ESound::custom_drop_sound_name.size())
			&&
			(ESound::engine != NULL)
		)
		{
			ESound::custom_drop_sound.at(data_id)->setDefaultVolume(StaticData::window_filter_block->sound_volume);
			ESound::engine->play2D(ESound::custom_drop_sound.at(data_id));
		}
	}
}

void EButtonItemSearch::update_localisation()
{
	//description_text = "";
	if ((button_type == Enums::ButtonType::BUTTON_SEARCH_CUSTOM_SOUND)||(button_type == Enums::ButtonType::BUTTON_SEARCH_DEFAULT_SOUND))
	{
		description_text = EString::localize_it("description_press_rmb_to_play_sound");
	}
}

	/*void EButton::click_event()
	{
		std::cout << "STANDART click event" << std::endl;
	}
	*/
	/*void EButton::click_event()
	{
		//std::cout << " ### pressed ### " << std::endl;

//		StaticData::window_find_item->is_active=false;
	}*/



