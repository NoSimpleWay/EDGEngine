#pragma once
#include "EButton.h"

class EButtonInputSearchItem : public EButton
{
public:
	//EButtonInputSearchItem(float _x, float _y, float _sx, float _sy);;

	EButtonInputSearchItem(float _x, float _y, float _sx, float _sy, Enums::ButtonType _type);

	//void input_event();
	void input_event();


	//void click_event();
	// конструктор класса SecondClass вызывает конструктор класса FirstClass
};

