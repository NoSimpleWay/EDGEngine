#pragma once
#include "EWindow.h"
#include "Enums.h"

class EWindowSelectLootPattern : public EWindow
{
public:

	EWindowSelectLootPattern(int _id, bool _can_be_closed);

	std::vector <std::string> text_list;



	virtual void update(float _d);
	virtual void draw(Batcher* _batch, float _delta);
	virtual void update_localisation();
	virtual void input_event(EButton* _b);
	virtual void pre_draw(Batcher* _batch, float _delta);
};