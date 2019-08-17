#pragma once
#include "EWindow.h"

#include "EWindowFilterBlockSearch.h"
#include "EWindowFilterBlock.h"
#include "EWindowFindItem.cpp"
#include "EWindowAddNewBaseData.cpp"
#include "EWindowSocketGroup.cpp"
#include "EWindowFilterVisualEditor.cpp"
#include "EWindowMain.cpp"
#include "EWindowLoadingScreen.cpp"
#include "EWindowCreateNewLootFilter.h"
#include "EWindowSelectLocalisation.cpp"
#include "EWindowLootSimulator.h"





class StaticData
{
public:
	static EWindowFilterBlock* window_filter_block;
	static EWindowFindItem* window_find_item;
	static EWindowAddNewBaseData* window_add_new_base_data;
	static EWindowSocketGroup* window_socket_group;
	static EWindowFilterVisualEditor* window_filter_visual_editor;
	static EWindowMain* window_main;
	static EWindowFilterBlockSearch* window_filter_block_search;
	static EWindowLoadingScreen* window_loading_screen;
	static EWindowCreateNewLootFilter* window_new_loot_filter;
	static EWindowSelectLocalisation* window_select_localisation;
	static EWindowLootSimulator* window_loot_simulator;

};