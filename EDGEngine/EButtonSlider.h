#pragma once
#include "EButton.h"


class EButtonSlider : public EButton
{
public:
	//EButtonService(float _x, float _y, float _sx, float _sy);   // конструктор класса SecondClass вызывает конструктор класса FirstClass

	//EButtonSlider(float _x, float _y, float _sx, float _sy);

	EButtonSlider(float _x, float _y, float _sx, float _sy, Enums::ButtonType _type);

	virtual void click_event();
	virtual void slide_drag_event();
	virtual void update_additional(float _d);

};