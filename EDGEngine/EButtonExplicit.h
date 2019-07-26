#pragma once
#include "EButton.h"
class EButtonExplicit : public EButton
{
public:
	//EButtonService(float _x, float _y, float _sx, float _sy);   // конструктор класса SecondClass вызывает конструктор класса FirstClass

	EButtonExplicit(float _x, float _y, float _sx, float _sy);
	int explicit_group_id;

	virtual void click_event();

	bool is_plus = false;


};