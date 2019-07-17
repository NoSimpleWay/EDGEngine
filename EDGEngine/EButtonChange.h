#pragma once
#include "EButton.h"


class EButtonChange : public EButton
{
public:
	//EButtonService(float _x, float _y, float _sx, float _sy);   // конструктор класса SecondClass вызывает конструктор класса FirstClass

	EButtonChange(float _x, float _y, float _sx, float _sy, Enums::ButtonType _type, bool _inc);

	virtual void click_event();
	virtual void draw(Batcher* _batch);
	bool is_increase=false;


};