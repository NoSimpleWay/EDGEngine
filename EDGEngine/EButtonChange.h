#pragma once
#include "EButton.h"


class EButtonChange : public EButton
{
public:
	//EButtonService(float _x, float _y, float _sx, float _sy);   // ����������� ������ SecondClass �������� ����������� ������ FirstClass

	EButtonChange(float _x, float _y, float _sx, float _sy, Enums::ButtonType _type, bool _inc);

	virtual void click_event();
	bool is_increase=false;


};