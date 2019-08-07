#include "EWindowFilterBlockSearch.h"

//#include "StaticData.h"

#include "EWindow.h"

#include "Enums.h"
#include "EButtonInputSearchItem.h"
#include "StaticData.h"

//#include "EButtonInputSearchItem.h"

	EWindowFilterBlockSearch::EWindowFilterBlockSearch(int _id, bool _can_be_closed) :EWindow(_id, _can_be_closed)
	{
		EButton* but = new EButtonInputSearchItem(0, -10, 30, 30, Enums::ButtonType::BUTTON_SEARCH_INPUT_FOR_FILTER_BLOCK);
		but->master_window = this;
		button_list.push_back (but);
		input_button_link = but;

		align_x = Enums::PositionMode::MID;
		align_y = Enums::PositionMode::DOWN;

		window_size_x = 330.0;
		window_size_y = 300.0f;

		is_active = true;

		bg_color->set(0.8f, 0.9f, 1.0f, 0.8f);
	}

	void EWindowFilterBlockSearch::update(float _d)
	{
		window_size_x = EWindow::SCR_WIDTH;
		window_size_y = 40.0f;
	}

	void EWindowFilterBlockSearch::input_event(EButton* _b)
	{
		//StaticData::window_filter_block->is_active = false;
		
		EControl::block_scroll = 0;

		for (FilterBlock* fb : StaticData::window_filter_block->filter_block_list)
		{
			fb->is_deactivated = true;

			bool detection = false;

			for (EButton* b : fb->filter_block_items_button_list)
			{
				if
				(
					(b->data_id >= 0)
					&&
					(
						(EString::to_lower(ItemList::item_list.at(b->data_id)->item_name, false).find(EString::to_lower(input_button_link->text, false)) != std::string::npos)
						||
						(EString::to_lower(ItemList::item_list.at(b->data_id)->item_name_ru, false).find(EString::to_lower(input_button_link->text, false)) != std::string::npos)
					)
				)
				{
					detection = true;
				}

				if
				(
					(b->data_id < 0)
					&&
					(EString::to_lower(b->data_string, false).find(EString::to_lower(input_button_link->text, false)) != std::string::npos)
				)
				{
					detection = true;
				}
			}



			for (EButton* b : fb->base_class_list)
			{
				if
				(
					(b->data_id >= 0)
					&&
					(
					(EString::to_lower(EString::base_class_list.at(b->data_id)->base_name, false).find(EString::to_lower(input_button_link->text, false)) != std::string::npos)
					||
					(EString::to_lower(EString::base_class_list.at(b->data_id)->ru_name, false).find(EString::to_lower(input_button_link->text, false)) != std::string::npos)
					)
				)
				{
					detection = true;
				}

				if
				(
					(b->data_id < 0)
					&&
					(
						(EString::to_lower(b->data_string, false).find(EString::to_lower(input_button_link->text, false)) != std::string::npos)
					)
				)
				{
					detection = true;
				}
			}

			fb->is_deactivated = !detection;
		}
	}



