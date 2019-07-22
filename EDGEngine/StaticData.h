#pragma once
#include "EWindowFilterBlock.cpp"
#include "EWindowFindItem.cpp"
#include "EWindowAddNewBaseData.cpp"
#include "EWindowSocketGroup.cpp"
#include "EWindowFilterVisualEditor.cpp"


#include "EWindow.h"

class StaticData
{
public:
	static EWindowFilterBlock* window_filter_block;
	static EWindowFindItem* window_find_item;
	static EWindowAddNewBaseData* window_add_new_base_data;
	static EWindowSocketGroup* window_socket_group;
	static EWindowFilterVisualEditor* window_filter_visual_editor;
	

};