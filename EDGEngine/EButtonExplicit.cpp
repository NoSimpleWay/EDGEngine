#include "EButtonExplicit.h"
#include "StaticData.h"

std::string cached_text_press_me;

EButtonExplicit::EButtonExplicit(float _x, float _y, float _sx, float _sy, Enums::ButtonType _type) : EButton(_x, _y, _sx, _sy)
{
	button_type = _type;
	

	if (button_type == Enums::ButtonType::BUTTON_EXPLICIT_FILTER_BLOCK_LIST)
	{
		have_input_mode = true;

		bg_color->set(0.4f, 0.5f, 1.0f, 0.8f);
	}

	if (button_type == Enums::ButtonType::BUTTON_CLASS_FILTER_BLOCK_LIST)
	{
		have_input_mode = false;

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
			explicit_button->text = cached_text_press_me;
			explicit_button->master_block = master_block;
			explicit_button->master_window = StaticData::window_filter_block;
			explicit_button->button_size_x = EFont::get_width(EFont::font_arial, explicit_button->text) + 5.0f;
			master_block->explicit_list.at(data_id)->button_list.push_back(explicit_button);

			master_block->button_list.push_back(explicit_button);
		}
	}

	if (button_type == Enums::ButtonType::BUTTON_CLASS_FILTER_BLOCK_LIST)
	{
		StaticData::window_find_item->is_active = true;
		StaticData::window_find_item->window_searchs_mode = Enums::WindowSearchMode::BASE_CLASS_SEARCH_LIST;

		StaticData::window_find_item->target_button = this;
		StaticData::window_find_item->button_event(this);

		if (is_plus)
		{
			EButtonExplicit* class_button = new EButtonExplicit(0, 0, 100, 20, Enums::ButtonType::BUTTON_CLASS_FILTER_BLOCK_LIST);
			class_button->text = cached_text_press_me;
			class_button->have_input_mode = false;
			class_button->master_block = master_block;
			class_button->master_window = StaticData::window_filter_block;
			class_button->button_size_x = EFont::get_width(EFont::font_arial, class_button->text) + 5.0f;
			master_block->base_class_list.push_back(class_button);

			master_block->button_list.push_back(class_button);

			StaticData::window_find_item->target_button = class_button;
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
			prophecy_button->text = cached_text_press_me;
			prophecy_button->have_input_mode = false;
			prophecy_button->master_block = master_block;
			prophecy_button->master_window = StaticData::window_filter_block;
			prophecy_button->button_size_x = EFont::get_width(EFont::font_arial, prophecy_button->text) + 5.0f;
			master_block->prophecy_list.push_back(prophecy_button);

			master_block->button_list.push_back(prophecy_button);

			StaticData::window_find_item->target_button = prophecy_button;
		}



	}
}

void EButtonExplicit::update_localisation()
{
	if (button_type == Enums::ButtonType::BUTTON_EXPLICIT_FILTER_BLOCK_LIST)
	{description_text = EString::localize_it("name_of_suffix/prefix");}

	if (button_type == Enums::ButtonType::BUTTON_CLASS_FILTER_BLOCK_LIST)
	{description_text = EString::localize_it("name_of_class");}

	if (button_type == Enums::ButtonType::BUTTON_PROPHECY_FILTER_BLOCK_LIST)
	{description_text = EString::localize_it("name_of_prophecy");}

	if (button_type == Enums::ButtonType::BUTTON_EXPLICIT_FILTER_BLOCK_LIST)
	{description_text = EString::localize_it("description_add_new_explicit_group_list");}

	if (button_type == Enums::ButtonType::BUTTON_CLASS_FILTER_BLOCK_LIST)
	{description_text = EString::localize_it("description_add_new_class");}

	if (button_type == Enums::ButtonType::BUTTON_PROPHECY_FILTER_BLOCK_LIST)
	{description_text = EString::localize_it("description_add_new_prophecy");}

	cached_text_press_me = EString::localize_it("press_me");
}
