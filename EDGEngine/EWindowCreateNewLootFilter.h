#pragma once
#include "EWindow.h"
#include "Enums.h"

class EWindowCreateNewLootFilter : public EWindow
{
public:

	EButton* link_to_input_button;
	EButton* link_to_accept_button;

	EWindowCreateNewLootFilter(int _id, bool _can_be_closed);

	virtual void update(float _d);

	virtual void input_event(EButton* _b);
	virtual void draw(Batcher* _batch, float _delta);

};