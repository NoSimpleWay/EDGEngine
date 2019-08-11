#pragma once
#include "EWindow.h"
#include "Enums.h"

class EWindowCreateNewLootFilter : public EWindow
{
public:


	EWindowCreateNewLootFilter(int _id, bool _can_be_closed);

	virtual void update(float _d);

	virtual void input_event(EButton* _b);
	virtual void draw(Batcher* _batch, float _delta);

};