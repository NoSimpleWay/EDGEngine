#pragma once
#include <vector>
#include "EButtonExplicit.h"

class EButtonExplicit;
class ExplicitGroup
{
public:
	std::vector <EButtonExplicit*>  button_list;
	EButton*  button_close;
	EButton*  button_add;

	bool is_active = false;

	ExplicitGroup();
	~ExplicitGroup();
};