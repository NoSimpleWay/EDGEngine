#pragma once
#include <vector>
#include "EWindow.h"
class EControl
{
public:
	static int WTF;

	static int mouse_x;
	static int mouse_y;

	static bool button_pressed;
	static bool button_right_pressed;

	static bool mouse_pressed;
	static bool mouse_right_pressed;


	static bool button_backspace_released;
	static int block_scroll;

	static char last_inputed_char;
	static int last_inputed_char_id;

	static float delete_button_hold_time;

	static std::vector<EWindow*> window_list;
};