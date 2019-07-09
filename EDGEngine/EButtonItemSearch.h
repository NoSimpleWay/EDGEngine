#pragma once
#include "EButton.h"

class EButtonItemSearch : public EButton
{
public:
	EButtonItemSearch(float _x, float _y, float _sx, float _sy);;

	void click_event()
	{
		std::cout << " you are idiot? " << std::endl;
	}
	//void click_event();
	// конструктор класса SecondClass вызывает конструктор класса FirstClass
};