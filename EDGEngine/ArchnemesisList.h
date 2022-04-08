#include <string>
#include "Enums.h"
#pragma once
class ArchnemesisList
{
public:
	std::string base_name;
	std::string ru_name;
	Enums::CostList cost = Enums::CostList::TRASH;

	ArchnemesisList();
	~ArchnemesisList();
};