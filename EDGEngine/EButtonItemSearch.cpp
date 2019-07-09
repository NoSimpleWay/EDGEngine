#pragma once
#include "EButtonItemSearch.h"


EButtonItemSearch::EButtonItemSearch(float _x, float _y, float _sx, float _sy) : EButton(_x, _y, _sx, _sy)
{
	is_active = false;
	have_icon = true;
	have_text = false;
	have_description = true;

	description_text = "none";
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



