#include "EButtonExplicit.h"
#include "StaticData.h"

EButtonExplicit::EButtonExplicit(float _x, float _y, float _sx, float _sy, Enums::ButtonType _type) : EButton(_x, _y, _sx, _sy)
{
	button_type = _type;
	have_input_mode = true;

	if (button_type == Enums::ButtonType::BUTTON_EXPLICIT_FILTER_BLOCK_LIST)
	{
		bg_color->set(0.4f, 0.5f, 1.0f, 0.8f);
	}

	if (button_type == Enums::ButtonType::BUTTON_CLASS_FILTER_BLOCK_LIST)
	{
		bg_color->set(0.4f, 1.0f, 0.5f, 0.8f);
	}

	if (button_type == Enums::ButtonType::BUTTON_PROPHECY_FILTER_BLOCK_LIST)
	{
		have_input_mode = false;

		bg_color->set(1.0f, 0.4f, 0.5f, 0.5f);
	}



	master_position = Enums::PositionMaster::FILTER_BLOCK;

	position_mode_y = Enums::PositionMode::UP;


	can_be_removed = true;
	dynamic_input_width = true;


}

void EButtonExplicit::click_event()
{
	if (button_type == Enums::ButtonType::BUTTON_EXPLICIT_FILTER_BLOCK_LIST)
	{
		if (is_plus)
		{
			EButtonExplicit* explicit_button = new EButtonExplicit(0, 0, 100, 20, Enums::ButtonType::BUTTON_EXPLICIT_FILTER_BLOCK_LIST);
			explicit_button->text = "=click me=";
			explicit_button->master_block = master_block;
			explicit_button->master_window = StaticData::window_filter_block;
			explicit_button->button_size_x = EFont::get_width(EFont::font_arial, "=click me=") + 5.0f;
			master_block->explicit_list.at(data_id)->button_list.push_back(explicit_button);

			master_block->button_list.push_back(explicit_button);
		}
	}

	if (button_type == Enums::ButtonType::BUTTON_CLASS_FILTER_BLOCK_LIST)
	{
		if (is_plus)
		{
			EButtonExplicit* explicit_button = new EButtonExplicit(0, 0, 100, 20, Enums::ButtonType::BUTTON_CLASS_FILTER_BLOCK_LIST);
			explicit_button->text = "=click me=";
			explicit_button->have_input_mode = false;
			explicit_button->master_block = master_block;
			explicit_button->master_window = StaticData::window_filter_block;
			explicit_button->button_size_x = EFont::get_width(EFont::font_arial, "=click me=") + 5.0f;
			master_block->base_class_list.push_back(explicit_button);

			master_block->button_list.push_back(explicit_button);

			StaticData::window_find_item->is_active = true;
			StaticData::window_find_item->window_searchs_mode = Enums::WindowSearchMode::BASE_CLASS_SEARCH_LIST;

			StaticData::window_find_item->target_button = explicit_button;
			StaticData::window_find_item->button_event(this);
		}
	}

	if (button_type == Enums::ButtonType::BUTTON_PROPHECY_FILTER_BLOCK_LIST)
	{
		StaticData::window_find_item->is_active = true;
		StaticData::window_find_item->window_searchs_mode = Enums::WindowSearchMode::PROPHECY_SEARCH_LIST;

		StaticData::window_find_item->target_button = this;
		StaticData::window_find_item->button_event(this);

		if (is_plus)
		{
			EButtonExplicit* prophecy_button = new EButtonExplicit(0, 0, 100, 20, Enums::ButtonType::BUTTON_PROPHECY_FILTER_BLOCK_LIST);
			prophecy_button->text = ">click me<";
			prophecy_button->have_input_mode = false;
			prophecy_button->master_block = master_block;
			prophecy_button->master_window = StaticData::window_filter_block;
			prophecy_button->button_size_x = EFont::get_width(EFont::font_arial, ">click me<") + 5.0f;
			master_block->prophecy_list.push_back(prophecy_button);

			master_block->button_list.push_back(prophecy_button);

			StaticData::window_find_item->target_button = prophecy_button;
		}



	}
}
