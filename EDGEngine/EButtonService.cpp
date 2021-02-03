#include "EButtonService.h"
#include "StaticData.h"
#include "EButtonFilterItem.h"

EButtonService::EButtonService(float _x, float _y, float _sx, float _sy, Enums::ButtonType _type) : EButton(_x, _y, _sx, _sy)
{
	button_type = _type;
	have_icon = true;
	have_text = false;
	have_description = true;
	//description_text = "Write filter block data to console";

	have_rama = true;
	rama_thikness = 2;

	rama_color->set(EColorCollection::BLACK);
	rama_color_default->set(EColorCollection::RED);

	bg_color_default->set(bg_color);

	master_position = Enums::FILTER_BLOCK;

	position_mode_x = Enums::PositionMode::RIGHT;
	position_mode_y = Enums::PositionMode::UP;

	if (button_type == Enums::ButtonType::BUTTON_REMOVE_LOOT_FROM_SIMULATOR)
	{
		gabarite = DefaultGabarite::gabarite_remove;

		master_position = Enums::PositionMaster::WINDOW;

		position_mode_x = Enums::PositionMode::LEFT;
		position_mode_y = Enums::PositionMode::UP;
	}

	if (button_type == Enums::ButtonType::BUTTON_OPEN_MANUAL_LOOT_WINDOW)
	{
		gabarite = DefaultGabarite::gabarite_plus;

		master_position = Enums::PositionMaster::WINDOW;

		position_mode_x = Enums::PositionMode::LEFT;
		position_mode_y = Enums::PositionMode::UP;
	}

	if (button_type == Enums::ButtonType::BUTTON_SYS_VISUAL_MODE)
	{
		gabarite = DefaultGabarite::gabarite_visual_mode;

		position_mode_x = Enums::PositionMode::RIGHT;
		position_mode_y = Enums::PositionMode::DOWN;
	}

	if (button_type == Enums::ButtonType::BUTTON_SYS_PLAY_SOUND)
	{
		gabarite = DefaultGabarite::gabarite_play_sound;

		position_mode_x = Enums::PositionMode::RIGHT;
		position_mode_y = Enums::PositionMode::DOWN;
	}

	if (button_type == Enums::ButtonType::BUTTON_MINIMAP_ICON_SELECT_SHAPE)
	{
		master_position = Enums::PositionMaster::WINDOW;

		position_mode_x = Enums::PositionMode::LEFT;
		position_mode_y = Enums::PositionMode::DOWN;
	}

	if (button_type == Enums::ButtonType::BUTTON_MINIMAP_ICON_SELECT_COLOR)
	{
		master_position = Enums::PositionMaster::WINDOW;

		position_mode_x = Enums::PositionMode::LEFT;
		position_mode_y = Enums::PositionMode::DOWN;
	}

	if (button_type == Enums::ButtonType::BUTTON_OPEN_LOOT_FILTER)
	{
		master_position = Enums::PositionMaster::WINDOW;

		position_mode_x = Enums::PositionMode::LEFT;
		position_mode_y = Enums::PositionMode::UP;

		
		gabarite = DefaultGabarite::gabarite_button_load;



		
	}

	if (button_type == Enums::ButtonType::BUTTON_SAVE_LOOT_FILTER)
	{
		master_position = Enums::PositionMaster::WINDOW;

		position_mode_x = Enums::PositionMode::LEFT;
		position_mode_y = Enums::PositionMode::UP;

		gabarite = DefaultGabarite::gabarite_button_save;

		
	}

	if (button_type == Enums::ButtonType::BUTTON_NEW_LOOT_FILTER_WINDOW)
	{
		master_position = Enums::PositionMaster::WINDOW;

		position_mode_x = Enums::PositionMode::LEFT;
		position_mode_y = Enums::PositionMode::UP;

		gabarite = DefaultGabarite::gabarite_button_new;
	}

	if (button_type == Enums::ButtonType::BUTTON_PLUS_NEW_FILTER_BLOCK)
	{
		master_position = Enums::PositionMaster::FILTER_BLOCK;

		position_mode_x = Enums::PositionMode::RIGHT;
		position_mode_y = Enums::PositionMode::DOWN;

		gabarite = DefaultGabarite::gabarite_plus_gray;

		rama_thikness = 1.0f;
		rama_color->set_alpha(EColorCollection::BLACK, 0.75f);

		
	}

	if (button_type == Enums::ButtonType::BUTTON_MOVE_FILTER_BLOCK_UP)
	{
		master_position = Enums::PositionMaster::FILTER_BLOCK;

		position_mode_x = Enums::PositionMode::RIGHT;
		position_mode_y = Enums::PositionMode::DOWN;

		gabarite = DefaultGabarite::gabarite_up_gray;

		rama_thikness = 1.0f;
		rama_color->set_alpha(EColorCollection::BLACK, 0.75f);

		
	}

	if (button_type == Enums::ButtonType::BUTTON_MOVE_FILTER_BLOCK_DOWN)
	{
		master_position = Enums::PositionMaster::FILTER_BLOCK;

		position_mode_x = Enums::PositionMode::RIGHT;
		position_mode_y = Enums::PositionMode::DOWN;

		gabarite = DefaultGabarite::gabarite_down_gray;

		rama_thikness = 1.0f;
		rama_color->set_alpha(EColorCollection::BLACK, 0.75f);

		
	}

	if (button_type == Enums::ButtonType::BUTTON_REMOVE_BLOCK)
	{
		master_position = Enums::PositionMaster::FILTER_BLOCK;

		position_mode_x = Enums::PositionMode::RIGHT;
		position_mode_y = Enums::PositionMode::DOWN;

		gabarite = DefaultGabarite::gabarite_remove_block;

		rama_thikness = 1.0f;
		rama_color->set_alpha(EColorCollection::RED, 0.75f);
	}

	if (button_type == Enums::ButtonType::BUTTON_SHOW_HIDE)
	{
		master_position = Enums::PositionMaster::FILTER_BLOCK;

		position_mode_x = Enums::PositionMode::RIGHT;
		position_mode_y = Enums::PositionMode::DOWN;

		gabarite = DefaultGabarite::gabarite_gray_eye;

		rama_thikness = 1.0f;
		rama_color->set_alpha(EColorCollection::BLACK, 0.75f);
	}

	if (button_type == Enums::ButtonType::BUTTON_LOCALISATION_EN)
	{
		position_mode_x = Enums::PositionMode::MID;
		position_mode_y = Enums::PositionMode::MID;

		gabarite = DefaultGabarite::gabarite_flag_EN;
	}

	if (button_type == Enums::ButtonType::BUTTON_LOCALISATION_RU)
	{
		position_mode_x = Enums::PositionMode::MID;
		position_mode_y = Enums::PositionMode::MID;

		gabarite = DefaultGabarite::gabarite_flag_RU;
	}

	if (button_type == Enums::ButtonType::BUTTON_OPEN_SIMULATOR)
	{
		master_position = Enums::PositionMaster::WINDOW;

		position_mode_x = Enums::PositionMode::LEFT;
		position_mode_y = Enums::PositionMode::UP;

		gabarite = DefaultGabarite::gabarite_open_simulator;


	}


	if (button_type == Enums::ButtonType::BUTTON_CONFIGUE_FONT)
	{
		master_position = Enums::PositionMaster::WINDOW;

		position_mode_x = Enums::PositionMode::LEFT;
		position_mode_y = Enums::PositionMode::UP;

		gabarite = DefaultGabarite::gabarite_configue_font;


	}


	if (button_type == Enums::ButtonType::BUTTON_CONFIGUE_LANGUAGE)
	{
		master_position = Enums::PositionMaster::WINDOW;

		position_mode_x = Enums::PositionMode::LEFT;
		position_mode_y = Enums::PositionMode::UP;

		gabarite = DefaultGabarite::gabarite_configue_language;
	}

	if (button_type == Enums::ButtonType::BUTTON_CUT_FILTER_BLOCK)
	{
		master_position = Enums::PositionMaster::FILTER_BLOCK;

		position_mode_x = Enums::PositionMode::RIGHT;
		position_mode_y = Enums::PositionMode::DOWN;

		rama_thikness = 1.0f;
		rama_color->set_alpha(EColorCollection::BLACK, 0.75f);

		gabarite = DefaultGabarite::gabarite_cut_gray;
	}

	if (button_type == Enums::ButtonType::BUTTON_REFRESH_LOOT_SIMULATOR)
	{
		master_position = Enums::PositionMaster::WINDOW;

		position_mode_x = Enums::PositionMode::LEFT;
		position_mode_y = Enums::PositionMode::UP;

		rama_thikness = 1.0f;
		rama_color->set_alpha(EColorCollection::BLACK, 0.75f);

		gabarite = DefaultGabarite::gabarite_button_refresh;
	}

	if (button_type == Enums::ButtonType::BUTTON_CHANGE_BG_BRIGHT)
	{
		master_position = Enums::PositionMaster::WINDOW;

		position_mode_x = Enums::PositionMode::LEFT;
		position_mode_y = Enums::PositionMode::UP;

		rama_thikness = 1.0f;
		rama_color->set_alpha(EColorCollection::BLACK, 0.75f);

		gabarite = DefaultGabarite::gabarite_button_bright_bg;
	}

	if (button_type == Enums::ButtonType::BUTTON_CHANGE_BG_DARK)
	{
		master_position = Enums::PositionMaster::WINDOW;

		position_mode_x = Enums::PositionMode::LEFT;
		position_mode_y = Enums::PositionMode::UP;

		rama_thikness = 1.0f;
		rama_color->set_alpha(EColorCollection::BLACK, 0.75f);

		gabarite = DefaultGabarite::gabarite_button_dark_bg;
	}

	if (button_type == Enums::ButtonType::BUTTON_CLONE_FILTER_BLOCK)
	{
		master_position = Enums::PositionMaster::FILTER_BLOCK;

		position_mode_x = Enums::PositionMode::RIGHT;
		position_mode_y = Enums::PositionMode::DOWN;

		gabarite = DefaultGabarite::gabarite_button_clone;

		rama_thikness = 1.0f;
		rama_color->set_alpha(EColorCollection::BLACK, 0.75f);


	}

	if (button_type == Enums::ButtonType::BUTTON_ADD_SEPARATOR_TO_FILTER_BLOCK)
	{
		master_position = Enums::PositionMaster::FILTER_BLOCK;

		position_mode_x = Enums::PositionMode::RIGHT;
		position_mode_y = Enums::PositionMode::DOWN;

		gabarite = DefaultGabarite::gabarite_button_separator;

		rama_thikness = 1.0f;
		rama_color->set_alpha(EColorCollection::BLACK, 0.75f);


	}

	if (button_type == Enums::ButtonType::BUTTON_SET_BLOCK_CONTINUE)
	{
		master_position = Enums::PositionMaster::FILTER_BLOCK;

		position_mode_x = Enums::PositionMode::RIGHT;
		position_mode_y = Enums::PositionMode::DOWN;

		gabarite = DefaultGabarite::gabarite_button_continue_off;

		rama_thikness = 1.0f;
		rama_color->set_alpha(EColorCollection::BLACK, 0.75f);


	}

	if (button_type == Enums::ButtonType::BUTTON_REMOVE_SEPARATOR)
	{
		master_position = Enums::PositionMaster::SEPARATOR;

		position_mode_x = Enums::PositionMode::LEFT;
		position_mode_y = Enums::PositionMode::DOWN;

		gabarite = DefaultGabarite::gabarite_remove_block;

		rama_thikness = 1.0f;
		rama_color->set_alpha(EColorCollection::BLACK, 0.75f);

		
	

	}
	
	if (button_type == Enums::ButtonType::BUTTON_PASSIVE)
	{
		master_position = Enums::PositionMaster::WINDOW;
		position_mode_x = Enums::PositionMode::LEFT;
		position_mode_y = Enums::PositionMode::DOWN;

		rama_thikness = 1.0f;
		rama_color->set_alpha(EColorCollection::BLACK, 0.75f);

		have_bg = false;
	}

	if (button_type == Enums::ButtonType::BUTTON_CHECK_OIL)
	{
		master_position = Enums::PositionMaster::WINDOW;
		position_mode_x = Enums::PositionMode::LEFT;
		position_mode_y = Enums::PositionMode::UP;

		rama_thikness = 1.0f;
		rama_color->set_alpha(EColorCollection::BLACK, 0.75f);
	}

	if (button_type == Enums::ButtonType::BUTTON_OPEN_OIL_WINDOW)
	{
		master_position = Enums::PositionMaster::WINDOW;
		position_mode_x = Enums::PositionMode::LEFT;
		position_mode_y = Enums::PositionMode::UP;

		rama_thikness = 1.0f;
		rama_color->set_alpha(EColorCollection::BLACK, 0.75f);

		gabarite = DefaultGabarite::gabarite_button_oil;
	}



	if (button_type == Enums::ButtonType::BUTTON_AUTOGEN_SAVE_LOOT_FILTER)
	{
		master_position = Enums::PositionMaster::WINDOW;

		position_mode_x = Enums::PositionMode::LEFT;
		position_mode_y = Enums::PositionMode::UP;

		gabarite = DefaultGabarite::gabarite_save_autogen;


	}

	if (button_type == Enums::ButtonType::BUTTON_SWITCHER_INFLUENCE)
	{
		master_position = Enums::PositionMaster::FILTER_BLOCK;

		position_mode_x = Enums::PositionMode::LEFT;
		position_mode_y = Enums::PositionMode::DOWN;

		have_icon = true;

		//{gabarite = DefaultGabarite::gabarite_switcher_influence_shaper_deactivated; }
		gabarite = DefaultGabarite::gabarite_bg_noise;

		/*if (data_id == 0) { gabarite = DefaultGabarite::gabarite_switcher_influence_shaper_deactivated; }
		if (data_id == 1) { gabarite = DefaultGabarite::gabarite_switcher_influence_elder_deactivated; }

		if (data_id == 2) { gabarite = DefaultGabarite::gabarite_switcher_influence_crusader_deactivated; }
		if (data_id == 3) { gabarite = DefaultGabarite::gabarite_switcher_influence_redeemer_deactivated; }
		if (data_id == 4) { gabarite = DefaultGabarite::gabarite_switcher_influence_warlord_deactivated; }
		if (data_id == 5) { gabarite = DefaultGabarite::gabarite_switcher_influence_hunter_deactivated; }*/

		rama_thikness = 1.0f;
		rama_color->set_alpha(EColorCollection::GRAY, 0.75f);
		bg_color->set(EColorCollection::DARK_GRAY);
	}

	if (button_type == Enums::ButtonType::BUTTON_SWITCHER_SPECIAL_STATUS)
	{
		master_position = Enums::PositionMaster::FILTER_BLOCK;

		position_mode_x = Enums::PositionMode::LEFT;
		position_mode_y = Enums::PositionMode::DOWN;

		have_icon = true;

		gabarite = DefaultGabarite::gabarite_bg_noise;



		rama_thikness = 1.0f;
		rama_color->set_alpha(EColorCollection::GRAY, 0.75f);
		bg_color->set(EColorCollection::DARK_GRAY);
	}
}

