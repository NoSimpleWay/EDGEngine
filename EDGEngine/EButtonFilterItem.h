#pragma once
#include "EButton.h"
#include "StaticData.h"


class EButtonFilterItem : public EButton
{
public:
	EButtonFilterItem(float _x, float _y, float _sx, float _sy);   // ����������� ������ SecondClass �������� ����������� ������ FirstClass

	virtual void click_event();
	bool is_plus = false;

	virtual void update_localisation();
};