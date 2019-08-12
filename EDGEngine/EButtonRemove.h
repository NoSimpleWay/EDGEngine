#pragma once
#include "EButton.h"
#include "StaticData.h"


class EButtonRemove : public EButton
{
public:
	//EButtonService(float _x, float _y, float _sx, float _sy);   // конструктор класса SecondClass вызывает конструктор класса FirstClass

	EButtonRemove(float _x, float _y, float _sx, float _sy, Enums::ButtonType _type);

	virtual void click_event();

	virtual void update_localisation();

};