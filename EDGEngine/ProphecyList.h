#include <string>
#include "Enums.h"
#pragma once
class ProphecyList
{
public:
	std::string base_name;
	std::string ru_name;
	Enums::CostList cost = Enums::CostList::TRASH;

	ProphecyList();
	~ProphecyList();
};