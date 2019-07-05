#pragma once

#include <glad/glad.h>
#include "Batcher.h"
#include <iostream>
#include "Helper.h"
#include <GLFW/glfw3.h>
#include "EFont.h"

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
	bool is_drop_list = true;

	int drop_elements = 5;

	EButton();




	~EButton();

	bool is_overlap();
	void update(float _d);
	void draw(Batcher* _batch);
	void text_pass(EFont* _font, Batcher* _batch);
};