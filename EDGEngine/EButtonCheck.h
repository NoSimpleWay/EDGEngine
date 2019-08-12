#pragma once
#include "EButton.h"



class EButtonCheck : public EButton
{
public:
	//EButtonService(float _x, float _y, float _sx, float _sy);   // конструктор класса SecondClass вызывает конструктор класса FirstClass


	EButtonCheck(float _x, float _y, float _sx, float _sy, Enums::ButtonType _type);
	virtual void click_event();
	bool is_checked=true;
	virtual void incoming_data(FilterBlock* _filter);
	void change_state(bool _b);

	virtual void update_localisation();

};