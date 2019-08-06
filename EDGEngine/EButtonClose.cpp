#include "EButtonClose.h"

EButtonClose::EButtonClose(float _x, float _y, float _sx, float _sy): EButton(_x, _y, _sx, _sy)
{
	have_text = false;
	have_icon = true;

	master_position = Enums::PositionMaster::WINDOW;

	position_mode_x = Enums::PositionMode::RIGHT;
	position_mode_y = Enums::PositionMode::UP;

	gabarite = DefaultGabarite::gabarite_close;

	have_bg = false;
	description_text = "Закрыть окно";
	icon_adaptation = false;
}

void EButtonClose::click_event()
{
	master_window->is_active = false;
}
