#pragma once
#include "EButtonItemSearch.h"
#include "StaticData.h"


EButtonItemSearch::EButtonItemSearch(float _x, float _y, float _sx, float _sy) : EButton(_x, _y, _sx, _sy)
{
	is_active = false;
	have_icon = true;
	have_text = false;
	have_description = true;

	position_mode_x = Enums::PositionMode::LEFT;
	position_mode_y = Enums::PositionMode::UP;

	master_position = Enums::PositionMaster::WINDOW;

	description_text = "none";

	have_rama = true;
}

void EButtonItemSearch::click_event()
{
	StaticData::window_find_item->is_active = false;
	StaticData::window_find_item->target_button->description_text = description_text;
	StaticData::window_find_item->target_button->gabarite = gabarite;

	StaticData::window_find_item->input_button->text = "";
	//StaticData::window_find_item->fill_search_array();

}

	/*void EButton::click_event()
	{
		std::cout << "STANDART click event" << std::endl;
	}
	*/
	/*void EButton::click_event()
	{
		//std::cout << " ### pressed ### " << std::endl;

//		StaticData::window_find_item->is_active=false;
	}*/



