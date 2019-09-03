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

	window_size_x = 600.0f;
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
}

void EWindowAC::update_localisation()
{
	for (EButton* b : button_list) {b->update_localisation();}

	if ((window_mode == Enums::WindowAcceptCancelMode::AC_unsave_open)||(window_mode == Enums::WindowAcceptCancelMode::AC_exit_program))
	{window_text = EString::localize_it("window_text_unsaved_changes"); }
}

void EWindowAC::text_pass(Batcher* _batch)
{
	if (window_mode == Enums::WindowAcceptCancelMode::AC_unsave_open)
	{_batch->setcolor(EColorCollection::RED);}

	if (window_mode == Enums::WindowAcceptCancelMode::AC_exit_program)
	{_batch->setcolor(EColorCollection::RED);}

	EFont::active_font->draw(_batch, window_text, pos_x + window_size_x / 2.0f, pos_y + window_size_y - 20.0f);
	
}

void EWindowAC::manual_event()
{
}