void EButtonService::click_event()
{

	//description_text = std::to_string(button_type);

	if (button_type == Enums::ButtonType::BUTTON_FILTER_BLOCK_TO_CONSOLE)
	{
		std::cout << "=================================================" << std::endl;
		std::cout << "Drop level is active:" << master_block->is_required_level_active << " " << master_block->required_level_condition << master_block->required_level << std::endl;
		std::cout << "Gem level is active:" << master_block->is_gem_level_active << " " << master_block->gem_level_condition << master_block->gem_level << std::endl;
		std::cout << "Height is active:" << master_block->is_item_height_active << " " << master_block->item_height_condition << master_block->item_height << std::endl;
		std::cout << "Item level is active:" << master_block->is_item_level_active << " " << master_block->item_level_condition << master_block->item_level << std::endl;
		std::cout << "Links is active:" << master_block->is_links_active << " " << master_block->links_condition << master_block->links_count << std::endl;
		std::cout << "Map tier is active:" << master_block->is_map_tier_active << " " << master_block->map_tier_condition << master_block->map_tier << std::endl;
		std::cout << "Quality is active:" << master_block->is_item_quality_active << " " << master_block->item_quality_condition << master_block->item_quality << std::endl;
		std::cout << "Rarity is active:" << master_block->is_item_rarity_active << " " << master_block->rarity_condition << master_block->item_rarity << std::endl;
		//std::cout << "Sockets is active:" << master_block->is_socket_active << " " << master_block->socket_condition << master_block->socket_count << std::endl;
		std::cout << "Stack size is active:" << master_block->is_stack_size_active << " " << master_block->item_stack_size_condition << master_block->item_stack_size << std::endl;
		std::cout << "Width is active:" << master_block->is_item_width_active << " " << master_block->item_width_condition << master_block->item_width << std::endl;
	}
	if (button_type == Enums::ButtonType::BUTTON_REMOVE_LOOT_FROM_SIMULATOR)
	{
		StaticData::window_loot_simulator->main_loot_item_list.clear();
		for (int i = 0; i < 87; i++)
		for (int j = 0; j < 125; j++)
		{
			StaticData::window_loot_simulator->free_space[j][i] = true;
		}
	}

	if (button_type == Enums::ButtonType::BUTTON_OPEN_MANUAL_LOOT_WINDOW)
	{
		StaticData::window_manual_loot->is_active = true;
	}

	if (button_type == Enums::ButtonType::BUTTON_SYS_VISUAL_MODE)
	{
		StaticData::window_filter_visual_editor->is_active = true;
		StaticData::window_filter_visual_editor->button_event(this);

		if (StaticData::window_loot_simulator->is_active)
		{
			StaticData::window_filter_visual_editor->align_x = Enums::PositionMode::RIGHT;
			StaticData::window_loot_simulator->align_x = Enums::PositionMode::LEFT;
		}
		else
		{
			StaticData::window_filter_visual_editor->align_x = Enums::PositionMode::MID;
			StaticData::window_loot_simulator->align_x = Enums::PositionMode::MID;
		}
	}

	if ((button_type == Enums::ButtonType::BUTTON_SYS_PLAY_SOUND))
	{
		

		//std::cout << "Alert sound name: " << master_block->alert_sound_name << std::endl;

		if ((master_block->is_alert_sound) && (master_block->alert_sound_name != "") && (ESound::engine != NULL))
		{
			ESound::default_drop_sound.at(master_block->alert_sound_id)->setDefaultVolume (StaticData::window_filter_block->sound_volume);
			ESound::engine->play2D(ESound::default_drop_sound.at(master_block->alert_sound_id));
		}

		if ((master_block->is_custom_alert_sound) && (master_block->custom_alert_sound_name != "") && (ESound::engine != NULL))
		{
			ESound::get_sound_by_name(master_block->custom_alert_sound_name)->setDefaultVolume (StaticData::window_filter_block->sound_volume);
			ESound::engine->play2D(ESound::get_sound_by_name(master_block->custom_alert_sound_name));
		}
		else
		{
			//std::cout << "Custom sound disabled" << std::endl;
		}

		//std::cout << "id of this block = " << StaticData::window_filter_block->get_id_of_filter_block(master_block) << std::endl;
		//StaticData::window_filter_block->filter_block_list.
	}

	if ((button_type == Enums::ButtonType::BUTTON_MINIMAP_ICON_SELECT_SHAPE) && (master_block->is_minimap_icon))
	{
		master_block->minimap_icon_shape = Enums::IconShape(data_id);
		StaticData::window_filter_visual_editor->update_minimap_button();
	}

	if ((button_type == Enums::ButtonType::BUTTON_MINIMAP_ICON_SELECT_COLOR) && (master_block->is_minimap_icon))
	{
		master_block->minimap_icon_color = Enums::IconColor(data_id);
		StaticData::window_filter_visual_editor->update_minimap_button();
	}

	if (button_type == Enums::ButtonType::BUTTON_OPEN_LOOT_FILTER)
	{
		StaticData::window_add_new_base_data->is_active = false;
		StaticData::window_filter_visual_editor->is_active = false;
		StaticData::window_find_item->is_active = false;
		StaticData::window_manual_loot->is_active = false;
		StaticData::window_new_loot_filter->is_active = false;
		StaticData::window_socket_group->is_active = false;

		if (StaticData::window_filter_block->unsave_change)
		{ 
			StaticData::window_accept_cancel->window_mode = Enums::WindowAcceptCancelMode::AC_unsave_open;
			StaticData::window_accept_cancel->is_active = true;
		}
		else
		{
			EString::load_loot_filter_list();

			StaticData::window_find_item->is_active = true;
			StaticData::window_find_item->window_searchs_mode = Enums::WindowSearchMode::OPEN_LOOT_FILTER_SEARCH_LIST;
		
			StaticData::window_find_item->manual_event();
		}

		StaticData::window_filter_block->unsave_change = false;
		
	}

	if (button_type == Enums::ButtonType::BUTTON_SAVE_LOOT_FILTER)
	{
		if (EString::path_list.at(StaticData::active_tab) != "")
		{
			EFile::save_filter(EString::path_list.at(StaticData::active_tab), Enums::AutogenSaveMode::SOURCE, true);

			//EFile::save_filter(EString::path_to_poe_folder + StaticData::window_main->tab_list.at(StaticData::active_tab)->text + "_very_low.filter", Enums::AutogenSaveMode::VERY_LOW, true);
			StaticData::filter_block_tab.at(StaticData::active_tab)->unsave_change = false;
		}
	}

	if (button_type == Enums::ButtonType::BUTTON_AUTOGEN_SAVE_LOOT_FILTER)
	{
		if (EString::path_list.at(StaticData::active_tab) != "")
		{
			

			EFile::save_filter(EString::path_to_poe_folder + StaticData::window_main->tab_list.at(StaticData::active_tab)->text + EString::localize_it("autogen_very_low") + ".filter", Enums::AutogenSaveMode::VERY_LOW, false);
			EFile::save_filter(EString::path_to_poe_folder + StaticData::window_main->tab_list.at(StaticData::active_tab)->text + EString::localize_it("autogen_low") + ".filter", Enums::AutogenSaveMode::LOW, false);
			EFile::save_filter(EString::path_to_poe_folder + StaticData::window_main->tab_list.at(StaticData::active_tab)->text + EString::localize_it("autogen_default") + ".filter", Enums::AutogenSaveMode::DEFAULT, false);
			EFile::save_filter(EString::path_to_poe_folder + StaticData::window_main->tab_list.at(StaticData::active_tab)->text + EString::localize_it("autogen_rich") + ".filter", Enums::AutogenSaveMode::RICH, false);
			EFile::save_filter(EString::path_to_poe_folder + StaticData::window_main->tab_list.at(StaticData::active_tab)->text + EString::localize_it("autogen_very_rich") + ".filter", Enums::AutogenSaveMode::VERY_RICH, false);

			EFile::save_filter(EString::path_to_poe_folder + StaticData::window_main->tab_list.at(StaticData::active_tab)->text + ".filter", Enums::AutogenSaveMode::SOURCE, false);

			StaticData::filter_block_tab.at(StaticData::active_tab)->unsave_change = false;
		}
	}
	
	if (button_type == Enums::ButtonType::BUTTON_NEW_LOOT_FILTER_WINDOW)
	{
		StaticData::window_add_new_base_data->is_active = false;
		StaticData::window_filter_visual_editor->is_active = false;
		StaticData::window_find_item->is_active = false;
		StaticData::window_manual_loot->is_active = false;
		//StaticData::window_new_loot_filter->is_active = false;
		StaticData::window_socket_group->is_active = false;

		if (StaticData::window_filter_block->unsave_change)
		{
			StaticData::window_accept_cancel->window_mode = Enums::WindowAcceptCancelMode::AC_new_loot_filter;
			StaticData::window_accept_cancel->is_active = true;
		}
		else
		{
			StaticData::window_new_loot_filter->is_active = true;
			StaticData::window_new_loot_filter->link_to_input_button->is_input_mode_active = true;
		}
	}

	if ((button_type == Enums::ButtonType::BUTTON_SELECT_RAY_COLOR))
	{
		if (data_id >= 0)
		{
			master_block->is_ray = true;
			master_block->ray_color = Enums::GameColors(data_id);
		}
		else
		{
			master_block->is_ray = false;
		}

		StaticData::window_filter_visual_editor->update_ray_button();

	}

	if ((button_type == Enums::ButtonType::BUTTON_PLUS_NEW_FILTER_BLOCK))
	{
		FilterBlock* fb = new FilterBlock();
		fb->data_change();
		fb->highlight_time = 0.5f;

		StaticData::window_filter_block->filter_block_list.emplace
		(
			StaticData::window_filter_block->filter_block_list.begin() + StaticData::window_filter_block->get_id_of_filter_block(master_block),
			fb
		);

		for (int i = 0; i < StaticData::window_filter_block->filter_block_list.size(); i++)
		{StaticData::window_filter_block->filter_block_list.at(i)->order_id = i;}

		for (FilterBlockSeparator* sep : StaticData::window_filter_block->separator_list)
		{
			if (sep->separator_start > master_block->order_id - 1)
			{
				sep->separator_start++;
			}

			if (sep->separator_end >= master_block->order_id - 1)
			{
				sep->separator_end++;
			}
		}

		StaticData::window_filter_block->recalculate_filter_block_separator();

		fb->update_localisation();
	}

	if ((button_type == Enums::ButtonType::BUTTON_MOVE_FILTER_BLOCK_UP))
	{
		
		int position_id = StaticData::window_filter_block->get_id_of_filter_block(master_block);
		
		if (position_id > 0)
		{
			FilterBlock* swap = StaticData::window_filter_block->filter_block_list.at(position_id - 1);
			StaticData::window_filter_block->filter_block_list.at(position_id - 1) = StaticData::window_filter_block->filter_block_list.at(position_id);
			StaticData::window_filter_block->filter_block_list.at(position_id) = swap;

			master_block->highlight_time = 0.5f;
		}

		for (int i = 0; i < StaticData::window_filter_block->filter_block_list.size(); i++)
		{StaticData::window_filter_block->filter_block_list.at(i)->order_id = i;}

		StaticData::window_filter_block->recalculate_filter_block_separator();
	}

	if ((button_type == Enums::ButtonType::BUTTON_MOVE_FILTER_BLOCK_DOWN))
	{

		int position_id = StaticData::window_filter_block->get_id_of_filter_block(master_block);

		if (position_id < StaticData::window_filter_block->filter_block_list.size() - 1)
		{
			FilterBlock* swap = StaticData::window_filter_block->filter_block_list.at(position_id + 1);
			StaticData::window_filter_block->filter_block_list.at(position_id + 1) = StaticData::window_filter_block->filter_block_list.at(position_id);
			StaticData::window_filter_block->filter_block_list.at(position_id) = swap;

			master_block->highlight_time = 0.5f;
		}

		for (int i = 0; i < StaticData::window_filter_block->filter_block_list.size(); i++)
		{StaticData::window_filter_block->filter_block_list.at(i)->order_id = i;}

		StaticData::window_filter_block->recalculate_filter_block_separator();
	}

	if ((button_type == Enums::ButtonType::BUTTON_REMOVE_BLOCK))
	{
		if (master_block->remove_timer == -100)
		{
			master_block->remove_timer = 3.0f;

			master_block->link_to_cancel_remove_button->is_active = true;
		}
	}

	if ((button_type == Enums::ButtonType::BUTTON_SHOW_HIDE))
	{
		master_block->is_show = !master_block->is_show;
	}

	if ((button_type == Enums::ButtonType::BUTTON_LOCALISATION_EN))
	{
		EString::active_localisation = Enums::LocalisationList::EN;

		EString::load_localisation("EN");

		for (EWindow* w : EControl::window_list)
		{
			w->update_localisation();
		}

		master_window->is_active = false;

		if (!EString::font_is_configued)
		{
			StaticData::window_select_font->is_active = true;
		}
		else
		{
			if (!StaticData::window_filter_block->is_active) { StaticData::window_find_item->is_active = true; }
		}

		EString::save_config();
	}

	if ((button_type == Enums::ButtonType::BUTTON_LOCALISATION_RU))
	{
		EString::active_localisation = Enums::LocalisationList::RU;

		EString::load_localisation("RU");

		for (EWindow* w : EControl::window_list)
		{
			w->update_localisation();
		}

		master_window->is_active = false;

		if (!EString::font_is_configued)
		{
			StaticData::window_select_font->is_active = true;
		}
		else
		{
			if (!StaticData::window_filter_block->is_active) { StaticData::window_find_item->is_active = true; }
		}

		EString::save_config();
	}

	if (button_type == Enums::ButtonType::BUTTON_OPEN_SIMULATOR)
	{
		StaticData::window_loot_simulator->is_active = true;
		//StaticData::window_loot_simulator->manual_event();

		if (StaticData::window_filter_visual_editor->is_active)
		{
			StaticData::window_filter_visual_editor->align_x = Enums::PositionMode::RIGHT;
			StaticData::window_loot_simulator->align_x = Enums::PositionMode::LEFT;
		}
		else
		{
			StaticData::window_filter_visual_editor->align_x = Enums::PositionMode::MID;
			StaticData::window_loot_simulator->align_x = Enums::PositionMode::MID;
		}

	}	
	
	if (button_type == Enums::ButtonType::BUTTON_CONFIGUE_FONT)
	{
		StaticData::window_select_font->is_active = true;
	}

	if (button_type == Enums::ButtonType::BUTTON_CONFIGUE_LANGUAGE)
	{
		StaticData::window_select_localisation->is_active = true;
	}

	if (button_type == Enums::ButtonType::BUTTON_CUT_FILTER_BLOCK)
	{
		if (StaticData::window_filter_block->moved_filter_block == NULL)
		{

			StaticData::window_filter_block->moved_filter_block = master_block;
			StaticData::window_filter_block->filter_block_list.erase(StaticData::window_filter_block->filter_block_list.begin() + master_block->order_id);

			for (int i = 0; i < StaticData::window_filter_block->filter_block_list.size(); i++)
			{
				StaticData::window_filter_block->filter_block_list.at(i)->order_id = i;
			}
		}

		for (FilterBlockSeparator* sep : StaticData::window_filter_block->separator_list)
		{
			if (sep->separator_start > master_block->order_id)
			{
				sep->separator_start--;
			}

			if (sep->separator_end >= master_block->order_id)
			{
				sep->separator_end--;
			}
		}

		StaticData::window_filter_block->recalculate_filter_block_separator();
	}

	if (button_type == Enums::ButtonType::BUTTON_REFRESH_LOOT_SIMULATOR)
	{
		StaticData::window_loot_simulator->manual_event();
	}

	if (button_type == Enums::ButtonType::BUTTON_CHANGE_BG_BRIGHT)
	{
		StaticData::window_loot_simulator->is_bright_bg = true;
	}

	if (button_type == Enums::ButtonType::BUTTON_CHANGE_BG_DARK)
	{
		StaticData::window_loot_simulator->is_bright_bg = false;
	}

	if ((button_type == Enums::ButtonType::BUTTON_CLONE_FILTER_BLOCK))
	{
		FilterBlock* fb = new FilterBlock();
		fb->data_change();
		fb->highlight_time = 0.5f;

		StaticData::window_filter_block->filter_block_list.emplace
		(
			StaticData::window_filter_block->filter_block_list.begin() + StaticData::window_filter_block->get_id_of_filter_block(master_block),
			fb
		);

		for (int i = 0; i < StaticData::window_filter_block->filter_block_list.size(); i++)
		{
			StaticData::window_filter_block->filter_block_list.at(i)->order_id = i;
		}

		fb->is_bg_color_active = master_block->is_bg_color_active;
		fb->bg_alpha = master_block->bg_alpha;
		fb->bg_blue = master_block->bg_blue;
		fb->bg_green = master_block->bg_green;
		fb->bg_hue = master_block->bg_hue;
		fb->bg_red = master_block->bg_red;
		fb->bg_saturation = master_block->bg_saturation;
		fb->bg_value = master_block->bg_value;

		fb->is_font_size_active = master_block->is_font_size_active;
		fb->font_size = master_block->font_size;

		fb->is_text_color_active = master_block->is_text_color_active;
		fb->text_color_alpha = master_block->text_color_alpha;
		fb->text_color_blue = master_block->text_color_blue;
		fb->text_color_green = master_block->text_color_green;
		fb->text_color_hue = master_block->text_color_hue;
		fb->text_color_red = master_block->text_color_red;
		fb->text_color_saturation = master_block->text_color_saturation;
		fb->text_color_value = master_block->text_color_value;

		fb->is_rama_color_active = master_block->is_rama_color_active;
		fb->rama_alpha = master_block->rama_alpha;
		fb->rama_blue = master_block->rama_blue;
		fb->rama_green = master_block->rama_green;
		fb->rama_hue = master_block->rama_hue;
		fb->rama_red = master_block->rama_red;
		fb->rama_saturation = master_block->rama_saturation;
		fb->rama_value = master_block->rama_value;

		for (int i=0; i<fb->base_filter_data_name.size(); i++)
		{
			fb->base_filter_data_active.at(i) = master_block->base_filter_data_active.at(i);
			fb->base_filter_data_bool.at(i) = master_block->base_filter_data_bool.at(i);
		}

		fb->rarity_condition = master_block->rarity_condition;
		fb->item_rarity = master_block->item_rarity;

		fb->item_level_condition = master_block->item_level_condition;
		fb->item_level = master_block->item_level;

		fb->required_level_condition = master_block->required_level_condition;
		fb->required_level = master_block->required_level;

		fb->socket_condition = master_block->socket_condition;
		fb->socket_count = master_block->socket_count;

		fb->links_condition = master_block->links_condition;
		fb->links_count = master_block->links_count;

		fb->red_sockets_group = master_block->red_sockets_group;
		fb->green_sockets_group = master_block->green_sockets_group;
		fb->blue_sockets_group = master_block->blue_sockets_group;
		fb->white_sockets_group = master_block->white_sockets_group;

		fb->item_quality_condition = master_block->item_quality_condition;
		fb->item_quality = master_block->item_quality;

		fb->gem_level_condition = master_block->gem_level_condition;
		fb->gem_level = master_block->gem_level;

		fb->map_tier_condition = master_block->map_tier_condition;
		fb->map_tier = master_block->map_tier;

		fb->is_shaper_map = master_block->is_shaper_map;
		fb->is_elder_map = master_block->is_elder_map;


		fb->item_height_condition = master_block->item_height_condition;
		fb->item_height = master_block->item_height;

		fb->item_width_condition = master_block->item_width_condition;
		fb->item_width = master_block->item_width;

		fb->item_quality_condition = master_block->item_quality_condition;
		fb->item_quality = master_block->item_quality;

		fb->area_level_condition = master_block->area_level_condition;
		fb->area_level = master_block->area_level;

		fb->is_corrupted = master_block->is_corrupted;
		fb->is_shaper_item = master_block->is_shaper_item;
		fb->is_elder_item = master_block->is_elder_item;
		fb->is_synthesised_item = master_block->is_synthesised_item;
		fb->is_fractured_item = master_block->is_fractured_item;
		fb->is_identified = master_block->is_identified;

		
		for (EButton* b : master_block->filter_block_items_button_list)
		{
			EButton* but = new EButtonFilterItem(0,0,45.0f, 45.0f);
			but->text = b->text;
			but->description_text = b->description_text;
			but->data_id = b->data_id;
			but->data_string = b->data_string;
			but->gabarite = b->gabarite;
			

			but->master_block = fb;
			but->master_window = StaticData::window_filter_block;

			fb->filter_block_items_button_list.push_back(but);

			but->update_localisation();
		}


		fb->is_base_class_active = master_block->is_base_class_active;
		fb->remove_base_class_button->is_active = master_block->remove_base_class_button->is_active;
		fb->plus_class_button_link->is_active = master_block->plus_class_button_link->is_active;
		for (EButton* b : master_block->base_class_list)
		{
			EButtonExplicit* but = new EButtonExplicit(0, 0, 45.0f, 45.0f,Enums::ButtonType::BUTTON_CLASS_FILTER_BLOCK_LIST);
			but->text = b->text;
			but->description_text = b->description_text;
			but->data_id = b->data_id;
			but->data_string = b->data_string;
			but->gabarite = b->gabarite;
			but->button_size_x = b->button_size_x;
			but->button_size_y = b->button_size_y;
			but->button_min_size_x = b->button_min_size_x;

			but->master_block = fb;
			but->master_window = StaticData::window_filter_block;

			fb->base_class_list.push_back(but);
			fb->button_list.push_back(but);

			but->update_localisation();
		}

		fb->is_prophecy_active = master_block->is_prophecy_active;
		fb->remove_prophecy_button->is_active = master_block->remove_prophecy_button->is_active;
		fb->plus_prophecy_button_link->is_active = master_block->plus_prophecy_button_link->is_active;
		for (EButton* b : master_block->prophecy_list)
		{
			EButtonExplicit* but = new EButtonExplicit(0, 0, 45.0f, 45.0f, Enums::ButtonType::BUTTON_PROPHECY_FILTER_BLOCK_LIST);
			but->text = b->text;
			but->description_text = b->description_text;
			but->data_id = b->data_id;
			but->data_string = b->data_string;
			but->gabarite = b->gabarite;
			but->button_size_x = b->button_size_x;
			but->button_size_y = b->button_size_y;
			but->button_min_size_x = b->button_min_size_x;

			but->master_block = fb;
			but->master_window = StaticData::window_filter_block;

			fb->prophecy_list.push_back(but);
			fb->button_list.push_back(but);

			but->update_localisation();
		}

		fb->is_alert_sound = master_block->is_alert_sound;
		fb->alert_sound_id = master_block->alert_sound_id;
		fb->alert_sound_name = master_block->alert_sound_name;
		fb->is_positional_sound = master_block->is_positional_sound;

		fb->is_custom_alert_sound = master_block->is_custom_alert_sound;
		fb->custom_alert_sound_name = master_block->custom_alert_sound_name;
		fb->custom_sound_button_link = master_block->custom_sound_button_link;

		fb->is_ray = master_block->is_ray;
		fb->ray_color = master_block->ray_color;
		fb->ray_is_temp = master_block->ray_is_temp;

		fb->is_minimap_icon = master_block->is_minimap_icon;
		fb->minimap_icon_color = master_block->minimap_icon_color;
		fb->minimap_icon_shape = master_block->minimap_icon_shape;
		fb->minimap_icon_size = master_block->minimap_icon_size;

		fb->data_change();
		fb->update_localisation();

		for (FilterBlockSeparator* sep : StaticData::window_filter_block->separator_list)
		{
			if (sep->separator_start > master_block->order_id - 1)
			{
				sep->separator_start++;
			}

			if (sep->separator_end >= master_block->order_id - 1)
			{
				sep->separator_end++;
			}
		}

		for (int i = 0; i < master_block->special_status_button_list.size(); i++)
		{
			fb->special_status_button_list.at(i)->is_active = master_block->special_status_button_list.at(i)->is_active;

			fb->special_status_button_list.at(i)->bg_color->set(master_block->special_status_button_list.at(i)->bg_color);
			fb->special_status_button_list.at(i)->text_color->set(master_block->special_status_button_list.at(i)->text_color);

			fb->special_status_button_list.at(i)->gabarite = master_block->special_status_button_list.at(i)->gabarite;
		}

		for (int i = 0; i < master_block->vector_special_status.size(); i++)
		{
			fb->vector_special_status.at(i) = master_block->vector_special_status.at(i);
		}

		for (int i = 0; i < master_block->influences_button_list.size(); i++)
		{
			fb->influences_button_list.at(i)->is_active = master_block->influences_button_list.at(i)->is_active;

			fb->influences_button_list.at(i)->bg_color->set(master_block->influences_button_list.at(i)->bg_color);
			fb->influences_button_list.at(i)->text_color->set(master_block->influences_button_list.at(i)->text_color);

			fb->influences_button_list.at(i)->gabarite = master_block->influences_button_list.at(i)->gabarite;
		}

		for (int i = 0; i < master_block->vector_influence.size(); i++)
		{
			fb->vector_influence.at(i) = master_block->vector_influence.at(i);
		}

		fb->link_to_all_or_oneof->text = master_block->link_to_all_or_oneof->text;

		fb->link_to_all_or_oneof->bg_color->set(master_block->link_to_all_or_oneof->bg_color);
		fb->link_to_all_or_oneof->text_color->set(master_block->link_to_all_or_oneof->text_color);

		fb->influence_mode = master_block->influence_mode;

		for (int i = 0; i < master_block->base_data_button_collection_list.size(); i++)
		{
			FilterBlock::base_data_button_collection_struct* jc_bdbcs
			=
				FilterBlock::add_new_base_attribute
				(
					*FilterBlock::filter_block_data_attribute_registerer.at(master_block->base_data_button_collection_list.at(i)->target_id)->data_name, fb
				);

			if (master_block->base_data_button_collection_list.at(i)->condition_button != NULL)
			{
				jc_bdbcs->condition_button->text = master_block->base_data_button_collection_list.at(i)->condition_button->text;
				jc_bdbcs->condition_button->selected_element = master_block->base_data_button_collection_list.at(i)->condition_button->selected_element;
				jc_bdbcs->condition_button->update_localisation();
			}

			if (master_block->base_data_button_collection_list.at(i)->main_button != NULL)
			{
				jc_bdbcs->main_button->text = master_block->base_data_button_collection_list.at(i)->main_button->text;
				jc_bdbcs->main_button->selected_element = master_block->base_data_button_collection_list.at(i)->main_button->selected_element;
				jc_bdbcs->main_button->update_localisation();
			}

			//fb->base_data_button_collection_list.push_back(jc_bdbcs);

		}

		for (int i = 0; i < master_block->explicit_list.size(); i++)
		//for (ExplicitGroup* eg : master_block->explicit_list)
		{
			fb->explicit_list.at(i)->is_active = master_block->explicit_list.at(i)->is_active;

			for (int j = 0; j < master_block->explicit_list.at(i)->button_list.size(); j++)
			{
				EButtonExplicit* explicit_button = new EButtonExplicit(0, 0, 100, 20, Enums::ButtonType::BUTTON_EXPLICIT_FILTER_BLOCK_LIST);

				explicit_button->text = master_block->explicit_list.at(i)->button_list.at(j)->text;
				explicit_button->data_string = master_block->explicit_list.at(i)->button_list.at(j)->data_string;

				explicit_button->master_block = fb;
				explicit_button->master_window = StaticData::window_filter_block;

				explicit_button->button_size_x = EFont::get_width(EFont::active_font, explicit_button->text) + 5.0f;
				explicit_button->button_min_size_x = 30.0f;

				fb->explicit_list.at(i)->button_list.push_back(explicit_button);
				fb->button_list.push_back(explicit_button);

				explicit_button->is_active = master_block->explicit_list.at(i)->button_list.at(j)->is_active;
			}

			fb->explicit_list.at(i)->button_add->is_active = master_block->explicit_list.at(i)->button_add->is_active;
			fb->explicit_list.at(i)->button_close->is_active = master_block->explicit_list.at(i)->button_close->is_active;

		}

		StaticData::window_filter_block->recalculate_filter_block_separator();
	}

	if (button_type == Enums::ButtonType::BUTTON_ADD_SEPARATOR_TO_FILTER_BLOCK)
	{
		/*
			FilterBlockSeparator* sep = new FilterBlockSeparator();
			sep->separator_start = master_block->order_id;
			sep->separator_end = master_block->order_id;


			StaticData::window_filter_block->separator_list.push_back(sep);
			StaticData::window_filter_block->recalculate_filter_block_separator();
			//std::cout << "separator created" << std::endl;
		*/

		for (EButton* b : master_block->header_button_list)
		{
			b->is_active = true;
		}
	}

	if (button_type == Enums::ButtonType::BUTTON_SET_BLOCK_CONTINUE)
	{
		master_block->is_continue = !master_block->is_continue;

		if (master_block->is_continue)
		{
			gabarite = DefaultGabarite::gabarite_button_continue_on;
		}
		else
		{
			gabarite = DefaultGabarite::gabarite_button_continue_off;
		}

			//std::cout << "separator created" << std::endl;
	}
	
	if (button_type == Enums::ButtonType::BUTTON_SEPARATOR_COLLAPSE)
	{
		/*
		master_separator->is_collapsed = !master_separator->is_collapsed;

		for (int i = master_separator->separator_start; i <= master_separator->separator_end; i++)
		{
			StaticData::window_filter_block->filter_block_list.at(i)->hided_by_separator = master_separator->is_collapsed;
		}

		
		*/

		StaticData::window_filter_block->unsave_change = true;
		bool hiding_state = !master_block->hided_by_separator;

		for (int i = master_block->order_id; i < StaticData::window_filter_block->filter_block_list.size(); i++)
		{
			if ((i != master_block->order_id) && (StaticData::window_filter_block->filter_block_list.at(i)->link_to_header_separator->is_active))
			{
				break;
				//i = 999999;
			}

			StaticData::window_filter_block->filter_block_list.at(i)->hided_by_separator = !StaticData::window_filter_block->filter_block_list.at(i)->hided_by_separator;
		}


		if
		(
			(glfwGetKey(EWindow::main_window, GLFW_KEY_LEFT_SHIFT))
			||
			(glfwGetKey(EWindow::main_window, GLFW_KEY_RIGHT_SHIFT))
		)
		{
			if (button_type == Enums::ButtonType::BUTTON_SEPARATOR_COLLAPSE)
			{
				for (FilterBlock* f : StaticData::window_filter_block->filter_block_list)
				{
					f->hided_by_separator = false;
				}
			}
		}
	}	

	if (button_type == Enums::ButtonType::BUTTON_REMOVE_SEPARATOR)
	{
		/*
		StaticData::window_accept_cancel->window_mode = Enums::WindowAcceptCancelMode::AC_remove_separator;
		StaticData::window_accept_cancel->master_separator = master_separator;
		StaticData::window_accept_cancel->is_active = true;
		StaticData::window_accept_cancel->update_localisation();*/

		for (int i = master_block->order_id; i < StaticData::window_filter_block->filter_block_list.size(); i++)
		{
			if ((i != master_block->order_id) && (StaticData::window_filter_block->filter_block_list.at(i)->link_to_header_separator->is_active))
			{
				break;
				//i = 999999;
			}

			StaticData::window_filter_block->filter_block_list.at(i)->hided_by_separator = false;

			for (EButton* b : master_block->header_button_list)
			{
				b->is_active = false;
			}
		}

		for (int i = master_block->order_id; i < StaticData::window_filter_block->filter_block_list.size(); i++)
		{
			if ((i != master_block->order_id) && (StaticData::window_filter_block->filter_block_list.at(i)->link_to_header_separator->is_active))
			{
				break;
				//i = 999999;
			}

			StaticData::window_filter_block->filter_block_list.at(i)->disabled = false;
		}

		StaticData::window_filter_block->unsave_change = true;
		
	}

	if (button_type == Enums::ButtonType::BUTTON_CHECK_OIL)
	{
		StaticData::window_oil->oil_count.at(data_id) = 3;
		StaticData::window_oil->update_passives_button();
	}

	if (button_type == Enums::ButtonType::BUTTON_OPEN_OIL_WINDOW)
	{
		StaticData::window_oil->is_active = true;
		//StaticData::window_oil->update_passives_button();
	}

	if (button_type == Enums::ButtonType::BUTTON_DISABLE_FILTER_BLOCK)
	{
		//StaticData::window_filter_block->unsave_change = true;
		//bool hiding_state = !master_block->hided_by_separator;

		for (int i = master_block->order_id; i < StaticData::window_filter_block->filter_block_list.size(); i++)
		{
			if ((i != master_block->order_id) && (StaticData::window_filter_block->filter_block_list.at(i)->link_to_header_separator->is_active))
			{
				break;
				//i = 999999;
			}

			StaticData::window_filter_block->filter_block_list.at(i)->disabled = true;
		}

		StaticData::window_filter_block->unsave_change = true;
	}

	if (button_type == Enums::ButtonType::BUTTON_ENABLE_FILTER_BLOCK)
	{
		//StaticData::window_filter_block->unsave_change = true;
		//bool hiding_state = !master_block->hided_by_separator;

		for (int i = master_block->order_id; i < StaticData::window_filter_block->filter_block_list.size(); i++)
		{
			if ((i != master_block->order_id) && (StaticData::window_filter_block->filter_block_list.at(i)->link_to_header_separator->is_active))
			{
				break;
				//i = 999999;
			}

			StaticData::window_filter_block->filter_block_list.at(i)->disabled = false;
		}

		StaticData::window_filter_block->unsave_change = true;
	}
	
	if (button_type == Enums::ButtonType::BUTTON_SWITCHER_INFLUENCE)
	{


		master_block->vector_influence.at(data_id) = !master_block->vector_influence.at(data_id);

		if (master_block->vector_influence.at(data_id))
		{
			if (data_id == 0) { gabarite = DefaultGabarite::gabarite_switcher_influence_shaper; }
			if (data_id == 1) { gabarite = DefaultGabarite::gabarite_switcher_influence_elder; }

			if (data_id == 2) { gabarite = DefaultGabarite::gabarite_switcher_influence_crusader; }
			if (data_id == 3) { gabarite = DefaultGabarite::gabarite_switcher_influence_redeemer; }
			if (data_id == 4) { gabarite = DefaultGabarite::gabarite_switcher_influence_warlord; }
			if (data_id == 5) { gabarite = DefaultGabarite::gabarite_switcher_influence_hunter; }

			bg_color->set(EColorCollection::WHITE);
		}
		else
		{
			if (data_id == 0) { gabarite = DefaultGabarite::gabarite_switcher_influence_shaper_deactivated; }
			if (data_id == 1) { gabarite = DefaultGabarite::gabarite_switcher_influence_elder_deactivated; }

			if (data_id == 2) { gabarite = DefaultGabarite::gabarite_switcher_influence_crusader_deactivated; }
			if (data_id == 3) { gabarite = DefaultGabarite::gabarite_switcher_influence_redeemer_deactivated; }
			if (data_id == 4) { gabarite = DefaultGabarite::gabarite_switcher_influence_warlord_deactivated; }
			if (data_id == 5) { gabarite = DefaultGabarite::gabarite_switcher_influence_hunter_deactivated; }

			bg_color->set(EColorCollection::DARK_GRAY);
		}

	}
	
	if (button_type == Enums::ButtonType::BUTTON_SWITCHER_SPECIAL_STATUS)
	{


		//master_block->vector_special_status.at(data_id) = !master_block->vector_special_status.at(data_id);

		if (master_block->vector_special_status.at(data_id) == FilterBlock::SpecialStatusMode::SSM_DEACTIVATED)
		{
			master_block->vector_special_status.at(data_id) = FilterBlock::SpecialStatusMode::SSM_ON;

			if (data_id == FilterBlock::SpecialStatusList::SSL_CORRUPTED)			{ gabarite = DefaultGabarite::gabarite_switcher_vaaled; }
			if (data_id == FilterBlock::SpecialStatusList::SSL_ALTERNATE_QUALITY)	{ gabarite = DefaultGabarite::gabarite_switcher_alternate_gem; }
			if (data_id == FilterBlock::SpecialStatusList::SSL_BLIGHTED)			{ gabarite = DefaultGabarite::gabarite_switcher_blighted; }
			if (data_id == FilterBlock::SpecialStatusList::SSL_ENCHANTED)			{ gabarite = DefaultGabarite::gabarite_switcher_enchant; }
			if (data_id == FilterBlock::SpecialStatusList::SSL_FRACTURED)			{ gabarite = DefaultGabarite::gabarite_switcher_fractured; }
			if (data_id == FilterBlock::SpecialStatusList::SSL_IDENTIFIED)			{ gabarite = DefaultGabarite::gabarite_switcher_identified; }
			if (data_id == FilterBlock::SpecialStatusList::SSL_MIRRORED)			{ gabarite = DefaultGabarite::gabarite_switcher_mirrored; }
			if (data_id == FilterBlock::SpecialStatusList::SSL_REPLICA)				{ gabarite = DefaultGabarite::gabarite_switcher_replica; }
			if (data_id == FilterBlock::SpecialStatusList::SSL_SYNTHESISED)			{ gabarite = DefaultGabarite::gabarite_switcher_synthesised; }

			icon_color->set_alpha(EColorCollection::WHITE, 1.0f);
			bg_color->set(EColorCollection::WHITE);
		}
		else
		if (master_block->vector_special_status.at(data_id) == FilterBlock::SpecialStatusMode::SSM_ON)
		{
			master_block->vector_special_status.at(data_id) = FilterBlock::SpecialStatusMode::SSM_OFF;

			if (data_id == FilterBlock::SpecialStatusList::SSL_CORRUPTED)			{ gabarite = DefaultGabarite::gabarite_switcher_vaaled_off; }
			if (data_id == FilterBlock::SpecialStatusList::SSL_ALTERNATE_QUALITY)	{ gabarite = DefaultGabarite::gabarite_switcher_alternate_gem_off; }
			if (data_id == FilterBlock::SpecialStatusList::SSL_BLIGHTED)			{ gabarite = DefaultGabarite::gabarite_switcher_blighted_off; }
			if (data_id == FilterBlock::SpecialStatusList::SSL_ENCHANTED)			{ gabarite = DefaultGabarite::gabarite_switcher_enchant_off; }
			if (data_id == FilterBlock::SpecialStatusList::SSL_FRACTURED)			{ gabarite = DefaultGabarite::gabarite_switcher_fractured_off; }
			if (data_id == FilterBlock::SpecialStatusList::SSL_IDENTIFIED)			{ gabarite = DefaultGabarite::gabarite_switcher_identified_off; }
			if (data_id == FilterBlock::SpecialStatusList::SSL_MIRRORED)			{ gabarite = DefaultGabarite::gabarite_switcher_mirrored_off; }
			if (data_id == FilterBlock::SpecialStatusList::SSL_REPLICA)				{ gabarite = DefaultGabarite::gabarite_switcher_replica_off; }
			if (data_id == FilterBlock::SpecialStatusList::SSL_SYNTHESISED)			{ gabarite = DefaultGabarite::gabarite_switcher_synthesised_off; }

			bg_color->set(EColorCollection::RED);
		}
		else
		{
			master_block->vector_special_status.at(data_id) = FilterBlock::SpecialStatusMode::SSM_DEACTIVATED;

			if (data_id == FilterBlock::SpecialStatusList::SSL_CORRUPTED)			{ gabarite = DefaultGabarite::gabarite_switcher_vaaled_deactivated; }
			if (data_id == FilterBlock::SpecialStatusList::SSL_ALTERNATE_QUALITY)	{ gabarite = DefaultGabarite::gabarite_switcher_alternate_gem_deactivated; }
			if (data_id == FilterBlock::SpecialStatusList::SSL_BLIGHTED)			{ gabarite = DefaultGabarite::gabarite_switcher_blighted_deactivated; }
			if (data_id == FilterBlock::SpecialStatusList::SSL_ENCHANTED)			{ gabarite = DefaultGabarite::gabarite_switcher_enchant_deactivated; }
			if (data_id == FilterBlock::SpecialStatusList::SSL_FRACTURED)			{ gabarite = DefaultGabarite::gabarite_switcher_fractured_deactivated; }
			if (data_id == FilterBlock::SpecialStatusList::SSL_IDENTIFIED)			{ gabarite = DefaultGabarite::gabarite_switcher_identified_deactivated; }
			if (data_id == FilterBlock::SpecialStatusList::SSL_MIRRORED)			{ gabarite = DefaultGabarite::gabarite_switcher_mirrored_deactivated; }
			if (data_id == FilterBlock::SpecialStatusList::SSL_REPLICA)				{ gabarite = DefaultGabarite::gabarite_switcher_replica_deactivated; }
			if (data_id == FilterBlock::SpecialStatusList::SSL_SYNTHESISED)			{ gabarite = DefaultGabarite::gabarite_switcher_synthesised_deactivated; }
			
			icon_color->set_alpha(EColorCollection::WHITE, 0.5f);
			bg_color->set(EColorCollection::DARK_GRAY);
			
		}

	}
}

