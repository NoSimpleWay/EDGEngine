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

	

	if (button_type == Enums::ButtonType::BUTTON_AREA_LEVEL_FOR_LOOT_SIMULATOR)
	{
		text_align_x = Enums::PositionMode::LEFT;

		input_only_numbers = true;
		have_input_mode = true;

		position_mode_x = Enums::PositionMode::LEFT;
		position_mode_y = Enums::PositionMode::UP;

	
		master_position = Enums::PositionMaster::WINDOW;
		dynamic_input_width = false;

		//text = std::to_string(StaticData::window_loot_simulator->area_level);
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

		bg_color->set(0.5f,0.5f,1.0f,0.85f);
	}

	if (button_type == Enums::ButtonType::BUTTON_ACTIVE_BASE_CLASS_LIST)
	{
		text_align_x = Enums::PositionMode::MID;
		position_mode_x = Enums::PositionMode::MID;
		position_mode_y = Enums::PositionMode::UP;

		

		master_position = Enums::PositionMaster::WINDOW;

		bg_color->set(0.5f, 1.0f, 0.5f, 0.85f);
	}
	
	if (button_type == Enums::ButtonType::BUTTON_ACTIVE_PROPHECY_LIST)
	{
		text_align_x = Enums::PositionMode::MID;
		position_mode_x = Enums::PositionMode::MID;
		position_mode_y = Enums::PositionMode::UP;

		

		master_position = Enums::PositionMaster::WINDOW;

		bg_color->set(1.0f, 0.5f, 1.0f, 0.85f);
	}

	if (button_type == Enums::ButtonType::BUTTON_ACTIVE_ENCHANTEMENT_LIST)
	{
		text_align_x = Enums::PositionMode::MID;
		position_mode_x = Enums::PositionMode::MID;
		position_mode_y = Enums::PositionMode::UP;

		

		master_position = Enums::PositionMaster::WINDOW;

		bg_color->set(0.3f, 0.3f, 0.3f, 0.85f);
	}
	
	if (button_type == Enums::ButtonType::BUTTON_ACTIVE_CLUSTER_ENCHANTEMENT_LIST)
	{
		text_align_x = Enums::PositionMode::MID;
		position_mode_x = Enums::PositionMode::MID;
		position_mode_y = Enums::PositionMode::UP;

		

		master_position = Enums::PositionMaster::WINDOW;

		bg_color->set(1.0f, 1.0f, 1.0f, 0.85f);
		text_color->set(0.0f, 0.0f, 0.0f, 1.0f);
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

		bg_color->set_alpha(EColorCollection::BLACK, 0.85f);
		text_color->set(EColorCollection::WHITE);
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

	if (button_type == Enums::ButtonType::BUTTON_SELECT_LOOT_PATTERN)
	{
		text_align_x = Enums::PositionMode::MID;

		position_mode_x = Enums::PositionMode::LEFT;
		position_mode_y = Enums::PositionMode::UP;

		master_position = Enums::PositionMaster::WINDOW;

		have_text = true;
		have_input_mode = false;
	}
	
	if (button_type == Enums::ButtonType::BUTTON_INFLUENCE_ALL_OR_ONEOF)
	{
		text_align_x = Enums::PositionMode::MID;

		position_mode_x = Enums::PositionMode::LEFT;
		position_mode_y = Enums::PositionMode::DOWN;

		master_position = Enums::PositionMaster::FILTER_BLOCK;

		have_text = true;
		have_input_mode = false;

		text = EString::localize_it("influence_ignore");

		bg_color->set(EColorCollection::GRAY);
		text_color->set(EColorCollection::BLACK);
	}

	if (button_type == Enums::ButtonType::BUTTON_EXACT_MATCH)
	{
		text_align_x = Enums::PositionMode::MID;

		position_mode_x = Enums::PositionMode::LEFT;
		position_mode_y = Enums::PositionMode::DOWN;

		master_position = Enums::PositionMaster::FILTER_BLOCK;

		have_text = true;
		have_input_mode = false;

		text = EString::localize_it("non_exact_match");

		bg_color->set(EColorCollection::GRAY);
		text_color->set(EColorCollection::BLACK);
	}
}

