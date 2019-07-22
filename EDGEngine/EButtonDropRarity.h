#pragma once
#include "EButton.h"
#include "StaticData.h"
#include "Enums.h"


class EButtonDropRarity : public EButton
{
public:


	EButtonDropRarity(float _x, float _y, float _sx, float _sy, Enums::ButtonType _type);

	virtual void click_event();
	virtual void incoming_data(FilterBlock* _filter);
	virtual void drop_list_select_event();





};