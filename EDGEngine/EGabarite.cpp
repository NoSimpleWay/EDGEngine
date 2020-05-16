#include "EGabarite.h"

EGabarite::EGabarite(std::string _name, float _x, float _y, float _size_x, float _size_y)
{
	x = _x;
	y = _y;

	uv_size_x = _size_x;
	uv_size_y = _size_y;

	x2 = _x + _size_x;
	y2 = _y + _size_y;

	size_x = uv_size_x * 4096.0f;
	size_y = uv_size_y * 4096.0f;

	name = _name;
}

EGabarite::~EGabarite()
{

}

EGabarite* DefaultGabarite::gabarite_white=NULL;
EGabarite* DefaultGabarite::gabarite_undefined=NULL;
EGabarite* DefaultGabarite::gabarite_plus=NULL;
EGabarite* DefaultGabarite::gabarite_checked =NULL;
EGabarite* DefaultGabarite::gabarite_unchecked =NULL;
EGabarite* DefaultGabarite::gabarite_remove =NULL;
EGabarite* DefaultGabarite::gabarite_plus_wide =NULL;
EGabarite* DefaultGabarite::gabarite_increase =NULL;
EGabarite* DefaultGabarite::gabarite_decrease =NULL;
EGabarite* DefaultGabarite::gabarite_close =NULL;
EGabarite* DefaultGabarite::gabarite_visual_mode =NULL;
EGabarite* DefaultGabarite::gabarite_play_sound =NULL;

EGabarite* DefaultGabarite::gabarite_slider_hue =NULL;
EGabarite* DefaultGabarite::gabarite_slider_saturation =NULL;
EGabarite* DefaultGabarite::gabarite_slider_value =NULL;
EGabarite* DefaultGabarite::gabarite_slider_alpha =NULL;

EGabarite* DefaultGabarite::gabarite_visual_editor_bg =NULL;

EGabarite* DefaultGabarite::gabarite_minimap_icon[12];

EGabarite* DefaultGabarite::gabarite_button_load = NULL;
EGabarite* DefaultGabarite::gabarite_button_save = NULL;

EGabarite* DefaultGabarite::gabarite_bg_noise = NULL;
EGabarite* DefaultGabarite::gabarite_ray_icon = NULL;

EGabarite* DefaultGabarite::gabarite_plus_gray = NULL;
EGabarite* DefaultGabarite::gabarite_up_gray = NULL;
EGabarite* DefaultGabarite::gabarite_down_gray = NULL;

EGabarite* DefaultGabarite::gabarite_remove_block = NULL;

EGabarite* DefaultGabarite::gabarite_gray_eye = NULL;
EGabarite* DefaultGabarite::gabarite_ray_icon_remove = NULL;

EGabarite* DefaultGabarite::gabarite_shaper_bg = NULL;
EGabarite* DefaultGabarite::gabarite_elder_bg = NULL;

EGabarite* DefaultGabarite::gabarite_background = NULL;

EGabarite* DefaultGabarite::gabarite_button_new = NULL;

EGabarite* DefaultGabarite::gabarite_plus_circle = NULL;
EGabarite* DefaultGabarite::gabarite_remove_circle = NULL;

EGabarite* DefaultGabarite::gabarite_flag_EN = NULL;
EGabarite* DefaultGabarite::gabarite_flag_RU = NULL;

EGabarite* DefaultGabarite::gabarite_open_simulator = NULL;
EGabarite* DefaultGabarite::gabarite_configue_font = NULL;
EGabarite* DefaultGabarite::gabarite_configue_language = NULL;

EGabarite* DefaultGabarite::gabarite_cut_gray = NULL;

EGabarite* DefaultGabarite::gabarite_bg_bright = NULL;
EGabarite* DefaultGabarite::gabarite_bg_dark = NULL;

EGabarite* DefaultGabarite::gabarite_button_refresh = NULL;

EGabarite* DefaultGabarite::gabarite_button_bright_bg = NULL;
EGabarite* DefaultGabarite::gabarite_button_dark_bg = NULL;

EGabarite* DefaultGabarite::gabarite_button_clone = NULL;
EGabarite* DefaultGabarite::gabarite_button_separator = NULL;

EGabarite* DefaultGabarite::gabarite_button_collapse = NULL;

EGabarite* DefaultGabarite::gabarite_error = NULL;

EGabarite* DefaultGabarite::gabarite_oil[12];

EGabarite* DefaultGabarite::gabarite_cap;
EGabarite* DefaultGabarite::gabarite_socket;

EGabarite* DefaultGabarite::gabarite_link_vertical;
EGabarite* DefaultGabarite::gabarite_link_horizontal;
EGabarite* DefaultGabarite::gabarite_cap_rama;
EGabarite* DefaultGabarite::gabarite_wood_bg;

EGabarite* DefaultGabarite::gabarite_wood_button_bg;
EGabarite* DefaultGabarite::gabarite_save_autogen;
EGabarite* DefaultGabarite::gabarite_plus_equal;

EGabarite* DefaultGabarite::gabarite_shaper_small;
EGabarite* DefaultGabarite::gabarite_elder_small;
EGabarite* DefaultGabarite::gabarite_blighted_small;

EGabarite* DefaultGabarite::gabarite_button_continue_on = NULL;
EGabarite* DefaultGabarite::gabarite_button_continue_off = NULL;

EGabarite* DefaultGabarite::gabarite_button_disable_block = NULL;
EGabarite* DefaultGabarite::gabarite_button_enable_block = NULL;

EGabarite* DefaultGabarite::gabarite_shaper_slider_bg = NULL;
EGabarite* DefaultGabarite::gabarite_shaper_slider_trail = NULL;
EGabarite* DefaultGabarite::gabarite_shaper_slider_head = NULL;

EGabarite* DefaultGabarite::gabarite_button_oil = NULL;






