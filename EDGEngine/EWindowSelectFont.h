#pragma once
#include "EWindow.h"
#include "Enums.h"

class EWindowSelectFont : public EWindow
{
public:


	std::string cached_text_search;

	EWindowSelectFont(int _id, bool _can_be_closed);

	void create_font_button(std::string _s, EFont* _f, int _id);

	virtual void update(float _d);

	virtual void draw(Batcher* _batch, float _delta);

	virtual void update_localisation();

};