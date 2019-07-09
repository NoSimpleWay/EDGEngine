#include "EButtonFilterItem.h"
#include "StaticData.h"




	EButtonFilterItem::EButtonFilterItem(float _x, float _y, float _sx, float _sy) : EButton(_x, _y, _sx, _sy)   // конструктор класса SecondClass вызывает конструктор класса FirstClass
	{
		master_position = Enums::ButtonPositionMaster::FILTER_BLOCK;
		have_text = false;
	}

	void EButtonFilterItem::click_event()
	{
		std::cout << " ### pressed ### " << std::endl;

		StaticData::window_find_item->is_active = true;
		StaticData::window_find_item->button_event(this);
	}


