#pragma once
#include <string>
class EGabarite
{
public:
	float x;
	float y;

	float x2;
	float y2;

	float size_x;
	float size_y;



	std::string name;

	EGabarite(std::string _name, float _x, float _y, float _size_x, float _size_y);
	~EGabarite();
};

class DefaultGabarite
{
public:
	static EGabarite* gabarite_white;
	static EGabarite* gabarite_undefined;
	static EGabarite* gabarite_plus;
	static EGabarite* gabarite_checked;
	static EGabarite* gabarite_unchecked;
	static EGabarite* gabarite_remove;
	static EGabarite* gabarite_plus_wide;
	static EGabarite* gabarite_increase;
	static EGabarite* gabarite_decrease;
	static EGabarite* gabarite_close;
	static EGabarite* gabarite_visual_mode;
	static EGabarite* gabarite_play_sound;

	static EGabarite* gabarite_slider_hue;
	static EGabarite* gabarite_slider_saturation;
	static EGabarite* gabarite_slider_value;
	static EGabarite* gabarite_slider_alpha;

	static EGabarite* gabarite_visual_editor_bg;

	static EGabarite* gabarite_minimap_icon[6];

	static EGabarite* gabarite_button_load;
	static EGabarite* gabarite_button_save;

	static EGabarite* gabarite_bg_noise;
	static EGabarite* gabarite_ray_icon;

	static EGabarite* gabarite_plus_gray;
	static EGabarite* gabarite_up_gray;
	static EGabarite* gabarite_down_gray;

	static EGabarite* gabarite_remove_block;

	static EGabarite* gabarite_gray_eye;
	static EGabarite* gabarite_ray_icon_remove;







};
