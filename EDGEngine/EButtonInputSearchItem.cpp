#pragma once
#include "EButtonInputSearchItem.h"
#include "StaticData.h"


EButtonInputSearchItem::EButtonInputSearchItem(float _x, float _y, float _sx, float _sy, Enums::ButtonType _type) : EButton(_x, _y, _sx, _sy)
{
	button_type = _type;
	is_active = true;
	have_icon = false;
	have_text = true;
	have_description = true;
	have_input_mode = true;
	//is_input_mode_active = true;

	master_position = Enums::PositionMaster::WINDOW;

	position_mode_x = Enums::PositionMode::MID;
	position_mode_y = Enums::PositionMode::UP;

	button_size_x = 300;
	button_size_y = 25;


	text = "";
	

	have_rama = true;



}

void EButtonInputSearchItem::input_event()
{
	if (button_type == Enums::ButtonType::BUTTON_SEARCH_INPUT_FOR_ITEM)
	{
		StaticData::window_find_item->input_event(this);
	}

	if (button_type == Enums::ButtonType::BUTTON_SEARCH_INPUT_FOR_FILTER_BLOCK)
	{
		StaticData::window_filter_block_search->input_event(this);
	}


}

	void EButtonInputSearchItem::update_localisation()
	{
		if (Enums::ButtonType::BUTTON_SEARCH_ITEM)
		{input_hint = EString::localize_it("hint_input_search_item");}

		if (Enums::ButtonType::BUTTON_SEARCH_DEFAULT_SOUND)
		{input_hint = EString::localize_it("hint_default_sound");}

		if (Enums::ButtonType::BUTTON_SEARCH_CUSTOM_SOUND)
		{input_hint = EString::localize_it("hint_custom_sound");}

		if (Enums::ButtonType::BUTTON_SEARCH_BASE_CLASS)
		{input_hint = EString::localize_it("hint_input_base_class_name");}

		if (Enums::ButtonType::BUTTON_SEARCH_PROPHECY)
		{input_hint = EString::localize_it("hint_input_prophecy_name");}
	}


