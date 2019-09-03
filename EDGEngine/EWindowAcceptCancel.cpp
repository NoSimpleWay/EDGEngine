#include "EWindowAcceptCancel.h"
#include "EWindow.h"
#include "EUtils.cpp"




EWindowAcceptCancel::EWindowAcceptCancel(int _id, bool _can_be_closed):EWindow(_id, _can_be_closed)
{
	window_size_x = 700.0f;

	window_size_y = 300.0f;

	EButton* but = new EButtonText(-110.0f, 5.0f, 100.0f, 20.0f, Enums::ButtonType::BUTTON_ACCEPT);
	but->master_window = this;
	button_list.push_back(but);

	but = new EButtonText(-110.0f, 5.0f, 100.0f, 20.0f, Enums::ButtonType::BUTTON_CANCEL);
	but->master_window = this;
	button_list.push_back(but);
}

void EWindowAcceptCancel::create_font_button(std::string _s, EFont* _f, int _id)
{
}

void EWindowAcceptCancel::update_localisation()
{
}

void EWindowAcceptCancel::button_event(EButton* _b)
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
}
