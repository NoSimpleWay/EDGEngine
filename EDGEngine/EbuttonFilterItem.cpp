#include "EButtonFilterItem.h"
#include "StaticData.h"


	

	EButtonFilterItem::EButtonFilterItem(float _x, float _y, float _sx, float _sy) : EButton(_x, _y, _sx, _sy)   // конструктор класса SecondClass вызывает конструктор класса FirstClass
	{
		master_position = Enums::PositionMaster::FILTER_BLOCK;
		have_text = false;
		have_icon = true;

		can_be_removed = true;

		have_rama = true;
		rama_color->set(0.2f, 0.15f, 0.05f, 0.6f);
	}

	void EButtonFilterItem::click_event()
	{
		std::cout << " ### pressed ### " << std::endl;

		if (!is_plus)
		{
			StaticData::window_find_item->is_active = true;
			StaticData::window_find_item->button_event(this);
			StaticData::window_find_item->target_button = this;
		}
		else
		{
			EButtonFilterItem* but = new EButtonFilterItem(0, 0, 45, 45);

			but->gabarite = DefaultGabarite::gabarite_undefined;
			but->description_text = "LOL";
			master_block->filter_block_items_button_list.push_back(but);

			but->master_block	= master_block;
			but->master_window	= master_window;


			StaticData::window_find_item->button_event(but);

			StaticData::window_find_item->is_active = true;
			StaticData::window_find_item->target_button = but;
		}
	}


