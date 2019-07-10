#pragma once
#include "EButton.h"
#include "StaticData.h"
#include "Enums.h"


class EButtonDropCondition : public EButton
{
public:
	

	EButtonDropCondition(float _x, float _y, float _sx, float _sy, Enums::ButtonType _type);

	virtual void click_event();
	virtual void incoming_data(FilterBlock* _filter);

	

};