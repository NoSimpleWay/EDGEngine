#include "EButtonDropCondition.h"
#include "StaticData.h"





EButtonDropCondition::EButtonDropCondition(float _x, float _y, float _sx, float _sy, Enums::ButtonType _type) : EButton(_x, _y, _sx, _sy)   // ����������� ������ SecondClass �������� ����������� ������ FirstClass
{
	button_type = _type;

	master_position = Enums::PositionMaster::FILTER_BLOCK;
	text_align_x = Enums::PositionMode::MID;

	have_text = true;
	have_icon = false;

	rama_thikness = 1;
	can_be_removed = false;



	have_rama = true;
	rama_color->set(0.05f, 0.15f, 0.25f, 0.6f);
	is_drop_list = true;

	drop_elements = 5;

	drop_text.push_back("<=");
	drop_text.push_back("<");
	drop_text.push_back("=");
	drop_text.push_back(">");
	drop_text.push_back(">=");
}

void EButtonDropCondition::click_event()
{
}

void EButtonDropCondition::incoming_data(FilterBlock* _filter)
{
	if (button_type == Enums::ButtonType::BUTTON_CONDITION_DROP_LEVEL)		{ text = _filter->required_level_condition; }
	if (button_type == Enums::ButtonType::BUTTON_CONDITION_GEM_LEVEL)		{ text = _filter->gem_level_condition; }
	if (button_type == Enums::ButtonType::BUTTON_CONDITION_HEIGHT)			{ text = _filter->item_height_condition; }
	if (button_type == Enums::ButtonType::BUTTON_CONDITION_ITEM_LEVEL)		{ text = _filter->item_level_condition; }
	if (button_type == Enums::ButtonType::BUTTON_CONDITION_LINKS)			{ text = _filter->links_condition; }
	if (button_type == Enums::ButtonType::BUTTON_CONDITION_MAP_TIER)		{ text = _filter->map_tier_condition; }
	if (button_type == Enums::ButtonType::BUTTON_CONDITION_QUALITY)			{ text = _filter->item_quality_condition; }
	if (button_type == Enums::ButtonType::BUTTON_CONDITION_RARITY)			{ text = _filter->rarity_condition; }
	if (button_type == Enums::ButtonType::BUTTON_CONDITION_SOCKETS)			{ text = _filter->socket_condition; }
	if (button_type == Enums::ButtonType::BUTTON_CONDITION_STACK_SIZE)		{ text = _filter->item_stack_size_condition; }
	if (button_type == Enums::ButtonType::BUTTON_CONDITION_WIDTH)			{ text = _filter->item_width_condition; }

}


