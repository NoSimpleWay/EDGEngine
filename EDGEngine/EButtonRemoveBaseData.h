#pragma once
#include "EButton.h"
#include "StaticData.h"


class EButtonRemoveBaseData : public EButton
{
public:
	//EButtonService(float _x, float _y, float _sx, float _sy);   // ����������� ������ SecondClass �������� ����������� ������ FirstClass

	EButtonRemoveBaseData(float _x, float _y, float _sx, float _sy, Enums::ButtonType _type);

	virtual void click_event();


};