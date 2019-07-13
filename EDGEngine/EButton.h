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

	int drop_elements = 0;
	std::vector<string> drop_text;
	bool have_list_color=false;
	std::vector<EColor*> drop_list_color;

	EGabarite* gabarite=NULL;

	bool have_icon = false;
	Enums::PositionMaster master_position=Enums::PositionMaster::SCREEN;

	Enums::PositionMode position_mode_x=Enums::PositionMode::LEFT;
	Enums::PositionMode position_mode_y=Enums::PositionMode::DOWN;

	Enums::PositionMode text_align_x=Enums::PositionMode::LEFT;

	FilterBlock* master_block;
	EWindow* master_window;


	float master_position_x = 0;
	float master_position_y = 0;

	EButton();
	EButton(float _x, float _y, float _sx, float _sy);
	EButton(float _x, float _y, float _sx, float _sy, Enums::ButtonType _type);

	bool have_description = true;
	string description_text;

	bool have_text = true;

	string input_hint;



	~EButton();

	bool is_number(char _c);

	bool is_overlap();
	bool is_click();
	bool is_right_click();
	void update(float _d);
	void draw(Batcher* _batch);
	void text_pass(Batcher* _batch);
	virtual void incoming_data(FilterBlock* _block);


	virtual void click_event();
	virtual void input_event();
	virtual void input_finish_event();
	virtual void drop_list_select_event();


	static int top_window_id;

	bool flash_line_active = false;
	float flash_cooldown = 0.5f;

	bool can_be_removed = false;
	bool need_remove = false;

	bool have_rama=false;
	int rama_thikness = 2;
	EColor* rama_color = new EColor();
	EColor* bg_color = new EColor(0.8f,0.8f,0.8f,0.75f);

	int catched_element = 0;
	int selected_element = 0;

	Enums::ButtonType button_type;

	bool input_only_numbers = false;

	int data_id;
	
	
};