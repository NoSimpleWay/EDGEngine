#pragma once
#include "EButton.h"



class EButtonService : public EButton
{
public:
	//EButtonService(float _x, float _y, float _sx, float _sy);   // конструктор класса SecondClass вызывает конструктор класса FirstClass

	EButtonService(float _x, float _y, float _sx, float _sy, Enums::ButtonType _type);

	virtual void click_event();
	virtual void right_click_event();

	bool is_plus = false;

	virtual void update_localisation();
};