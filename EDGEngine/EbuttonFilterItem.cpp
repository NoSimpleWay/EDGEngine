#include "EButtonFilterItem.h"
#include "StaticData.h"


	

	EButtonFilterItem::EButtonFilterItem(float _x, float _y, float _sx, float _sy) : EButton(_x, _y, _sx, _sy)   // конструктор класса SecondClass вызывает конструктор класса FirstClass
	{
		master_position = Enums::PositionMaster::FILTER_BLOCK;
		have_text = false;
		have_icon = true;

		can_be_removed = true;

		have_rama = true;


		
			rama_color->set(0.4f, 0.3f, 0.1f, 0.6f);
			bg_color->set(0.1f, 0.08f, 0.06f, 0.75f);
			rama_thikness = 2;
		
	}

	void EButtonFilterItem::change_color_cheme()
	{
		rama_color->set(1.0f, 0.3f, 1.0f, 0.6f);
		bg_color->set(0.1f, 0.08f, 0.1f, 0.75f);
		rama_thikness = 5;

		update_localisation();
	};

	void EButtonFilterItem::click_event()
	{
		std::cout << " ### pressed ### " << std::endl;

		StaticData::window_find_item->window_searchs_mode = Enums::ITEM;

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
			but->description_text = "?";
			master_block->filter_block_items_button_list.push_back(but);

			but->master_block = master_block;
			but->master_window = master_window;


			StaticData::window_find_item->button_event(but);

			StaticData::window_find_item->is_active = true;
			StaticData::window_find_item->target_button = but;

			but->is_full_equal_mode = is_full_equal_mode;

			if (is_full_equal_mode)
			{
				but->change_color_cheme();
			}
		}
	}

	void EButtonFilterItem::update_localisation()
	{
		description_text = EString::localize_it("button_new_filter_item");

		if (is_full_equal_mode)
		{
			description_text = EString::localize_it("button_new_filter_item_equal");
		}
	}


