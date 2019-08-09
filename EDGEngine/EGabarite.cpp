#include "EGabarite.h"

EGabarite::EGabarite(std::string _name, float _x, float _y, float _size_x, float _size_y)
{
	x = _x;
	y = _y;

	size_x = _size_x;
	size_y = _size_y;

	x2 = _x + _size_x;
	y2 = _y + _size_y;

	size_x *= 4096.0f;
	size_y *= 4096.0f;

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

EGabarite* DefaultGabarite::gabarite_minimap_icon[6];

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

