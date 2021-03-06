#include "EButtonExplicit.h"
#include "StaticData.h"

std::string cached_text_press_me;

EButtonExplicit::EButtonExplicit(float _x, float _y, float _sx, float _sy, Enums::ButtonType _type) : EButton(_x, _y, _sx, _sy)
{
	button_type = _type;
	
	can_receive_paste = true;

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

	if (button_type == Enums::ButtonType::BUTTON_ENCHANTMENT_FILTER_BLOCK_LIST)
	{
		have_input_mode = false;

		bg_color->set(0.0f, 0.0f, 0.0f, 0.85f);
		text_color->set(0.75f, 0.75f, 0.75f, 1.0f);
		
	}

	if (button_type == Enums::ButtonType::BUTTON_CLUSTER_ENCHANTMENT_FILTER_BLOCK_LIST)
	{
		have_input_mode = false;

		bg_color->set(0.05f, 0.05f, 0.05f, 1.0f);
		text_color->set(1.0f, 1.0f, 1.0f, 1.0f);
		
	}
	input_auto_clear_text = true;

	master_position = Enums::PositionMaster::FILTER_BLOCK;

	position_mode_x = Enums::PositionMode::LEFT;
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
			explicit_button->button_size_x = EFont::get_width(EFont::active_font, explicit_button->text) + 5.0f;
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
			class_button->button_size_x = EFont::get_width(EFont::active_font, class_button->text) + 5.0f;
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
			prophecy_button->button_size_x = EFont::get_width(EFont::active_font, prophecy_button->text) + 5.0f;
			master_block->prophecy_list.push_back(prophecy_button);

			master_block->button_list.push_back(prophecy_button);

			StaticData::window_find_item->target_button = prophecy_button;
		}



	}

	
	if (button_type == Enums::ButtonType::BUTTON_ENCHANTMENT_FILTER_BLOCK_LIST)
	{
		StaticData::window_find_item->is_active = true;
		StaticData::window_find_item->window_searchs_mode = Enums::WindowSearchMode::ENCHANTMENT_SEARCH_LIST;

		StaticData::window_find_item->target_button = this;
		StaticData::window_find_item->button_event(this);

		if (is_plus)
		{
			EButtonExplicit* enchantment_button = new EButtonExplicit(0, 0, 100, 20, Enums::ButtonType::BUTTON_ENCHANTMENT_FILTER_BLOCK_LIST);
			enchantment_button->text = cached_text_press_me;
			enchantment_button->have_input_mode = false;
			enchantment_button->master_block = master_block;
			enchantment_button->master_window = StaticData::window_filter_block;
			enchantment_button->button_size_x = EFont::get_width(EFont::active_font, enchantment_button->text) + 5.0f;
			master_block->enchantment_list.push_back(enchantment_button);

			master_block->button_list.push_back(enchantment_button);

			StaticData::window_find_item->target_button = enchantment_button;
		}
		



	}
	
	if (button_type == Enums::ButtonType::BUTTON_CLUSTER_ENCHANTMENT_FILTER_BLOCK_LIST)
	{
		StaticData::window_find_item->is_active = true;
		StaticData::window_find_item->window_searchs_mode = Enums::WindowSearchMode::CLUSTER_ENCHANTMENT_SEARCH_LIST;

		StaticData::window_find_item->target_button = this;
		StaticData::window_find_item->button_event(this);

		if (is_plus)
		{
			EButtonExplicit* enchantment_button = new EButtonExplicit(0, 0, 100, 20, Enums::ButtonType::BUTTON_CLUSTER_ENCHANTMENT_FILTER_BLOCK_LIST);
			enchantment_button->text = cached_text_press_me;
			enchantment_button->have_input_mode = false;
			enchantment_button->master_block = master_block;
			enchantment_button->master_window = StaticData::window_filter_block;
			enchantment_button->button_size_x = EFont::get_width(EFont::active_font, enchantment_button->text) + 5.0f;
			master_block->cluster_enchantment_list.push_back(enchantment_button);

			master_block->button_list.push_back(enchantment_button);

			StaticData::window_find_item->target_button = enchantment_button;
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
	{
		if (is_plus)
		{
			description_text = EString::localize_it("description_add_new_explicit_group_list");
		}
		else
		{
			description_text = EString::localize_it("description_click_to_edit");
		}
	}

	if (button_type == Enums::ButtonType::BUTTON_CLASS_FILTER_BLOCK_LIST)
	{
		
			if (is_plus)
			{
				description_text = EString::localize_it("description_add_new_class");
			}
			else
			{
				description_text = EString::localize_it("description_click_to_edit");
			}
	}

	if (button_type == Enums::ButtonType::BUTTON_PROPHECY_FILTER_BLOCK_LIST)
	{
			if (is_plus)
			{
				description_text = EString::localize_it("description_add_new_prophecy");
			}
			else
			{
				description_text = EString::localize_it("description_click_to_edit");
			}
	}

	cached_text_press_me = EString::localize_it("press_me");
}
