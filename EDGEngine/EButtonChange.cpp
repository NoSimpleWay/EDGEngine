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

	if (button_type == Enums::ButtonType::BUTTON_SOCKET_LINKED)
	{
		//std::cout << "red " << master_block->red_sockets << std::endl;
		if (is_increase)
		{
			if (master_block->socket_group_links.at(data_id) < 6) { master_block->socket_group_links.at(data_id)++; }
		}
		else
		{
			if (master_block->socket_group_links.at(data_id) > 0) { master_block->socket_group_links.at(data_id)--; }
		}
	}

	if (button_type == Enums::ButtonType::BUTTON_SOCKET_RED)
	{
		//std::cout << "red " << master_block->red_sockets << std::endl;
		if (is_increase)
		{
			if (master_block->red_sockets.at(data_id) < 6) { master_block->red_sockets.at(data_id)++; }
		}
		else
		{
			if (master_block->red_sockets.at(data_id) > 0) { master_block->red_sockets.at(data_id)--; }
		}
	}

	if (button_type == Enums::ButtonType::BUTTON_SOCKET_GREEN)
	{
		if (is_increase)
		{
			if (master_block->green_sockets.at(data_id) < 6) { master_block->green_sockets.at(data_id)++; }
		}
		else
		{
			if (master_block->green_sockets.at(data_id) > 0) { master_block->green_sockets.at(data_id)--; }
		}
	}

	if (button_type == Enums::ButtonType::BUTTON_SOCKET_BLUE)
	{
		if (is_increase)
		{
			if (master_block->blue_sockets.at(data_id) < 6) { master_block->blue_sockets.at(data_id)++; }
		}
		else
		{
			if (master_block->blue_sockets.at(data_id) > 0) { master_block->blue_sockets.at(data_id)--; }
		}
	}

	if (button_type == Enums::ButtonType::BUTTON_SOCKET_WHITE)
	{
		if (is_increase)
		{
			if (master_block->white_sockets.at(data_id) < 6) { master_block->white_sockets.at(data_id)++; }
		}
		else
		{
			if (master_block->white_sockets.at(data_id) > 0) { master_block->white_sockets.at(data_id)--; }
		}
	}

	if (button_type == Enums::ButtonType::BUTTON_SOCKET_ABYSS)
	{
		if (is_increase)
		{
			if (master_block->abyss_sockets.at(data_id) < 6) { master_block->abyss_sockets.at(data_id)++; }
		}
		else
		{
			if (master_block->abyss_sockets.at(data_id) > 0) { master_block->abyss_sockets.at(data_id)--; }
		}
	}

	if (button_type == Enums::ButtonType::BUTTON_SOCKET_DELVE)
	{
		if (is_increase)
		{
			if (master_block->delve_sockets.at(data_id) < 6) { master_block->delve_sockets.at(data_id)++; }
		}
		else
		{
			if (master_block->delve_sockets.at(data_id) > 0) { master_block->delve_sockets.at(data_id)--; }
		}
	}

	if (button_type == Enums::ButtonType::BUTTON_CHANGE_OIL_COUNT)
	{
		std::cout << "oil: " << std::to_string(StaticData::window_oil->oil_count.at(data_id)) << std::endl;
		if (is_increase)
		{
			if (StaticData::window_oil->oil_count.at(data_id) < 3)
			{
				StaticData::window_oil->oil_count.at(data_id)++;
			}
		}
		else
		{
			if (StaticData::window_oil->oil_count.at(data_id) > 0)
			{
				StaticData::window_oil->oil_count.at(data_id)--;
			}
		}

		StaticData::window_oil->update_passives_button();
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


