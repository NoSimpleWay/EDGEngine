#include "EButtonExplicit.h"

EButtonExplicit::EButtonExplicit(float _x, float _y, float _sx, float _sy) : EButton(_x, _y, _sx, _sy)
{
	bg_color->set(0.8f, 0.9f, 1.0f, 0.9f);

	master_position = Enums::PositionMaster::FILTER_BLOCK;

	position_mode_y = Enums::PositionMode::UP;

	have_input_mode = true;
	can_be_removed = true;
}

void EButtonExplicit::click_event()
{
}
