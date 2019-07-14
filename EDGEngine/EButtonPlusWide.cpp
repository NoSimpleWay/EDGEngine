#include "EButtonPlusWide.h"

EButtonPlusWide::EButtonPlusWide(float _x, float _y, float _sx, float _sy, Enums::ButtonType _type):EButton(_x,_y,_sx,_sy)
{
	master_position = Enums::PositionMaster::FILTER_BLOCK;

	position_mode_x = Enums::PositionMode::LEFT;
	position_mode_y = Enums::PositionMode::DOWN;

	text_align_x = Enums::PositionMode::MID;

	have_text = false;
	have_icon = true;
	have_rama = true;
	is_drop_list = false;
	can_be_removed = false;

	gabarite = DefaultGabarite::gabarite_plus;

	rama_thikness = 1;


	rama_color->set(0.05f, 0.15f, 0.25f, 0.6f);


	button_type = _type;
}

void EButtonPlusWide::click_event()
{
	StaticData::window_add_new_base_data->button_event(this);
}
