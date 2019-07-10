#include "EButtonInputBaseData.h"

EButtonInputBaseData::EButtonInputBaseData(float _x, float _y, float _sx, float _sy, Enums::ButtonType _type) : EButton(_x, _y, _sx, _sy)
{
	master_position = Enums::PositionMaster::FILTER_BLOCK;
	text_align_x = Enums::PositionMode::LEFT;

	button_x = _x;
	button_y = _y;

	button_size_x = _sx;
	button_size_y = _sy;

	type = _type;

	have_icon = false;
	have_text = true;
	have_description = true;
	have_input_mode = true;
	have_rama = true;
	input_only_numbers = true;

	input_hint = "";

	rama_color->set(0.6f,0.8f,1.0f,0.55f);
}

void EButtonInputBaseData::click_event()
{
}
