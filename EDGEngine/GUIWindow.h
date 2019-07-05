#pragma once
#include <vector>

class GUIWindow
{
public:
	float window_x;
	float window_y;

	float window_size_x;
	float window_size_y;

	GUIWindow();
	~GUIWindow();
	void draw();

	//std::vector<EButton*> window_button_list;
};