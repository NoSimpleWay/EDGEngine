#pragma once
#include "EButton.h"



class EButtonCheck : public EButton
{
public:
	//EButtonService(float _x, float _y, float _sx, float _sy);   // ����������� ������ SecondClass �������� ����������� ������ FirstClass

	EButtonCheck(float _x, float _y, float _sx, float _sy, Enums::ButtonType _type);
	virtual void click_event();
	bool is_checked=true;


};