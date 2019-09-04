#pragma once
#include <string>
#include "FilterBlock.h"

class FilterBlockSeparator
{
public:
	std::string name;
	bool is_collapsed = false;

	int separator_start;
	int separator_end;

	float x;
	float y;

	float size_x;
	float size_y;

	FilterBlockSeparator();

	bool is_active = false;
	EButton* link_to_collapse;
	EButton* link_to_remove;
	EButton* link_to_caption_text;
};