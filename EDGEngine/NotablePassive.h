#pragma once
#include <string>
#include "EGabarite.h"

class NotablePassive
{
public:

	int need_verdant_oil;
	int need_sepia_oil;
	int need_clear_oil;
	int need_amber_oil;
	int need_teal_oil;
	int need_azure_oil;
	int need_violet_oil;
	int need_crimson_oil;
	int need_black_oil;
	int need_opacelent_oil;
	int need_silver_oil;
	int need_golden_oil;

	std::string passive_name;
	std::string passive_description;

	std::string passive_ru_name;
	std::string passive_ru_description;

	EGabarite* gabarite;

	NotablePassive();
	~NotablePassive();
};