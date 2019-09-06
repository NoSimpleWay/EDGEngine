#include "EButtonText.h"
#include "StaticData.h"



EButtonText::EButtonText(float _x, float _y, float _sx, float _sy, Enums::ButtonType _type):EButton(_x,_y,_sx,_sy)
{
	have_text = true;
	have_rama = true;
	have_icon = false;

	rama_thikness = 2;
	rama_color->set(.2f, .3f, .4f, .5f);

	button_type = _type;

	if (button_type == Enums::ButtonType::BUTTON_OPEN_DEFAULT_DROP_SOUND_WINDOW)
	{
		text_align_x = Enums::PositionMode::MID;
	

		master_position = Enums::PositionMaster::WINDOW;
	}

	if (button_type == Enums::ButtonType::BUTTON_OPEN_CUSTOM_DROP_SOUND_WINDOW)
	{
		text_align_x = Enums::PositionMode::MID;
		

		master_position = Enums::PositionMaster::WINDOW;
	}

	if (button_type == Enums::ButtonType::BUTTON_ADD_EXPLICIT_GROUP)
	{
		text_align_x = Enums::PositionMode::MID;
		position_mode_x = Enums::PositionMode::MID;
		position_mode_y = Enums::PositionMode::UP;

		

		master_position = Enums::PositionMaster::WINDOW;

		bg_color->set(0.5f,0.5f,0.8f,0.5f);
	}

	if (button_type == Enums::ButtonType::BUTTON_ACTIVE_BASE_CLASS_LIST)
	{
		text_align_x = Enums::PositionMode::MID;
		position_mode_x = Enums::PositionMode::MID;
		position_mode_y = Enums::PositionMode::UP;

		

		master_position = Enums::PositionMaster::WINDOW;

		bg_color->set(0.5f, 0.8f, 0.5f, 0.5f);
	}
	
	if (button_type == Enums::ButtonType::BUTTON_ACTIVE_PROPHECY_LIST)
	{
		text_align_x = Enums::PositionMode::MID;
		position_mode_x = Enums::PositionMode::MID;
		position_mode_y = Enums::PositionMode::UP;

		

		master_position = Enums::PositionMaster::WINDOW;

		bg_color->set(0.8f, 0.5f, 0.8f, 0.5f);
	}

	if (button_type == Enums::ButtonType::BUTTON_ACTIVE_ENCHANTEMENT_LIST)
	{
		text_align_x = Enums::PositionMode::MID;
		position_mode_x = Enums::PositionMode::MID;
		position_mode_y = Enums::PositionMode::UP;

		

		master_position = Enums::PositionMaster::WINDOW;

		bg_color->set(0.3f, 0.3f, 0.3f, 0.5f);
	}

	if (button_type == Enums::ButtonType::BUTTON_ADD_EXPLICIT_ELEMENT)
	{
		text_align_x = Enums::PositionMode::MID;
		position_mode_x = Enums::PositionMode::LEFT;
		position_mode_y = Enums::PositionMode::UP;

		

		master_position = Enums::PositionMaster::WINDOW;
	}

	if (button_type == Enums::ButtonType::BUTTON_MINIMAP_ICON_SELECT_SIZE)
	{
		text_align_x = Enums::PositionMode::MID;
		position_mode_x = Enums::PositionMode::LEFT;
		position_mode_y = Enums::PositionMode::DOWN;

		//text = "Select size of minimap icon";

		master_position = Enums::PositionMaster::WINDOW;
	}

	if (button_type == Enums::ButtonType::BUTTON_SET_RAY_IS_TEMPOTARY)
	{
		text_align_x = Enums::PositionMode::MID;
		

		master_position = Enums::PositionMaster::WINDOW;
	}

	if (button_type == Enums::ButtonType::BUTTON_SET_RAY_IS_CONSTANT)
	{
		text_align_x = Enums::PositionMode::MID;
		

		master_position = Enums::PositionMaster::WINDOW;
	}

	if (button_type == Enums::ButtonType::BUTTON_CANCEL_REMOVE_FILTER_BLOCK)
	{
		text_align_x = Enums::PositionMode::MID;

		position_mode_x = Enums::PositionMode::MID;
		position_mode_y = Enums::PositionMode::MID;

		master_position = Enums::PositionMaster::FILTER_BLOCK;
	}
	
	if (button_type == Enums::ButtonType::BUTTON_NEW_LOOT_FILTER_NAME)
	{
		text_align_x = Enums::PositionMode::LEFT;

		position_mode_x = Enums::PositionMode::LEFT;
		position_mode_y = Enums::PositionMode::MID;

		master_position = Enums::PositionMaster::WINDOW;

		

		have_text = true;
		have_input_mode = true;
		text = "";

		
	}

	if (button_type == Enums::ButtonType::BUTTON_NEW_LOOT_FILTER_OK)
	{
		text_align_x = Enums::PositionMode::MID;

		position_mode_x = Enums::PositionMode::LEFT;
		position_mode_y = Enums::PositionMode::MID;

		master_position = Enums::PositionMaster::WINDOW;


		have_text = true;
		have_input_mode = false;
	}

	if (button_type == Enums::ButtonType::BUTTON_SELECT_FONT)
	{
		text_align_x = Enums::PositionMode::MID;

		position_mode_x = Enums::PositionMode::MID;
		position_mode_y = Enums::PositionMode::UP;

		master_position = Enums::PositionMaster::WINDOW;

		have_text = true;
		have_input_mode = false;
	}


	if (button_type == Enums::ButtonType::BUTTON_FILTER_BLOCK_TAB)
	{
		text_align_x = Enums::PositionMode::MID;

		position_mode_x = Enums::PositionMode::LEFT;
		position_mode_y = Enums::PositionMode::UP;

		master_position = Enums::PositionMaster::WINDOW;

		have_text = true;
		have_input_mode = false;
	}

	if (button_type == Enums::ButtonType::BUTTON_OPEN_PATTERN_WINDOW)
	{
		text_align_x = Enums::PositionMode::MID;

		position_mode_x = Enums::PositionMode::LEFT;
		position_mode_y = Enums::PositionMode::UP;

		master_position = Enums::PositionMaster::WINDOW;

		have_text = true;
		have_input_mode = false;
	}

	if (button_type == Enums::ButtonType::BUTTON_ACCEPT)
	{
		text_align_x = Enums::PositionMode::MID;

		position_mode_x = Enums::PositionMode::MID;
		position_mode_y = Enums::PositionMode::DOWN;

		master_position = Enums::PositionMaster::WINDOW;

		have_text = true;
		have_input_mode = false;

		text_color->set(EColorCollection::RED);
		rama_color->set(EColorCollection::RED);
		bg_color->set_bright(EColorCollection::RED, 0.33333f);
	}

	if (button_type == Enums::ButtonType::BUTTON_CANCEL)
	{
		text_align_x = Enums::PositionMode::MID;

		position_mode_x = Enums::PositionMode::MID;
		position_mode_y = Enums::PositionMode::DOWN;

		master_position = Enums::PositionMaster::WINDOW;

		have_text = true;
		have_input_mode = false;
	}
	
}

