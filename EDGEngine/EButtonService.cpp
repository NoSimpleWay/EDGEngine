#include "EButtonService.h"

EButtonService::EButtonService(float _x, float _y, float _sx, float _sy, Enums::ButtonType _type) : EButton(_x, _y, _sx, _sy)
{
	button_type = _type;
	have_icon = true;
	have_text = false;
	have_description = true;
	description_text = "Write filter block data to console";

	have_rama = true;
	rama_thikness = 1;

	rama_color->set(EColorCollection::RED);
	master_position = Enums::FILTER_BLOCK;

	position_mode_x = Enums::PositionMode::RIGHT;
	position_mode_y = Enums::PositionMode::UP;

	if (button_type == Enums::ButtonType::BUTTON_SYS_VISUAL_MODE)
	{
		gabarite = DefaultGabarite::gabarite_visual_mode;
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
		std::cout << "Quality is active:" << master_block->is_item_qualityt_active << " " << master_block->item_quality_condition << master_block->item_quality << std::endl;
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
}
