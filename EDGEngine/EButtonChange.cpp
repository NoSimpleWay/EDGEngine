#include "EButtonChange.h"
#include "StaticData.h"

EButtonChange::EButtonChange(float _x, float _y, float _sx, float _sy, Enums::ButtonType _type, bool _inc): EButton(_x, _y, _sx, _sy)
{
	have_icon = true;
	if (_inc)
	{
		gabarite = DefaultGabarite::gabarite_increase;
		description_text = "Increase value";
	}
	else
	{
		gabarite = DefaultGabarite::gabarite_decrease;
		description_text = "Decrease value";
	}

	have_rama = false;

	master_position = Enums::PositionMaster::WINDOW;

	have_text = false;

	
}

void EButtonChange::click_event()
{

}

void EButtonChange::draw(Batcher* _batch)
{
}