void EButtonText::click_event()
{
	if (button_type == Enums::ButtonType::BUTTON_OPEN_DEFAULT_DROP_SOUND_WINDOW)
	{
		StaticData::window_find_item->is_active = true;
		StaticData::window_find_item->window_searchs_mode = Enums::WindowSearchMode::DEFAULT_DROP_SOUND;

		StaticData::window_find_item->button_event(this);

	}

	if (button_type == Enums::ButtonType::BUTTON_OPEN_CUSTOM_DROP_SOUND_WINDOW)
	{
		ESound::load_custom_sound();

		StaticData::window_find_item->is_active = true;
		StaticData::window_find_item->window_searchs_mode = Enums::WindowSearchMode::CUSTOM_DROP_SOUND;

		StaticData::window_find_item->button_event(this);
	}

	if (button_type == Enums::ButtonType::BUTTON_ADD_EXPLICIT_GROUP)
	{
		master_block->explicit_list.at(data_id)->is_active = true;
		master_block->explicit_list.at(data_id)->button_close->is_active = true;
		master_block->explicit_list.at(data_id)->button_add->is_active = true;

		StaticData::window_add_new_base_data->is_active = false;
	}

	if (button_type == Enums::ButtonType::BUTTON_ADD_EXPLICIT_ELEMENT)
	{

	}

	if (button_type == Enums::ButtonType::BUTTON_ACTIVE_BASE_CLASS_LIST)
	{
		master_block->plus_class_button_link->is_active = true;
		master_block->remove_base_class_button->is_active = true;
		master_block->is_base_class_active=true;

		StaticData::window_add_new_base_data->is_active = false;
	}

	if (button_type == Enums::ButtonType::BUTTON_ACTIVE_PROPHECY_LIST)
	{
		master_block->plus_prophecy_button_link->is_active = true;
		master_block->remove_prophecy_button->is_active = true;
		master_block->is_prophecy_active = true;

		StaticData::window_add_new_base_data->is_active = false;
	}

	if (button_type == Enums::ButtonType::BUTTON_ACTIVE_ENCHANTEMENT_LIST)
	{
		master_block->plus_enchantment_button_link->is_active = true;
		master_block->remove_enchantment_button->is_active = true;
		master_block->is_enchantment_active = true;

		StaticData::window_add_new_base_data->is_active = false;
	}
	if ((button_type == Enums::ButtonType::BUTTON_MINIMAP_ICON_SELECT_SIZE)&&(master_block->is_minimap_icon))
	{
		master_block->minimap_icon_size = Enums::IconSize(data_id);
		StaticData::window_filter_visual_editor->update_minimap_button();
	}

	if ((button_type == Enums::ButtonType::BUTTON_SET_RAY_IS_CONSTANT))
	{
		master_block->ray_is_temp = false;

		StaticData::window_filter_visual_editor->update_ray_button();
	}

	if ((button_type == Enums::ButtonType::BUTTON_SET_RAY_IS_TEMPOTARY))
	{
		master_block->ray_is_temp = true;

		StaticData::window_filter_visual_editor->update_ray_button();
	}

	if ((button_type == Enums::ButtonType::BUTTON_CANCEL_REMOVE_FILTER_BLOCK))
	{
		master_block->remove_timer = -100;

		is_active = false;
	}

	if ((button_type == Enums::ButtonType::BUTTON_NEW_LOOT_FILTER_OK))
	{
		if (StaticData::window_new_loot_filter->link_to_input_button->text != "")
		{
			EString::path_list.at(StaticData::active_tab) = EString::path_to_poe_folder + "/" + StaticData::window_new_loot_filter->link_to_input_button->text + ".filter";
			EString::opened_loot_filter_path = EString::path_to_poe_folder + "/" + StaticData::window_new_loot_filter->link_to_input_button->text + ".filter";

			StaticData::window_filter_block->filter_block_list.clear();
			StaticData::window_filter_block->filter_block_list.push_back(new FilterBlock());

			StaticData::window_new_loot_filter->is_active = false;

			StaticData::window_main->tab_list.at(StaticData::active_tab)->text = StaticData::window_new_loot_filter->link_to_input_button->text;


			if (EString::opened_loot_filter_path != "")
			{
				EFile::save_filter(EString::path_list.at(StaticData::active_tab));
			}
		}


	}

	if (button_type == Enums::ButtonType::BUTTON_SELECT_FONT)
	{
		//StaticData::window_select_font->is_active = false;
		if (!((button_type == Enums::ButtonType::BUTTON_SELECT_FONT) && (EFont::font_list.at(data_id)->is_not_cyrrilic) && (EString::active_localisation == Enums::LocalisationList::RU)))
		{
			EFont::active_font = EFont::font_list.at(data_id);

			EString::save_config();


			if (!StaticData::window_filter_block->is_active) { StaticData::window_find_item->is_active = true; }
		}
	}

	if (button_type == Enums::ButtonType::BUTTON_FILTER_BLOCK_TAB)
	{
		StaticData::active_tab = data_id;

		StaticData::window_filter_block = StaticData::filter_block_tab.at(data_id);
		EControl::window_list.at(0) = StaticData::filter_block_tab.at(data_id);

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
	}

	if (button_type == Enums::ButtonType::BUTTON_OPEN_PATTERN_WINDOW)
	{
		EString::load_loot_simulator_pattern_list();

		StaticData::window_find_item->window_searchs_mode = Enums::WindowSearchMode::LOOT_SIMULATOR_PATTERN;
		StaticData::window_find_item->is_active = true;
		StaticData::window_find_item->button_event(this);
	}


	if ((button_type == Enums::ButtonType::BUTTON_ACCEPT)||(button_type == Enums::ButtonType::BUTTON_CANCEL))
	{
		master_window->button_event(this);
	}
}

