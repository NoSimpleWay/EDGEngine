#pragma once
#include <string>
class EGabarite
{
public:
	float x = 0;
	float y = 0;

	float x2 = 0;
	float y2 = 0;

	float size_x = 0;
	float size_y = 0;

	float uv_size_x = 0;
	float uv_size_y = 0;



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

	static EGabarite* gabarite_shaper_bg;
	static EGabarite* gabarite_elder_bg;

	static EGabarite* gabarite_background;

	static EGabarite* gabarite_button_new;

	static EGabarite* gabarite_plus_circle;
	static EGabarite* gabarite_remove_circle;

	static EGabarite* gabarite_flag_EN;
	static EGabarite* gabarite_flag_RU;

	static EGabarite* gabarite_open_simulator;
	static EGabarite* gabarite_configue_font;
	static EGabarite* gabarite_configue_language;

	static EGabarite* gabarite_cut_gray;

	static EGabarite* gabarite_bg_bright;
	static EGabarite* gabarite_bg_dark;

	static EGabarite* gabarite_button_refresh;

	static EGabarite* gabarite_button_bright_bg;
	static EGabarite* gabarite_button_dark_bg;

	static EGabarite* gabarite_button_clone;
	static EGabarite* gabarite_button_separator;
	static EGabarite* gabarite_button_collapse;

	static EGabarite* gabarite_error;

	static EGabarite* gabarite_oil[12];

	static EGabarite* gabarite_cap;
	static EGabarite* gabarite_socket;

	static EGabarite* gabarite_link_vertical;
	static EGabarite* gabarite_link_horizontal;
	static EGabarite* gabarite_cap_rama;
	static EGabarite* gabarite_wood_bg;

	static EGabarite* gabarite_wood_button_bg;
	static EGabarite* gabarite_save_autogen;
	static EGabarite* gabarite_plus_equal;


};
