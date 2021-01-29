#include "EButtonDropCondition.h"
#include "StaticData.h"





EButtonDropCondition::EButtonDropCondition(float _x, float _y, float _sx, float _sy, Enums::ButtonType _type) : EButton(_x, _y, _sx, _sy)   // конструктор класса SecondClass вызывает конструктор класса FirstClass
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

	drop_text_base.push_back("<=");
	drop_text_base.push_back("<");
	drop_text_base.push_back("=");
	drop_text_base.push_back(">");
	drop_text_base.push_back(">=");


}

void EButtonDropCondition::click_event()
{
}

void EButtonDropCondition::incoming_data(FilterBlock* _filter)
{
	if (button_type == Enums::ButtonType::BUTTON_CONDITION_DROP_LEVEL)			{ text = _filter->required_level_condition; }
	if (button_type == Enums::ButtonType::BUTTON_CONDITION_GEM_LEVEL)			{ text = _filter->gem_level_condition; }
	if (button_type == Enums::ButtonType::BUTTON_CONDITION_HEIGHT)				{ text = _filter->item_height_condition; }
	if (button_type == Enums::ButtonType::BUTTON_CONDITION_ITEM_LEVEL)			{ text = _filter->item_level_condition; }
	if (button_type == Enums::ButtonType::BUTTON_CONDITION_LINKS)				{ text = _filter->links_condition; }
	if (button_type == Enums::ButtonType::BUTTON_CONDITION_MAP_TIER)			{ text = _filter->map_tier_condition; }
	if (button_type == Enums::ButtonType::BUTTON_CONDITION_QUALITY)				{ text = _filter->item_quality_condition; }
	if (button_type == Enums::ButtonType::BUTTON_CONDITION_RARITY)				{ text = _filter->rarity_condition; }
	if (button_type == Enums::ButtonType::BUTTON_CONDITION_SOCKETS)				{ text = _filter->socket_condition; }
	if (button_type == Enums::ButtonType::BUTTON_CONDITION_STACK_SIZE)			{ text = _filter->item_stack_size_condition; }
	if (button_type == Enums::ButtonType::BUTTON_CONDITION_SOCKET_GROUP)		{ text = _filter->socket_group_condition; }
	if (button_type == Enums::ButtonType::BUTTON_CONDITION_AREA_LEVEL)			{ text = _filter->area_level_condition; }


	//if (button_type == Enums::ButtonType::BUTTON_BASE_DATA_CONDITION_REGULAR)	{ text = _filter->base_data_button_collection_list.at(data_id); }
}

void EButtonDropCondition::drop_list_select_event()
{
	if (button_type == Enums::ButtonType::BUTTON_CONDITION_DROP_LEVEL)		{ master_block->required_level_condition=text; }
	if (button_type == Enums::ButtonType::BUTTON_CONDITION_GEM_LEVEL)		{ master_block->gem_level_condition=text; }
	if (button_type == Enums::ButtonType::BUTTON_CONDITION_HEIGHT)			{ master_block->item_height_condition=text; }
	if (button_type == Enums::ButtonType::BUTTON_CONDITION_ITEM_LEVEL)		{ master_block->item_level_condition=text; }
	if (button_type == Enums::ButtonType::BUTTON_CONDITION_LINKS)			{ master_block->links_condition=text; }
	if (button_type == Enums::ButtonType::BUTTON_CONDITION_MAP_TIER)		{ master_block->map_tier_condition=text; }
	if (button_type == Enums::ButtonType::BUTTON_CONDITION_QUALITY)			{ master_block->item_quality_condition=text; }
	if (button_type == Enums::ButtonType::BUTTON_CONDITION_RARITY)			{ master_block->rarity_condition=text; }
	if (button_type == Enums::ButtonType::BUTTON_CONDITION_SOCKETS)			{ master_block->socket_condition=text; }
	if (button_type == Enums::ButtonType::BUTTON_CONDITION_STACK_SIZE)		{ master_block->item_stack_size_condition=text; }
	if (button_type == Enums::ButtonType::BUTTON_CONDITION_WIDTH)			{ master_block->item_width_condition=text; }
	if (button_type == Enums::ButtonType::BUTTON_CONDITION_SOCKET_GROUP)	{ master_block->socket_group_condition =text; }
	if (button_type == Enums::ButtonType::BUTTON_CONDITION_AREA_LEVEL)		{ master_block->area_level_condition =text; }

}

void EButtonDropCondition::update_localisation()
{

}




