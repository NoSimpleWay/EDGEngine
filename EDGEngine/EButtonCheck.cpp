#include "EButtonCheck.h"

EButtonCheck::EButtonCheck(float _x, float _y, float _sx, float _sy, Enums::ButtonType _type): EButton(_x,_y,_sx,_sy)
{
	have_icon = true;
	gabarite = DefaultGabarite::gabarite_checked;
	have_text = false;

	master_position = Enums::PositionMaster::FILTER_BLOCK;

	description_text = "Click to change";


}

void EButtonCheck::click_event()
{
	is_checked = !is_checked;

	if (is_checked)
	{
		gabarite = DefaultGabarite::gabarite_checked;
	}
	else
	{
		gabarite = DefaultGabarite::gabarite_unchecked;
	}
}
