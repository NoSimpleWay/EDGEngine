#pragma once
class EControl
{
public:
	static int WTF;

	static int mouse_x;
	static int mouse_y;

	static bool button_pressed;
	static bool mouse_pressed;
	static bool button_backspace_released;
	static int block_scroll;

	static char last_inputed_char;
};