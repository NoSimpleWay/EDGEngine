#pragma once
#include "EButton.h"
#include "StaticData.h"


class EButtonSocketGroup : public EButton
{
public:
	//EButtonService(float _x, float _y, float _sx, float _sy);   // конструктор класса SecondClass вызывает конструктор класса FirstClass

	EButtonSocketGroup(float _x, float _y, float _sx, float _sy, Enums::ButtonType _type);

	virtual void click_event();
	virtual void additional_draw(Batcher* _batch);



};