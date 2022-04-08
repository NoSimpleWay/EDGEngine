#include "EButtonPlusWide.h"

EButtonPlusWide::EButtonPlusWide(float _x, float _y, float _sx, float _sy, Enums::ButtonType _type):EButton(_x,_y,_sx,_sy)
{
	master_position = Enums::PositionMaster::FILTER_BLOCK;

	position_mode_x = Enums::PositionMode::LEFT;
	position_mode_y = Enums::PositionMode::DOWN;

	text_align_x = Enums::PositionMode::MID;

	
	have_bg = false;
	have_text = false;
	have_icon = true;
	have_rama = false;
	is_drop_list = false;
	can_be_removed = false;

	gabarite = DefaultGabarite::gabarite_plus_circle;

	rama_thikness = 1;


	rama_color->set(0.05f, 0.15f, 0.25f, 0.6f);


	button_type = _type;

	if (button_type==Enums::ButtonType::BUTTON_OPEN_EXPLICIT_ARCHNEMESIS_CLASS_WINDOW)
	{
		position_mode_y = Enums::PositionMode::UP;
	}

	if (button_type == Enums::ButtonType::BUTTON_OPEN_BASE_CLASS_WINDOW)
	{
		position_mode_y = Enums::PositionMode::UP;
	}
}

void EButtonPlusWide::click_event()
{
	if (button_type==Enums::ButtonType::BUTTON_OPEN_BASE_DATA_WINDOW)
	{
		StaticData::window_add_new_base_data->window_searchs_mode = Enums::WindowSearchMode::BASE_DATA_VERTICAL_LIST;
		StaticData::window_add_new_base_data->button_event(this);
	}

	if (button_type==Enums::ButtonType::BUTTON_OPEN_EXPLICIT_ARCHNEMESIS_CLASS_WINDOW)
	{
		StaticData::window_add_new_base_data->window_searchs_mode = Enums::WindowSearchMode::EXPLICIT_ARCHNEMESIS_CLASS_VERTICAL_LIST;
		StaticData::window_add_new_base_data->button_event(this);
	}

	if (button_type == Enums::ButtonType::BUTTON_OPEN_BASE_CLASS_WINDOW)
	{
		StaticData::window_find_item->is_active = true;
		StaticData::window_find_item->window_searchs_mode = Enums::WindowSearchMode::BASE_CLASS_SEARCH_LIST;

		StaticData::window_find_item->button_event(this);
	}
}

void EButtonPlusWide::update_localisation()
{
	if (button_type == Enums::ButtonType::BUTTON_OPEN_EXPLICIT_ARCHNEMESIS_CLASS_WINDOW)
	{description_text = EString::localize_it("description_new_EPC");}

	if (button_type == Enums::ButtonType::BUTTON_OPEN_BASE_DATA_WINDOW)
	{description_text = EString::localize_it("description_new_base_data");}
}