void EButtonText::input_event()
{
	if ((button_type == Enums::ButtonType::BUTTON_NEW_LOOT_FILTER_NAME))
	{
		if (text == "")
		{
			StaticData::window_new_loot_filter->link_to_accept_button->bg_color->set_alpha(EColorCollection::GRAY, 1.00f);
		}
		else
		{
			StaticData::window_new_loot_filter->link_to_accept_button->bg_color->set_alpha(EColorCollection::GREEN, 0.5f);
		}
	}
}

void EButtonText::update_localisation()
{
	//std::cout << "LOCAL" << std::endl;

	if (button_type == Enums::ButtonType::BUTTON_OPEN_DEFAULT_DROP_SOUND_WINDOW)
	{
		text = EString::localize_it("text_default_sound");
		description_text = EString::localize_it("description_default_sound");
	}

	if (button_type == Enums::ButtonType::BUTTON_OPEN_CUSTOM_DROP_SOUND_WINDOW)
	{
		text = EString::localize_it("text_custom_sound");
		description_text = EString::localize_it("desciption_custom_sound");
	}

	if (button_type == Enums::ButtonType::BUTTON_ADD_EXPLICIT_GROUP)
	{
		text = EString::localize_it("button_add_explicit_group");
		description_text = EString::localize_it("description_add_explicit_group");
	}

	if (button_type == Enums::ButtonType::BUTTON_ACTIVE_BASE_CLASS_LIST)
	{
		text = EString::localize_it("button_activate_class");
		description_text = EString::localize_it("description_activate_class");
	}

	if (button_type == Enums::ButtonType::BUTTON_ACTIVE_PROPHECY_LIST)
	{
		text = EString::localize_it("button_activate_prophecy");
		description_text = EString::localize_it("description_activate_prophecy");
	}

	if (button_type == Enums::ButtonType::BUTTON_SET_RAY_IS_TEMPOTARY)
	{
		text = EString::localize_it("button_set_ray_is_tempotary");
		description_text = EString::localize_it("description_tempotary_ray");
	}

	if (button_type == Enums::ButtonType::BUTTON_ADD_EXPLICIT_ELEMENT)
	{
		text = EString::localize_it("button_add_explicit_group");
		description_text = EString::localize_it("description_add_explicit_group");
	}

	if (button_type == Enums::ButtonType::BUTTON_SET_RAY_IS_CONSTANT)
	{
		text = EString::localize_it("button_set_ray_is_constant");
		description_text = EString::localize_it("description_set_ray_is_constant");
	}

	if (button_type == Enums::ButtonType::BUTTON_CANCEL_REMOVE_FILTER_BLOCK)
	{
		text = EString::localize_it("button_cancel_remove_filter_block");
		description_text = EString::localize_it("description_cancel_remove_filter_block");
	}

	if (button_type == Enums::ButtonType::BUTTON_NEW_LOOT_FILTER_NAME)
	{
		//text = EString::localize_it("button_new_loot_filter_name");
		description_text = EString::localize_it("description_new_loot_filter_name");
		input_hint = EString::localize_it("hint_new_loot_filter_name");
	}

	if (button_type == Enums::ButtonType::BUTTON_NEW_LOOT_FILTER_OK)
	{
		text = EString::localize_it("button_new_loot_filter_ok");
		description_text = EString::localize_it("description_new_loot_filter_ok");
	}

	if (button_type == Enums::ButtonType::BUTTON_MINIMAP_ICON_SELECT_SIZE)
	{
		if (data_id == 0)
		{
			text = EString::localize_it("text_minimap_icon_select_size_big");
			description_text = EString::localize_it("description_minimap_icon_select_size_big");
		}

		if (data_id == 1)
		{
			text = EString::localize_it("text_minimap_icon_select_size_medium");
			description_text = EString::localize_it("description_minimap_icon_select_size_medium");
		}
		if (data_id == 2)
		{
			text = EString::localize_it("text_minimap_icon_select_size_small");
			description_text = EString::localize_it("description_minimap_icon_select_size_small");
		}

	}


	if (button_type == Enums::ButtonType::BUTTON_SELECT_FONT)
	{
		if ((EFont::font_list.at(data_id)->is_not_cyrrilic) && (EString::active_localisation == Enums::LocalisationList::RU))
		{
			bg_color->set(EColorCollection::RED);
			force_font = EFont::font_list.at(1);

			description_text = "Кириллица не поддерживается!";
		}
		else
		{
			bg_color->set(EColorCollection::LIGHT_GRAY);
			description_text = "The quick brown fox jumps over the lazy dog(1234567890)";
		}
	}

	if (button_type == Enums::ButtonType::BUTTON_OPEN_PATTERN_WINDOW)
	{
		text = EString::localize_it("text_open_loot_simulator_pattern_window");
		description_text = EString::localize_it("description_open_loot_simulator_pattern_window");
	}

	if (button_type == Enums::ButtonType::BUTTON_ACCEPT)
	{
		text = EString::localize_it("text_accept");
		description_text = "";
	}

	if (button_type == Enums::ButtonType::BUTTON_CANCEL)
	{
		text = EString::localize_it("text_cancel");
		description_text = "";
	}


}

void EButtonText::update_additional(float _d)
{
	if (button_type == Enums::ButtonType::BUTTON_FILTER_BLOCK_TAB)
	{
		if (StaticData::active_tab == data_id)
		{rama_color->set(EColorCollection::YELLOW);}
		else
		{rama_color->set(EColorCollection::GRAY);}

		if (StaticData::filter_block_tab.at(data_id)->unsave_change)
		{text_color->set(EColorCollection::RED);}
		else
		{text_color->set(EColorCollection::BLACK);}
	}
}
