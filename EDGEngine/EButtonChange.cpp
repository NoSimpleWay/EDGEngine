#include "EButtonChange.h"
#include "StaticData.h"

EButtonChange::EButtonChange(float _x, float _y, float _sx, float _sy, Enums::ButtonType _type, bool _inc): EButton(_x, _y, _sx, _sy)
{
	have_icon = true;
	if (_inc)
	{
		gabarite = DefaultGabarite::gabarite_increase;
	}
	else
	{
		gabarite = DefaultGabarite::gabarite_decrease;
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

void EButtonChange::update_localisation()
{
	if (is_increase)
	{
		if (button_type == Enums::ButtonType::BUTTON_SOCKET_RED)
		{description_text = EString::localize_it("description_increase_red_socket");}

		if (button_type == Enums::ButtonType::BUTTON_SOCKET_GREEN)
		{description_text = EString::localize_it("description_increase_green_socket");}

		if (button_type == Enums::ButtonType::BUTTON_PLUS_NEW_FILTER_BLOCK)
		{description_text = EString::localize_it("description_increase_blue_socket");}

		if (button_type == Enums::ButtonType::BUTTON_SOCKET_WHITE)
		{description_text = EString::localize_it("description_increase_white_socket");}
	}
	else
	{
		if (button_type == Enums::ButtonType::BUTTON_SOCKET_RED)
		{description_text = EString::localize_it("description_decrease_red_socket");}

		if (button_type == Enums::ButtonType::BUTTON_SOCKET_GREEN)
		{description_text = EString::localize_it("description_decrease_green_socket");}

		if (button_type == Enums::ButtonType::BUTTON_PLUS_NEW_FILTER_BLOCK)
		{description_text = EString::localize_it("description_decrease_blue_socket");}

		if (button_type == Enums::ButtonType::BUTTON_SOCKET_WHITE)
		{description_text = EString::localize_it("description_decrease_white_socket");}
	}
}


