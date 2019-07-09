#pragma once
#include "EButtonInputSearchItem.h"
#include "StaticData.h"


EButtonInputSearchItem::EButtonInputSearchItem(float _x, float _y, float _sx, float _sy) : EButton(_x, _y, _sx, _sy)
{
	is_active = true;
	have_icon = false;
	have_text = true;
	have_description = true;
	have_input_mode = true;

	master_position = Enums::ButtonPositionMaster::WINDOW;

	position_mode_x = Enums::ButtonPositionMode::MID;
	position_mode_y = Enums::ButtonPositionMode::MID;

	button_size_x = 300;
	button_size_y = 25;


	text = "";

	description_text = "none";
}

void EButtonInputSearchItem::input_event()
{
	StaticData::window_find_item->input_event(this);
}


