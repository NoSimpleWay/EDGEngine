#include "EButtonService.h"
#include "StaticData.h"

EButtonService::EButtonService(float _x, float _y, float _sx, float _sy, Enums::ButtonType _type) : EButton(_x, _y, _sx, _sy)
{
	button_type = _type;
	have_icon = true;
	have_text = false;
	have_description = true;
	description_text = "Write filter block data to console";

	have_rama = true;
	rama_thikness = 2;

	rama_color->set(EColorCollection::RED);
	rama_color_default->set(EColorCollection::RED);

	bg_color_default->set(bg_color);

	master_position = Enums::FILTER_BLOCK;

	position_mode_x = Enums::PositionMode::RIGHT;
	position_mode_y = Enums::PositionMode::UP;

	if (button_type == Enums::ButtonType::BUTTON_SYS_VISUAL_MODE)
	{
		gabarite = DefaultGabarite::gabarite_visual_mode;
	}

	if (button_type == Enums::ButtonType::BUTTON_SYS_PLAY_SOUND)
	{
		gabarite = DefaultGabarite::gabarite_play_sound;
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
}

void EButtonService::click_event()
{
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
		std::cout << "Sockets is active:" << master_block->is_socket_active << " " << master_block->socket_condition << master_block->socket_count << std::endl;
		std::cout << "Stack size is active:" << master_block->is_stack_size_active << " " << master_block->item_stack_size_condition << master_block->item_stack_size << std::endl;
		std::cout << "Width is active:" << master_block->is_item_width_active << " " << master_block->item_width_condition << master_block->item_width << std::endl;
	}

	if (button_type == Enums::ButtonType::BUTTON_SYS_VISUAL_MODE)
	{
		StaticData::window_filter_visual_editor->is_active = true;
		StaticData::window_filter_visual_editor->button_event(this);
	}

	if ((button_type == Enums::ButtonType::BUTTON_SYS_PLAY_SOUND))
	{
		std::cout << "Alert sound name: " << master_block->alert_sound_name << std::endl;
		if ((master_block->is_alert_sound) && (master_block->alert_sound_name != "")) { ESound::engine->play2D(ESound::default_drop_sound.at(master_block->alert_sound_id)); }

		if ((master_block->is_custom_alert_sound) && (master_block->custom_alert_sound_name != ""))
		{ ESound::engine->play2D(ESound::get_sound_by_name(master_block->custom_alert_sound_name));}
		else
		{
			std::cout << "Custom sound disabled" << std::endl;
		}
	}

	if ((button_type == Enums::ButtonType::BUTTON_MINIMAP_ICON_SELECT_SHAPE) && (master_block->is_minimap_icon))
	{
		master_block->minimap_icon_shape = Enums::IconShape(data_id);
		StaticData::window_filter_visual_editor->update_minimap_button();
	}

	if ((button_type == Enums::ButtonType::BUTTON_MINIMAP_ICON_SELECT_COLOR) && (master_block->is_minimap_icon))
	{
		master_block->minimap_icon_color = Enums::GameColors(data_id);
		StaticData::window_filter_visual_editor->update_minimap_button();
	}

	if (button_type == Enums::ButtonType::BUTTON_OPEN_LOOT_FILTER)
	{
		StaticData::window_find_item->is_active = true;
		StaticData::window_find_item->window_searchs_mode = Enums::WindowSearchMode::OPEN_LOOT_FILTER_SEARCH_LIST;
		StaticData::window_find_item->manual_event();
	}

	if (button_type == Enums::ButtonType::BUTTON_SAVE_LOOT_FILTER)
	{
		EFile::save_filter(EString::opened_loot_filter_path+"!");
	}
}