void EButtonText::click_event()
{

	if (button_type == Enums::ButtonType::BUTTON_MANUAL_LOOT_ADD_TO_LOOT_SIMULATOR)
	{
		LootItem* loot = new LootItem();
		loot->base_class = StaticData::window_manual_loot->link_to_class_button->text;

		{loot->name = StaticData::window_manual_loot->link_to_item_button->data_string;; }

		for (DADItem* item : ItemList::item_list)
		{
			
			if (item->item_name == StaticData::window_manual_loot->link_to_item_button->data_string)
			{
				if (EString::active_localisation == Enums::LocalisationList::EN)
				{loot->name = item->item_name;}

				if (EString::active_localisation == Enums::LocalisationList::RU)
				{loot->name = item->item_name_ru;}
			}
		}

		StaticData::window_manual_loot->is_active = false;

		loot->data_name = StaticData::window_manual_loot->link_to_item_button->data_string;
		loot->rarity = StaticData::window_manual_loot->rarity;

		loot->sockets = min(StaticData::window_manual_loot->sockets, 6);


		loot->links = StaticData::window_manual_loot->links;
		loot->item_level = StaticData::window_manual_loot->item_level;
		

		int sc = 0;

		for (int i = 0; i < StaticData::window_manual_loot->sockets; i++)
		{
			sc = StaticData::window_manual_loot->socket_color.at(i);

			if (sc == 0) { loot->socket_color.push_back(EColorCollection::RED);		loot->red_socket++;}
			if (sc == 1) { loot->socket_color.push_back(EColorCollection::GREEN);	loot->green_socket++;}
			if (sc == 2) { loot->socket_color.push_back(EColorCollection::BLUE);	loot->blue_socket++;}
			if (sc == 3) { loot->socket_color.push_back(EColorCollection::WHITE);	loot->white_socket++;}
			if (sc == 4) { loot->socket_color.push_back(EColorCollection::BLACK);	loot->abyss_socket++;}
			if (sc == 5) { loot->socket_color.push_back(EColorCollection::YELLOW);	loot->delve_socket++;}
		}

		for (int i = 0; i < StaticData::window_manual_loot->links; i++)
		{
			if (sc == 0) { loot->socket_color.push_back(EColorCollection::RED);		loot->linked_red_socket++; }
			if (sc == 1) { loot->socket_color.push_back(EColorCollection::GREEN);	loot->linked_green_socket++; }
			if (sc == 2) { loot->socket_color.push_back(EColorCollection::BLUE);	loot->linked_blue_socket++; }
			if (sc == 3) { loot->socket_color.push_back(EColorCollection::WHITE);	loot->linked_white_socket++; }
		}

		loot->red_socket			= min(loot->red_socket,				loot->sockets);
		loot->green_socket			= min(loot->green_socket,			loot->sockets);
		loot->blue_socket			= min(loot->blue_socket,			loot->sockets);
		loot->white_socket			= min(loot->white_socket,			loot->sockets);
		loot->abyss_socket			= min(loot->abyss_socket,			loot->sockets);
		loot->delve_socket			= min(loot->delve_socket,			loot->sockets);

		loot->linked_red_socket		= min(loot->linked_red_socket,		loot->links);
		loot->linked_green_socket	= min(loot->linked_green_socket,	loot->links);
		loot->linked_blue_socket	= min(loot->linked_blue_socket,		loot->links);
		loot->linked_white_socket	= min(loot->linked_white_socket,	loot->links);

		loot->quality = StaticData::window_manual_loot->quality;
		loot->gem_level = StaticData::window_manual_loot->gem_level;

		loot->map_tier = StaticData::window_manual_loot->map_tier;

		loot->is_elder_map = StaticData::window_manual_loot->elder_map;
		loot->is_shaper_map = StaticData::window_manual_loot->shaper_map;

		loot->is_blighted_map = StaticData::window_manual_loot->blighted_map;

		loot->identified = StaticData::window_manual_loot->identified;
		loot->quantity = StaticData::window_manual_loot->quantity;

		loot->height = StaticData::window_manual_loot->item_height;
		loot->width = StaticData::window_manual_loot->item_width;

		loot->corrupted = StaticData::window_manual_loot->is_corrupted;
		loot->corrupted_mods = StaticData::window_manual_loot->corruption_count;

		loot->shaper_item = StaticData::window_manual_loot->shaper_influence;
		loot->elder_item = StaticData::window_manual_loot->elder_influence;
		loot->crusader_item = StaticData::window_manual_loot->crusader_influence;
		loot->redeemer_item = StaticData::window_manual_loot->redeemer_influence;
		loot->hunter_item = StaticData::window_manual_loot->hunter_influence;
		loot->warlord_item = StaticData::window_manual_loot->warlord_influence;

		loot->fractured_item = StaticData::window_manual_loot->is_fractured;
		loot->synthesised_item = StaticData::window_manual_loot->is_synthesised;

		loot->any_enchantment = StaticData::window_manual_loot->is_enchanted;
		loot->is_mirrored = StaticData::window_manual_loot->is_mirrored;

		loot->cluster_small_passives_count = StaticData::window_manual_loot->cluster_jewel_small_passives_count;
		loot->alternate_quality_type = StaticData::window_manual_loot->selected_alternate_quality;
		loot->is_alternate_quality = StaticData::window_manual_loot->any_alternate_quality;

		StaticData::window_loot_simulator->put_loot(loot);
	}

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

		master_block->is_explicit = true;

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

	if (button_type == Enums::ButtonType::BUTTON_ACTIVE_CLUSTER_ENCHANTEMENT_LIST)
	{
		master_block->plus_cluster_enchantment_button_link->is_active = true;
		master_block->remove_cluster_enchantment_button->is_active = true;
		master_block->is_cluster_enchantment_active = true;

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

			FilterBlock* new_fb = new FilterBlock();

			StaticData::window_filter_block->filter_block_list.clear();
			StaticData::window_filter_block->filter_block_list.push_back(new_fb);

			StaticData::window_new_loot_filter->is_active = false;

			StaticData::window_main->tab_list.at(StaticData::active_tab)->text = StaticData::window_new_loot_filter->link_to_input_button->text;


			if (EString::opened_loot_filter_path != "")
			{
				//EFile::save_filter(EString::path_list.at(StaticData::active_tab));
				EFile::save_filter(EString::path_list.at(StaticData::active_tab), Enums::AutogenSaveMode::VERY_LOW, true);
			}

			new_fb->update_localisation();

			EControl::block_scroll = 0;
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

		StaticData::window_select_loot_pattern->is_active = true;
		StaticData::window_select_loot_pattern->manual_event();
		/*
		EString::load_loot_simulator_pattern_list();


		StaticData::window_find_item->window_searchs_mode = Enums::WindowSearchMode::LOOT_SIMULATOR_PATTERN;
		StaticData::window_find_item->is_active = true;
		StaticData::window_find_item->button_event(this);*/
	}


	if ((button_type == Enums::ButtonType::BUTTON_ACCEPT)||(button_type == Enums::ButtonType::BUTTON_CANCEL))
	{
		master_window->button_event(this);
	}

	if (button_type == Enums::ButtonType::BUTTON_SELECT_LOOT_PATTERN)
	{
		EString::load_loot_pattern(EString::loot_pattern_path.at(data_id));
		StaticData::window_loot_simulator->manual_event();

		master_window->is_active = false;
	}

	if (button_type == Enums::ButtonType::BUTTON_INFLUENCE_ALL_OR_ONEOF)
	{
		if (master_block != NULL)
		{
			if (master_block->influence_mode == FilterBlock::InfluenceMode::IM_ONE_OF)
			{
				master_block->influence_mode = FilterBlock::InfluenceMode::IM_ALL;
				text = EString::localize_it("influence_all");

				bg_color->set(EColorCollection::WHITE);
				text_color->set(EColorCollection::BLACK);

				for (EButton* b : master_block->influences_button_list)
				{b->is_active = true;}
			}
			else
			if (master_block->influence_mode == FilterBlock::InfluenceMode::IM_ALL)
			{
				master_block->influence_mode = FilterBlock::InfluenceMode::IM_NONE;
				text = EString::localize_it("influence_none");

				bg_color->set(EColorCollection::RED);
				text_color->set(EColorCollection::WHITE);
				for (EButton* b : master_block->influences_button_list)
				{b->is_active = false;}

			}
			else
			if (master_block->influence_mode == FilterBlock::InfluenceMode::IM_NONE)
			{
				master_block->influence_mode = FilterBlock::InfluenceMode::IM_IGNORE;
				text = EString::localize_it("influence_ignore");

				for (EButton* b : master_block->influences_button_list)
				{b->is_active = false;}

				bg_color->set(EColorCollection::GRAY);
				text_color->set(EColorCollection::BLACK);
			}
			else
			if (master_block->influence_mode == FilterBlock::InfluenceMode::IM_IGNORE)
			{
				master_block->influence_mode = FilterBlock::InfluenceMode::IM_ONE_OF;
				text = EString::localize_it("influence_oneof");

				for (EButton* b : master_block->influences_button_list)
				{b->is_active = true;}

				bg_color->set(EColorCollection::WHITE);
				text_color->set(EColorCollection::BLACK);
			}
		}
	}

	if (button_type == Enums::ButtonType::BUTTON_EXACT_MATCH)
	{
		master_block->is_exact_match = !master_block->is_exact_match;

		if (master_block->is_exact_match)
		{
			text_color->set(EColorCollection::PINK);
			bg_color->set(EColorCollection::SHAPER);
			text = EString::localize_it("exact_match");

			for (EButton* b : master_block->filter_block_items_button_list)
			{
				b->rama_color->set(EColorCollection::PINK);
			}
		}
		else
		{
			text_color->set(EColorCollection::LIGHT_GRAY);
			bg_color->set(EColorCollection::GRAY);
			text = EString::localize_it("non_exact_match");

			for (EButton* b : master_block->filter_block_items_button_list)
			{
				b->rama_color->set(0.4f, 0.3f, 0.1f, 0.6f);
			}
		}
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

void EButtonText::input_finish_event()
{

	/*if (button_type == Enums::ButtonType::BUTTON_AREA_LEVEL_FOR_LOOT_SIMULATOR)
	{
		if ((text != "") && (text.length() <= 3)) { StaticData::window_loot_simulator->area_level = std::stoi(text); }
	}*/

	if (button_type == Enums::ButtonType::BUTTON_MANUAL_LOOT_SOCKET_COUNT)
	{
		if ((text != "") && (text.length() <= 1)) {	StaticData::window_manual_loot->sockets = std::stoi(text); }
	}

	if (button_type == Enums::ButtonType::BUTTON_MANUAL_LOOT_ITEM_LEVEL)
	{
		if ((text != "") && (text.length() <= 3)) { StaticData::window_manual_loot->item_level = std::stoi(text); }
	}

	if (button_type == Enums::ButtonType::BUTTON_MANUAL_LOOT_LINK)
	{
		if ((text != "") && (text.length() <= 1)) { StaticData::window_manual_loot->links = std::stoi(text); }
	}

	if (button_type == Enums::ButtonType::BUTTON_MANUAL_LOOT_QUALITY)
	{
		if ((text != "") && (text.length() <= 2)) { StaticData::window_manual_loot->quality = std::stoi(text); }
	}

	if (button_type == Enums::ButtonType::BUTTON_MANUAL_LOOT_GEM_LEVEL)
	{
		if ((text != "") && (text.length() <= 2)) { StaticData::window_manual_loot->gem_level = std::stoi(text);	}
	}

	if (button_type == Enums::ButtonType::BUTTON_MANUAL_LOOT_QUANTITY)
	{
		if ((text != "") && (text.length() <= 5)) { StaticData::window_manual_loot->quantity = std::stoi(text); }
	}

	if (button_type == Enums::ButtonType::BUTTON_MANUAL_LOOT_HEIGHT)
	{
		if ((text != "") && (text.length() <= 1)) { StaticData::window_manual_loot->item_height = std::stoi(text); }
	}
	
	if (button_type == Enums::ButtonType::BUTTON_MANUAL_LOOT_WIDTH)
	{
		if ((text != "") && (text.length() <= 1)) { StaticData::window_manual_loot->item_width = std::stoi(text); }
	}
	
	if (button_type == Enums::ButtonType::BUTTON_MANUAL_LOOT_CORRUPTION_COUNT)
	{
		if ((text != "") && (text.length() <= 1)) { StaticData::window_manual_loot->corruption_count = std::stoi(text); }
	}

	if (button_type == Enums::ButtonType::BUTTON_MANUAL_LOOT_CLUSTER_PASSIVES_COUNT)
	{
		if ((text != "") && (text.length() <= 1)) { StaticData::window_manual_loot->cluster_jewel_small_passives_count = std::stoi(text); }
	}




	if (button_type == Enums::ButtonType::BUTTON_AREA_LEVEL_FOR_LOOT_SIMULATOR)
	{
		if ((text != "") && (text.length() <= 3)) { StaticData::window_loot_simulator->area_level = std::stoi(text); }
	}

}

void EButtonText::update_localisation()
{
	if (button_type == Enums::ButtonType::BUTTON_MANUAL_LOOT_ADD_TO_LOOT_SIMULATOR)
	{
		text = EString::localize_it("manual_loot_text_add_loot_to_simulator");
	}

	//std::cout << "LOCAL" << std::endl;
	if (button_type == Enums::ButtonType::BUTTON_AREA_LEVEL_FOR_LOOT_SIMULATOR)
	{
		//text = EString::localize_it("text_default_sound");
		description_text = EString::localize_it("description_area_level_for_loot_simulator");
	}

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

	if (button_type == Enums::ButtonType::BUTTON_ACTIVE_ENCHANTEMENT_LIST)
	{
		text = EString::localize_it("button_add_enchantment_list");
		description_text = EString::localize_it("description_add_enchantment_list");
	}

	if (button_type == Enums::ButtonType::BUTTON_ACTIVE_CLUSTER_ENCHANTEMENT_LIST)
	{
		text = EString::localize_it("button_add_cluster_enchantment_list");
		description_text = EString::localize_it("description_add_enchantment_list");
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

	if (button_type == Enums::ButtonType::BUTTON_HEADER_SEPARATOR)
	{
		description_text = EString::localize_it("description_header_separator");
		input_hint = EString::localize_it("hint_header_separator");
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

	if (button_type == Enums::ButtonType::BUTTON_SELECT_LOOT_PATTERN)
	{
		if (EString::active_localisation == Enums::LocalisationList::EN)
		{text = EString::loot_pattern_name.at(data_id);}

		if (EString::active_localisation == Enums::LocalisationList::RU)
		{text = EString::loot_pattern_name_ru.at(data_id);}

		///

		if (EString::active_localisation == Enums::LocalisationList::EN)
		{description_text = EString::loot_pattern_description.at(data_id);}

		if (EString::active_localisation == Enums::LocalisationList::RU)
		{description_text = EString::loot_pattern_description_ru.at(data_id);}

		//description_text = "";
	}

	if (button_type == Enums::ButtonType::BUTTON_INFLUENCE_ALL_OR_ONEOF)
	{
		if (master_block->influence_mode == FilterBlock::InfluenceMode::IM_ONE_OF)
		{
			text = EString::localize_it("influence_oneof");
		}
		if (master_block->influence_mode == FilterBlock::InfluenceMode::IM_ALL)
		{
			text = EString::localize_it("influence_all");
		}
		if (master_block->influence_mode == FilterBlock::InfluenceMode::IM_NONE)
		{
			text = EString::localize_it("influence_none");
		}

		description_text = EString::localize_it("influence_description");
	}

	if (button_type == Enums::ButtonType::BUTTON_EXACT_MATCH)
	{

		if (master_block->is_exact_match)
		{
			text_color->set(EColorCollection::PINK);
			bg_color->set(EColorCollection::SHAPER);
			text = EString::localize_it("exact_match");
		}
		else
		{
			text_color->set(EColorCollection::LIGHT_GRAY);
			bg_color->set(EColorCollection::GRAY);
			text = EString::localize_it("non_exact_match");
		}

		description_text = EString::localize_it("exact_match_description");
	}

}

void EButtonText::update_additional(float _d)
{
	if (button_type == Enums::ButtonType::BUTTON_FILTER_BLOCK_TAB)
	{
		if (StaticData::active_tab == data_id)
		{
			text_color->set(EColorCollection::SHAPER_LIGHT);
			rama_color->set(EColorCollection::SHAPER);
			bg_color->set_alpha(EColorCollection::SHAPER, 0.55f);
		}
		else
		{
			text_color->set_alpha(EColorCollection::SHAPER, 0.95f);
			rama_color->set(EColorCollection::BLACK);
			bg_color->set_alpha(EColorCollection::BLACK, 0.85f);
		}

		if (StaticData::filter_block_tab.at(data_id)->unsave_change)
		{text_color->set(EColorCollection::RED);}
		//else
		//{text_color->set(EColorCollection::PINK);}
	}
}
