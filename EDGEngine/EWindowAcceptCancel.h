#pragma once
#include "EWindow.h"
#include "Enums.h"


class EWindowAcceptCancel : public EWindow
{
public:

	Enums::WindowAcceptCancelMode window_mode;
	std::string cached_text_search;

	EWindowAcceptCancel(int _id, bool _can_be_closed);

	void create_font_button(std::string _s, EFont* _f, int _id);

	virtual void update_localisation();

	virtual void button_event(EButton* _b);

};