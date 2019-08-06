#include "EButtonChange.h"
#include "StaticData.h"

EButtonChange::EButtonChange(float _x, float _y, float _sx, float _sy, Enums::ButtonType _type, bool _inc): EButton(_x, _y, _sx, _sy)
{
	have_icon = true;
	if (_inc)
	{
		gabarite = DefaultGabarite::gabarite_increase;
		description_text = "Увеличить значение";
	}
	else
	{
		gabarite = DefaultGabarite::gabarite_decrease;
		description_text = "Уменьшить значение";
	}

	is_increase = _inc;

	have_rama = false;

	master_position = Enums::PositionMaster::WINDOW;

	have_text = false;
	button_type = _type;

	
}

void EButtonChange::click_event()
{
	if (button_type == Enums::ButtonType::BUTTON_SOCKET_RED)
	{
		std::cout << "red " << master_block->red_sockets << std::endl;
		if (is_increase) {master_block->red_sockets++; std::cout<<"increase "<<std::endl;} else {master_block->red_sockets--;}
	}

	if (button_type == Enums::ButtonType::BUTTON_SOCKET_GREEN)
	{
		if (is_increase) {master_block->green_sockets++;} else {master_block->green_sockets--;}
	}

	if (button_type == Enums::ButtonType::BUTTON_SOCKET_BLUE)
	{
		if (is_increase) {master_block->blue_sockets++;} else {master_block->blue_sockets--;}
	}

	if (button_type == Enums::ButtonType::BUTTON_SOCKET_WHITE)
	{
		if (is_increase) {master_block->white_sockets++;} else {master_block->white_sockets--;}
	}

}


