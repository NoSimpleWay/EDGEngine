#pragma once
#include "EButton.h"


class EButtonClose : public EButton
{
public:
	//EButtonService(float _x, float _y, float _sx, float _sy);   // конструктор класса SecondClass вызывает конструктор класса FirstClass

	EButtonClose(float _x, float _y, float _sx, float _sy);

	virtual void click_event();


};