void EButtonService::right_click_event()
{
	if (button_type == Enums::ButtonType::BUTTON_CHECK_OIL)
	{
		StaticData::window_oil->oil_count.at(data_id) = 0;
		StaticData::window_oil->update_passives_button();
	}

	if (button_type == Enums::ButtonType::BUTTON_SEPARATOR_COLLAPSE)
	{
		for (FilterBlock* f : StaticData::window_filter_block->filter_block_list)
		{
			f->hided_by_separator = true;
		}
	}
}

void EButtonService::update_localisation()
{
	if (button_type == Enums::ButtonType::BUTTON_REMOVE_LOOT_FROM_SIMULATOR)
	{
		description_text = EString::localize_it("clear_loot_from_simulator");
	}

	if (button_type == Enums::ButtonType::BUTTON_OPEN_MANUAL_LOOT_WINDOW)
	{
		description_text = EString::localize_it("open_manual_window_localisation");
	}
	if (button_type == Enums::ButtonType::BUTTON_OPEN_LOOT_FILTER)
	{description_text = EString::localize_it("open_loot_filter");}

	if (button_type == Enums::ButtonType::BUTTON_SAVE_LOOT_FILTER)
	{description_text = EString::localize_it("save_loot_filter");}

	if (button_type == Enums::ButtonType::BUTTON_NEW_LOOT_FILTER_WINDOW)
	{description_text = EString::localize_it("create_new_loot_filter");}
	
	if (button_type == Enums::ButtonType::BUTTON_SYS_VISUAL_MODE)
	{description_text = EString::localize_it("description_button_visual_mode");}

	if (button_type == Enums::ButtonType::BUTTON_SYS_PLAY_SOUND)
	{description_text = EString::localize_it("description_play_sound");}

	if (button_type == Enums::ButtonType::BUTTON_OPEN_BASE_DATA_WINDOW)
	{description_text = EString::localize_it("description_new_base_data_vertical_list");}
	
	if (button_type == Enums::ButtonType::BUTTON_OPEN_EXPLICIT_PROPHECY_CLASS_WINDOW)
	{description_text = EString::localize_it("description_new_EPC");}

	if (button_type == Enums::ButtonType::BUTTON_SHOW_HIDE)
	{description_text = EString::localize_it("description_show_hide_block");}

	if (button_type == Enums::ButtonType::BUTTON_MOVE_FILTER_BLOCK_UP)
	{description_text = EString::localize_it("description_raise_block");}

	if (button_type == Enums::ButtonType::BUTTON_MOVE_FILTER_BLOCK_DOWN)
	{description_text = EString::localize_it("description_lower_block");}

	if (button_type == Enums::ButtonType::BUTTON_DISABLE_FILTER_BLOCK)
	{description_text = EString::localize_it("description_deactivate_block");}

	if (button_type == Enums::ButtonType::BUTTON_ENABLE_FILTER_BLOCK)
	{description_text = EString::localize_it("description_activate_block");}

	if (button_type == Enums::ButtonType::BUTTON_PLUS_NEW_FILTER_BLOCK)
	{description_text = EString::localize_it("description_add_new_filter_block");}
	

	if (button_type == Enums::ButtonType::BUTTON_REMOVE_BLOCK)
	{description_text = EString::localize_it("description_remove_block");}

	if (button_type == Enums::ButtonType::BUTTON_MINIMAP_ICON_SELECT_SHAPE)
	{description_text = EString::localize_it("description_minimap_icon_select_shape");}

	if (button_type == Enums::ButtonType::BUTTON_MINIMAP_ICON_SELECT_COLOR)
	{description_text = EString::localize_it("description_minimap_icon_select_color");}

	if (button_type == Enums::ButtonType::BUTTON_SELECT_RAY_COLOR)
	{
		if (data_id >= 0)
		{
			description_text = EString::localize_it("description_set_ray_color");
		}
		else
		{
			description_text = EString::localize_it("description_set_ray_deactivate");
		}
	}

	if (button_type == Enums::ButtonType::BUTTON_OPEN_SIMULATOR)
	{
		description_text = EString::localize_it("description_open_loot_simulator_window");
	}

		if (button_type == Enums::ButtonType::BUTTON_CONFIGUE_FONT)
	{description_text = EString::localize_it("description_configue_font");}

		if (button_type == Enums::ButtonType::BUTTON_CONFIGUE_LANGUAGE)
	{description_text = EString::localize_it("description_configue_language");}

		if (button_type == Enums::ButtonType::BUTTON_CHANGE_BG_BRIGHT)
	{description_text = EString::localize_it("description_bright_bg");}

		if (button_type == Enums::ButtonType::BUTTON_CHANGE_BG_DARK)
	{description_text = EString::localize_it("description_dark_bg");}

		if (button_type == Enums::ButtonType::BUTTON_REFRESH_LOOT_SIMULATOR)
	{description_text = EString::localize_it("description_refresh_loot_simulator");}

		if (button_type == Enums::ButtonType::BUTTON_CLONE_FILTER_BLOCK)
	{description_text = EString::localize_it("description_clone_filter_block");}

		if (button_type == Enums::ButtonType::BUTTON_ADD_SEPARATOR_TO_FILTER_BLOCK)
	{description_text = EString::localize_it("description_add_separator");}

		if (button_type == Enums::ButtonType::BUTTON_REMOVE_SEPARATOR)
	{description_text = EString::localize_it("description_remove_separator");}

		if (button_type == Enums::ButtonType::BUTTON_HEADER_SEPARATOR)
	{description_text = EString::localize_it("description_header_separator");}

		if (button_type == Enums::ButtonType::BUTTON_SEPARATOR_COLLAPSE)
	{description_text = EString::localize_it("description_collapse_separator");}

		if (button_type == Enums::ButtonType::BUTTON_CUT_FILTER_BLOCK)
	{description_text = EString::localize_it("description_cut_filter_block");}
		

	if (button_type == Enums::ButtonType::BUTTON_AUTOGEN_SAVE_LOOT_FILTER)
	{description_text = EString::localize_it("description_save_autogen_loot_filter");}


	if (button_type == Enums::ButtonType::BUTTON_OPEN_OIL_WINDOW)
	{description_text = EString::localize_it("description_open_oil_window");}
		
	if (button_type == Enums::ButtonType::BUTTON_CHECK_OIL)
	{
		description_text = EString::localize_it(EString::oil_name_list.at(data_id)) + "\\n\\n" + EString::localize_it("description_oil_check_button");
	}

	if (button_type == Enums::ButtonType::BUTTON_SET_BLOCK_CONTINUE)
	{

			description_text = EString::localize_it("description_continue");
	}

	if (button_type == Enums::ButtonType::BUTTON_SWITCHER_INFLUENCE)
	{
		if (data_id == FilterBlock::InfluenceList::IL_CRUSADER)		{ description_text = EString::localize_it("description_switcher_influence_crusader"); }
		if (data_id == FilterBlock::InfluenceList::IL_ELDER)		{ description_text = EString::localize_it("description_switcher_influence_elder"); }
		if (data_id == FilterBlock::InfluenceList::IL_HUNTER)		{ description_text = EString::localize_it("description_switcher_influence_hunter"); }
		if (data_id == FilterBlock::InfluenceList::IL_REDEEMER)		{ description_text = EString::localize_it("description_switcher_influence_redeemer"); }
		if (data_id == FilterBlock::InfluenceList::IL_SHAPER)		{ description_text = EString::localize_it("description_switcher_influence_shaper"); }
		if (data_id == FilterBlock::InfluenceList::IL_WARLORD)		{ description_text = EString::localize_it("description_switcher_influence_warlord"); }
	}

	if (button_type == Enums::ButtonType::BUTTON_SWITCHER_SPECIAL_STATUS)
	{
		if (master_block->vector_special_status.at(data_id) == FilterBlock::SpecialStatusMode::SSM_DEACTIVATED)
		{
			icon_color->set_alpha(EColorCollection::WHITE, 0.5f);
			bg_color->set(EColorCollection::DARK_GRAY);
		}
		else
		if (master_block->vector_special_status.at(data_id) == FilterBlock::SpecialStatusMode::SSM_OFF)
		{
			icon_color->set_alpha(EColorCollection::WHITE, 1.0f);
			bg_color->set(EColorCollection::RED);
		}
		else
		if (master_block->vector_special_status.at(data_id) == FilterBlock::SpecialStatusMode::SSM_ON)
		{
			icon_color->set_alpha(EColorCollection::WHITE, 1.0f);
			bg_color->set(EColorCollection::WHITE);
		}

		if (data_id == FilterBlock::SpecialStatusList::SSL_ALTERNATE_QUALITY)		{ description_text = EString::localize_it("description_special_status_alternate_quality"); }
		if (data_id == FilterBlock::SpecialStatusList::SSL_BLIGHTED)				{ description_text = EString::localize_it("description_special_status_blighted"); }
		if (data_id == FilterBlock::SpecialStatusList::SSL_CORRUPTED)				{ description_text = EString::localize_it("description_special_status_corrupted"); }
																					
		if (data_id == FilterBlock::SpecialStatusList::SSL_ENCHANTED)				{ description_text = EString::localize_it("description_special_status_enchanted"); }
		if (data_id == FilterBlock::SpecialStatusList::SSL_FRACTURED)				{ description_text = EString::localize_it("description_special_status_fractured"); }
		if (data_id == FilterBlock::SpecialStatusList::SSL_IDENTIFIED)				{ description_text = EString::localize_it("description_special_status_identified"); }
																					
		if (data_id == FilterBlock::SpecialStatusList::SSL_MIRRORED)				{ description_text = EString::localize_it("description_special_status_mirrored"); }
		if (data_id == FilterBlock::SpecialStatusList::SSL_REPLICA)					{ description_text = EString::localize_it("description_special_status_replica"); }
		if (data_id == FilterBlock::SpecialStatusList::SSL_SYNTHESISED)				{ description_text = EString::localize_it("description_special_status_synthesised"); }



	}


}
