#pragma once
#include "EButton.h"

class EButtonAddNewBaseData : public EButton
{
public:
	EButtonAddNewBaseData(float _x, float _y, float _sx, float _sy);

	void click_event();
	virtual void input_finish_event();
	//{
	//	std::cout << " you are idiot? " << std::endl;
	//}
	//void click_event();
	// ����������� ������ SecondClass �������� ����������� ������ FirstClass
};