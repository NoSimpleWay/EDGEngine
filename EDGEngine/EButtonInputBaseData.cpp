#include "EButtonInputBaseData.h"
#include "FilterBlockSeparator.h"
#include "StaticData.h"

EButtonInputBaseData::EButtonInputBaseData(float _x, float _y, float _sx, float _sy, Enums::ButtonType _type) : EButton(_x, _y, _sx, _sy)
{
	master_position = Enums::PositionMaster::FILTER_BLOCK;
	text_align_x = Enums::PositionMode::LEFT;

	button_x = _x;
	button_y = _y;

	button_size_x = _sx;
	button_size_y = _sy;

	button_type = _type;

	have_icon = false;
	have_text = true;
	have_description = true;
	have_input_mode = true;
	have_rama = true;
	input_only_numbers = true;
	dynamic_input_width = false;

	input_hint = "";

	rama_color->set(0.2f,0.1f,0.05f,0.55f);

	if (button_type == Enums::ButtonType::BUTTON_SEPARATOR_CAPTION_TEXT)
	{
		master_position = Enums::PositionMaster::SEPARATOR;
		input_only_numbers = false;
	}

	can_receive_paste = true;

}

void EButtonInputBaseData::click_event()
{
}



void EButtonInputBaseData::incoming_data(FilterBlock* _filter)
{
	text = button_type;

	if (button_type == Enums::ButtonType::BUTTON_DROP_LEVEL)	{text = std::to_string(_filter->required_level);}

	if (button_type == Enums::ButtonType::BUTTON_GEM_LEVEL)		{ text = std::to_string(_filter->gem_level); }
	if (button_type == Enums::ButtonType::BUTTON_HEIGHT)		{ text = std::to_string(_filter->item_height); }
	if (button_type == Enums::ButtonType::BUTTON_ITEM_LEVEL)	{ text = std::to_string(_filter->item_level); }
	if (button_type == Enums::ButtonType::BUTTON_LINKS)			{ text = std::to_string(_filter->links_count); }
	if (button_type == Enums::ButtonType::BUTTON_MAP_TIER)		{ text = std::to_string(_filter->map_tier); }
	if (button_type == Enums::ButtonType::BUTTON_QUALITY)		{ text = std::to_string(_filter->item_quality); }

	if (button_type == Enums::ButtonType::BUTTON_SOCKETS)		{ text = std::to_string(_filter->socket_count); }
	if (button_type == Enums::ButtonType::BUTTON_STACK_SIZE)	{ text = std::to_string(_filter->item_stack_size); }
	if (button_type == Enums::ButtonType::BUTTON_WIDTH)			{ text = std::to_string(_filter->item_width);}
}

void EButtonInputBaseData::input_finish_event()
{
	if (button_type == Enums::ButtonType::BUTTON_DROP_LEVEL) { master_block->required_level=std::stoi(text); }
	if (button_type == Enums::ButtonType::BUTTON_GEM_LEVEL) { master_block->gem_level=std::stoi(text); }
	if (button_type == Enums::ButtonType::BUTTON_HEIGHT) { master_block->item_height=std::stoi(text); }
	if (button_type == Enums::ButtonType::BUTTON_ITEM_LEVEL) { master_block->item_level=std::stoi(text); }
	if (button_type == Enums::ButtonType::BUTTON_LINKS) { master_block->links_count=std::stoi(text); }
	if (button_type == Enums::ButtonType::BUTTON_MAP_TIER) { master_block->map_tier=std::stoi(text); }
	if (button_type == Enums::ButtonType::BUTTON_QUALITY) { master_block->item_quality=std::stoi(text); }
	if (button_type == Enums::ButtonType::BUTTON_RARITY) { master_block->item_rarity=text; }
	if (button_type == Enums::ButtonType::BUTTON_SOCKETS) { master_block->socket_count=std::stoi(text); }
	if (button_type == Enums::ButtonType::BUTTON_STACK_SIZE) { master_block->item_stack_size=std::stoi(text); }
	if (button_type == Enums::ButtonType::BUTTON_WIDTH) { master_block->item_width=std::stoi(text); }

	if (button_type == Enums::ButtonType::BUTTON_SEPARATOR_CAPTION_TEXT)
	{
		master_separator->name = text;

		StaticData::window_filter_block->unsave_change = true;
	}



}

void EButtonInputBaseData::update_localisation()
{
}
