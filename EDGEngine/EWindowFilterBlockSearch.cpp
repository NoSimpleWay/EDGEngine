#include "EWindowFilterBlockSearch.h"

//#include "StaticData.h"

#include "EWindow.h"

#include "Enums.h"
#include "EButtonInputSearchItem.h"
#include "StaticData.h"

//#include "EButtonInputSearchItem.h"


	EWindowFilterBlockSearch::EWindowFilterBlockSearch(int _id, bool _can_be_closed) :EWindow(_id, _can_be_closed)
	{
		EButton* but = new EButtonInputSearchItem(0, -10, 400.0, 30, Enums::ButtonType::BUTTON_SEARCH_INPUT_FOR_FILTER_BLOCK);
		but->master_window = this;
		button_list.push_back (but);
		input_button_link = but;
		but->rama_color->set_alpha(EColorCollection::BLACK, 0.8f);
		//but->button_size_x = 400.0f;

		align_x = Enums::PositionMode::MID;
		align_y = Enums::PositionMode::DOWN;

		window_size_x = 330.0;
		window_size_y = 300.0f;

		is_active = true;

		bg_color->set(0.2f, 0.15f, 0.1f, 0.8f);


	}

	void EWindowFilterBlockSearch::update(float _d)
	{
		window_size_x = EWindow::SCR_WIDTH;
		window_size_y = 40.0f;
	}

	void EWindowFilterBlockSearch::input_event(EButton* _b)
	{
		//StaticData::window_filter_block->is_active = false;
		
		StaticData::window_filter_block->recalculate_filter_block_separator();

		EControl::block_scroll = 0;

		if (_b->text != "")
		{
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

				if
					(
					(fb->base_filter_data_active.at(Enums::BaseDataOrder::DATA_LINKS))
						&&
						(
						(EString::to_lower("6l").find(EString::to_lower(input_button_link->text)) != std::string::npos)
							||
							(EString::to_lower("sixlink").find(EString::to_lower(input_button_link->text)) != std::string::npos)
							||
							(EString::to_lower("6л").find(EString::to_lower(input_button_link->text)) != std::string::npos)
							||
							(EString::to_lower("шестилинк").find(EString::to_lower(input_button_link->text)) != std::string::npos)
							)
						&&
						(
						((fb->links_condition == "=") && (fb->links_count == 6))
							||
							((fb->links_condition == ">") && (fb->links_count < 6))
							||
							((fb->links_condition == ">=") && (fb->links_count <= 6))
							||
							((fb->links_condition == "<") && (fb->links_count > 7))
							||
							((fb->links_condition == "<=") && (fb->links_count >= 6))
							)
						)
				{
					detection = true;
				}

				if
					(
					(
						(fb->base_filter_data_active.at(Enums::BaseDataOrder::DATA_SHAPER_ITEM))
						||
						(fb->base_filter_data_active.at(Enums::BaseDataOrder::DATA_SHAPER_MAP))
						)
						&&
						(
						(EString::to_lower("shaper").find(EString::to_lower(input_button_link->text)) != std::string::npos)
							||
							(EString::to_lower("шейпер").find(EString::to_lower(input_button_link->text)) != std::string::npos)
							||
							(EString::to_lower("создатель").find(EString::to_lower(input_button_link->text)) != std::string::npos)
							)
						)
				{
					detection = true;
				}

				if
					(
					(
						(fb->base_filter_data_active.at(Enums::BaseDataOrder::DATA_ELDER_ITEM))
						||
						(fb->base_filter_data_active.at(Enums::BaseDataOrder::DATA_ELDER_MAP))
						)
						&&
						(
						(EString::to_lower("elder").find(EString::to_lower(input_button_link->text)) != std::string::npos)
							||
							(EString::to_lower("древний").find(EString::to_lower(input_button_link->text)) != std::string::npos)
							)
						)
				{
					detection = true;
				}



				fb->is_deactivated = !detection;

				if (detection)
				{
					fb->hided_by_separator = false;
				}
			}
		}
		else
		{
			for (FilterBlock* fb : StaticData::window_filter_block->filter_block_list)
			{fb->is_deactivated = false;}
		}

		

	}

	void EWindowFilterBlockSearch::draw(Batcher* _batch, float _delta)
	{
		_batch->setcolor_alpha(EColorCollection::BLACK, 0.8f);
		EFont::active_font->set_align_once(Enums::PositionMode::RIGHT);
		EFont::active_font->draw(_batch, cached_text_search, pos_x + (window_size_x - input_button_link->button_size_x) / 2.0f - 10, pos_y + 5.0f);

	}

	void EWindowFilterBlockSearch::update_localisation()
	{
		for (EButton* b : button_list)
		{
			b->update_localisation();
		}

		cached_text_search = EString::localize_it("cached_text_search");

		//input_button_link->update_localisation();
	}





