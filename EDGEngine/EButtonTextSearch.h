#pragma once
#include "EButton.h"
#include "StaticData.h"


class EButtonTextSearch : public EButton
{
public:
	//EButtonService(float _x, float _y, float _sx, float _sy);   // конструктор класса SecondClass вызывает конструктор класса FirstClass

	EButtonTextSearch(float _x, float _y, float _sx, float _sy, Enums::ButtonType _type);

	virtual void click_event();
	virtual void right_click_event();
};