#pragma once
#include "EButton.h"


class EButtonText : public EButton
{
public:
	//EButtonService(float _x, float _y, float _sx, float _sy);   // ����������� ������ SecondClass �������� ����������� ������ FirstClass

	EButtonText(float _x, float _y, float _sx, float _sy, Enums::ButtonType _type);

	virtual void click_event();
	virtual void input_event();


};