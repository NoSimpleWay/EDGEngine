#include "EButton.h"

class EButtonFilterItem : public EButton
{
public:
	EButtonFilterItem(float _x, float _y, float _sx, float _sy) : EButton(_x, _y, _sx, _sy)   // конструктор класса SecondClass вызывает конструктор класса FirstClass
	{
		master_position = Enums::ButtonPositionMaster::FILTER_BLOCK;
		have_text = false;
	}


};