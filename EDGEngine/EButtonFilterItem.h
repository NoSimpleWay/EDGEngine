#pragma once
#include "EButton.h"
#include "StaticData.h"


class EButtonFilterItem : public EButton
{
public:
	EButtonFilterItem(float _x, float _y, float _sx, float _sy);   // конструктор класса SecondClass вызывает конструктор класса FirstClass

	void change_color_cheme();

	virtual void click_event();
	bool is_plus = false;
	bool is_full_equal_mode = false;

	virtual void update_localisation();
};