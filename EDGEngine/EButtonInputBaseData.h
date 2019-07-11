#pragma once
#include "EButton.h"

class EButtonInputBaseData : public EButton
{
public:
	EButtonInputBaseData(float _x, float _y, float _sx, float _sy, Enums::ButtonType _type);

	void click_event();
	virtual void incoming_data(FilterBlock* _filter);
	virtual void input_finish_event();
	//{
	//	std::cout << " you are idiot? " << std::endl;
	//}
	//void click_event();
	// конструктор класса SecondClass вызывает конструктор класса FirstClass
};