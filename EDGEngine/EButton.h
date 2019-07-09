#pragma once


#include <glad/glad.h>
#include "Batcher.h"
#include <iostream>
#include "Helper.h"
#include <GLFW/glfw3.h>
#include "EFont.h"
#include "Enums.h"


#include "FilterBlock.h"
#include "EWindow.h"

class FilterBlock;
class EWindow;
class EButton
{
public:
	float button_x = 10;
	float button_y = 200;

	float button_size_x = 100;
	float button_size_y = 25;

	std::string text = "!";

	bool have_input_mode = false;
	bool is_input_mode_active = false;

	bool is_active = true;

	float bound_size_left = 0;
	float bound_size_right = 0;
	float bound_size_up = 0;
	float bound_size_down = 0;

	bool is_expanded = false;
	bool is_drop_list = false;

	int drop_elements = 5;
	EGabarite* gabarite=NULL;

	bool have_icon = false;
	Enums::ButtonPositionMaster master_position=Enums::ButtonPositionMaster::SCREEN;

	Enums::ButtonPositionMode position_mode_x=Enums::ButtonPositionMode::LEFT;
	Enums::ButtonPositionMode position_mode_y=Enums::ButtonPositionMode::DOWN;

	FilterBlock* master_block;
	EWindow* master_window;


	float master_position_x = 0;
	float master_position_y = 0;

	EButton();
	EButton(float _x, float _y, float _sx, float _sy);

	bool have_description = true;
	string description_text;

	bool have_text = true;



	~EButton();

	bool is_overlap();
	bool is_click();
	void update(float _d);
	void draw(Batcher* _batch);


	virtual void click_event();
	virtual void input_event();
};