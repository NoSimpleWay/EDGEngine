#include "EButtonSlider.h"
#include "EUtils.h"

EButtonSlider::EButtonSlider(float _x, float _y, float _sx, float _sy, Enums::ButtonType _type): EButton(_x, _y, _sx, _sy)
{
	button_type = _type;
	description_text = "Change value";

	master_position = Enums::PositionMaster::WINDOW;

	have_icon = true;

	if (
		(button_type == Enums::ButtonType::BUTTON_BG_H) ||
		(button_type == Enums::ButtonType::BUTTON_TEXT_H) ||
		(button_type == Enums::ButtonType::BUTTON_RAMA_H)
		)
	{gabarite = DefaultGabarite::gabarite_slider_hue;}

	if (
		(button_type == Enums::ButtonType::BUTTON_BG_S) ||
		(button_type == Enums::ButtonType::BUTTON_TEXT_S) ||
		(button_type == Enums::ButtonType::BUTTON_RAMA_S)
		)
	{gabarite = DefaultGabarite::gabarite_slider_saturation;}

	if (
		(button_type == Enums::ButtonType::BUTTON_BG_V) ||
		(button_type == Enums::ButtonType::BUTTON_TEXT_V) ||
		(button_type == Enums::ButtonType::BUTTON_RAMA_V)
		)
	{gabarite = DefaultGabarite::gabarite_slider_value;}

	if (
		(button_type == Enums::ButtonType::BUTTON_BG_ALPHA) ||
		(button_type == Enums::ButtonType::BUTTON_TEXT_ALPHA) ||
		(button_type == Enums::ButtonType::BUTTON_RAMA_ALPHA)
		)
	{gabarite = DefaultGabarite::gabarite_slider_alpha;}

	is_slider = true;
	//is_holdable = true;

	have_text = false;

	icon_adaptation = false;

	

}

void EButtonSlider::click_event()
{
}

 void EButtonSlider::slide_drag_event()
{
	 if (button_type == Enums::ButtonType::BUTTON_BG_H) { master_block->bg_hue = slider_value * 360.0; }
	 if (button_type == Enums::ButtonType::BUTTON_BG_S) { master_block->bg_saturation = slider_value; }
	 if (button_type == Enums::ButtonType::BUTTON_BG_V) { master_block->bg_value = slider_value*255.0; }
	 if (button_type == Enums::ButtonType::BUTTON_BG_ALPHA) { master_block->bg_alpha = slider_value*255.0; }

	 if (button_type == Enums::ButtonType::BUTTON_TEXT_H) { master_block->text_color_hue = slider_value * 360.0; }
	 if (button_type == Enums::ButtonType::BUTTON_TEXT_S) { master_block->text_color_saturation = slider_value; }
	 if (button_type == Enums::ButtonType::BUTTON_TEXT_V) { master_block->text_color_value = slider_value*255.0; }
	 if (button_type == Enums::ButtonType::BUTTON_TEXT_ALPHA) { master_block->text_color_alpha = slider_value*255.0; }
	 
	 if (button_type == Enums::ButtonType::BUTTON_RAMA_H) { master_block->rama_hue = slider_value * 360.0; }
	 if (button_type == Enums::ButtonType::BUTTON_RAMA_S) { master_block->rama_saturation = slider_value; }
	 if (button_type == Enums::ButtonType::BUTTON_RAMA_V) { master_block->rama_value = slider_value*255.0; }
	 if (button_type == Enums::ButtonType::BUTTON_RAMA_ALPHA) { master_block->rama_alpha = slider_value*255.0; }

	 FilterBlock::change_color_extract(master_block);

	 /*
	 std::cout << "===============================" << std::endl;

	 std::cout << "bg hue			" << master_block->bg_hue << std::endl;
	 std::cout << "b saturation		" << master_block->bg_saturation << std::endl;
	 std::cout << "bg value			" << master_block->bg_value << std::endl;
	 std::cout << "-" << std::endl;*/
}
