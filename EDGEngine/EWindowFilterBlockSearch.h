#pragma once
#include "EWindow.h"
#include "Enums.h"

class EWindowFilterBlockSearch : public EWindow
{
public:
	EButton* input_button_link;

	EButton* checker_item_name_link;
	EButton* checker_class_name_link;
	EButton* checker_explicit_name_link;
	EButton* checker_prophecy_name_link;


	EWindowFilterBlockSearch(int _id, bool _can_be_closed);

	virtual void update(float _d);

	virtual void input_event(EButton* _b);


};