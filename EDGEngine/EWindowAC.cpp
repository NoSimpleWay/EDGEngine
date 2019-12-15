#include "EWindowAC.h"
#include "EButtonText.h"
#include "EUtils.h"
#include "StaticData.h"


EWindowAC::EWindowAC(int _id, bool _can_be_closed):EWindow (_id, _can_be_closed)
{
	EButton* but = new EButtonText(-55.0f, 5.0f, 100.0f, 20.0f, Enums::ButtonType::BUTTON_ACCEPT);
	but->master_window = this;
	button_list.push_back(but);

	but = new EButtonText(55.0f, 5.0f, 100.0f, 20.0f, Enums::ButtonType::BUTTON_CANCEL);
	but->master_window = this;
	button_list.push_back(but);

	window_size_x = 700.0f;
	window_size_y = 150.0f;

	bg_color->set_alpha(EColorCollection::BLACK, 0.9f);
}

void EWindowAC::button_event(EButton* _b)
{
	if (window_mode == Enums::WindowAcceptCancelMode::AC_unsave_open)
	{
		if (_b->button_type == Enums::ButtonType::BUTTON_ACCEPT)
		{
			EString::load_loot_filter_list();
			StaticData::window_find_item->is_active = true;
			StaticData::window_find_item->window_searchs_mode = Enums::WindowSearchMode::OPEN_LOOT_FILTER_SEARCH_LIST;
			StaticData::window_find_item->manual_event();
		}

		is_active = false;
	}

	if (window_mode == Enums::WindowAcceptCancelMode::AC_exit_program)
	{	
		if (_b->button_type == Enums::ButtonType::BUTTON_ACCEPT)
		{
			StaticData::need_exit = true;
		}
		else
		{
			StaticData::need_exit = false;
		}

		is_active = false;
	}

	if (window_mode == Enums::WindowAcceptCancelMode::AC_new_loot_filter)
	{
		if (_b->button_type == Enums::ButtonType::BUTTON_ACCEPT)
		{
			StaticData::window_new_loot_filter->is_active = true;
			StaticData::window_new_loot_filter->link_to_input_button->is_input_mode_active = true;
		}

		is_active = false;
	}

	if (window_mode == Enums::WindowAcceptCancelMode::AC_remove_separator)
	{
		if (_b->button_type == Enums::ButtonType::BUTTON_ACCEPT)
		{
			int sep_id = -1;
			for (int i=0; i < StaticData::window_filter_block->separator_list.size(); i++)
			{
				if (StaticData::window_filter_block->separator_list.at(i) == master_separator) { sep_id = i;}
			}

			if (sep_id >= 0)
			{
				StaticData::window_filter_block->separator_list.at(sep_id)->is_collapsed = false;

				StaticData::window_filter_block->recalculate_filter_block_separator();

				StaticData::window_filter_block->separator_list.erase(StaticData::window_filter_block->separator_list.begin() + sep_id);
			}

			master_separator->link_to_collapse->need_remove = true;
			master_separator->link_to_remove->need_remove = true;
			master_separator->link_to_caption_text->need_remove = true;

			StaticData::window_filter_block->recalculate_filter_block_separator();
		}

		is_active = false;
	}
	
}

void EWindowAC::update_localisation()
{
	for (EButton* b : button_list) {b->update_localisation();}

	if 
	(
		(window_mode == Enums::WindowAcceptCancelMode::AC_unsave_open)
		||
		(window_mode == Enums::WindowAcceptCancelMode::AC_exit_program)
		||
		(window_mode == Enums::WindowAcceptCancelMode::AC_new_loot_filter)
	)
	{window_text = EString::localize_it("window_text_unsaved_changes"); }

	if
	(
		(window_mode == Enums::WindowAcceptCancelMode::AC_remove_separator)
	)
	{
		window_text = EString::localize_it("window_text_remove_separator");
	}
}

void EWindowAC::text_pass(Batcher* _batch)
{
	_batch->setcolor(EColorCollection::RED);



	EFont::active_font->draw(_batch, window_text, round(pos_x + window_size_x / 2.0f), round(pos_y + window_size_y) - 20.0f);
	
}

void EWindowAC::manual_event()
{
}

