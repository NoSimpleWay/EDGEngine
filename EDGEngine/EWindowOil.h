#pragma once
#include "EWindow.h"
#include "Enums.h"

class EWindowOil : public EWindow
{
public:


	std::string cached_text_search;

	EWindowOil(int _id, bool _can_be_closed);


	virtual void update(float _d);

	virtual void draw(Batcher* _batch, float _delta);

	virtual void update_localisation();

};