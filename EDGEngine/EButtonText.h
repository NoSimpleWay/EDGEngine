#pragma once
#include "EButton.h"


class EButtonText : public EButton
{
public:
	//EButtonService(float _x, float _y, float _sx, float _sy);   // конструктор класса SecondClass вызывает конструктор класса FirstClass

	EButtonText(float _x, float _y, float _sx, float _sy, Enums::ButtonType _type);

	virtual void click_event();
	virtual void input_event();
	virtual void input_finish_event();

	virtual void update_localisation();
	virtual void update_additional(float _d);
};