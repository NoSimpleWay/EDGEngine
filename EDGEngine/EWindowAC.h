#pragma once
#include "EWindow.h"
#include "Enums.h"

class EWindowAC : public EWindow
{
public:

	std::string cached_text_search;

	EWindowAC(int _id, bool _can_be_closed);
	virtual void button_event(EButton* _b);

	Enums::WindowAcceptCancelMode window_mode = Enums::WindowAcceptCancelMode::AC_unsave_open;
	virtual void update_localisation();

	std::string window_text;
	virtual void text_pass(Batcher* _batch);
	virtual void manual_event();

	FilterBlockSeparator* master_separator = NULL;
};