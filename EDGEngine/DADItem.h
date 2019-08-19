#pragma once
#include <string>
#include "EGabarite.h"

using namespace std;

class DADItem
{
public:
	string item_name;
	string item_name_ru;

	string icon_path;
	string base_class;
	string folder;
	string category;
	string subcategory;

	int width = 1;
	int height = 1;

	EGabarite* gabarite;

	DADItem()
	{

	}

	~DADItem()
	{

	}


};