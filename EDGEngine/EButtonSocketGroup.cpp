#include "EButtonSocketGroup.h"


EButtonSocketGroup::EButtonSocketGroup(float _x, float _y, float _sx, float _sy, Enums::ButtonType _type): EButton(_x, _y, _sx, _sy)
{
	have_icon = false;
	gabarite = DefaultGabarite::gabarite_checked;
	have_text = false;

	have_rama = true;
	rama_color->set(EColorCollection::GREEN);
	rama_thikness = 2.0f;

	master_position = Enums::PositionMaster::FILTER_BLOCK;

	bg_color->set(EColorCollection::BLACK);
	//description_text = "Click to change";
}

void EButtonSocketGroup::click_event()
{
	//std::cout << "WTF?" << std::endl;
	StaticData::window_socket_group->is_active = true;
	StaticData::window_socket_group->button_event(this);
}

void EButtonSocketGroup::additional_draw(Batcher* _batch)
{
	description_text = EString::localize_it("socket_group_button_description")+"\\n";
	for (int i = 0; i < master_block->red_sockets.size(); i++)
	{
		description_text += "=============================\\n\\n";

		if (master_block->socket_group_links.at(i) > 0)
		{ description_text += EString::localize_it("socket_group_button_linked_sockets") + std::to_string(master_block->socket_group_links.at(i)) + "\\n";}

		if (master_block->red_sockets.at(i) > 0)
		{ description_text += EString::localize_it("socket_group_button_color_red") + std::to_string(master_block->red_sockets.at(i)) + "\\n";}

		if (master_block->green_sockets.at(i) > 0)
		{ description_text += EString::localize_it("socket_group_button_color_green") + std::to_string(master_block->green_sockets.at(i)) + "\\n";}

		if (master_block->blue_sockets.at(i) > 0)
		{ description_text += EString::localize_it("socket_group_button_color_blue") + std::to_string(master_block->blue_sockets.at(i)) + "\\n";}

		if (master_block->white_sockets.at(i) > 0)
		{ description_text += EString::localize_it("socket_group_button_color_white") + std::to_string(master_block->white_sockets.at(i)) + "\\n";}

		if (master_block->abyss_sockets.at(i) > 0)
		{ description_text += EString::localize_it("socket_group_button_color_abyssal") + std::to_string(master_block->abyss_sockets.at(i)) + "\\n";}

		if (master_block->delve_sockets.at(i) > 0)
		{ description_text += EString::localize_it("socket_group_button_color_delve") + std::to_string(master_block->delve_sockets.at(i)) + "\\n\\n";}
	}
	//std::cout << "!" << std::endl;
	int xx = 2;
	//_batch->draw_rect_with_uv(master_position_x, master_position_y,button_size_x);
	EFont::active_font->align_x = Enums::PositionMode::LEFT;

	for (int i = 0; i < master_block->red_sockets.size(); i++)
	if
	(
		(master_block->socket_group_links.at(i) > 0)
		||
		(master_block->red_sockets.at(i) > 0)
		||
		(master_block->green_sockets.at(i) > 0)
		||
		(master_block->blue_sockets.at(i) > 0)
		||
		(master_block->white_sockets.at(i) > 0)
		||
		(master_block->abyss_sockets.at(i) > 0)
		||
		(master_block->delve_sockets.at(i) > 0)
	)
	{
		if (xx + 15 < button_size_x)
		{
			_batch->setcolor(EColorCollection::WHITE);
			EFont::active_font->draw(_batch, "[", master_position_x + xx, master_position_y + 2);
			xx += 10;
		}

		if ((master_block->socket_group_links.at(i) > 0) && (xx + 15 < button_size_x))
		{
			_batch->setcolor(EColorCollection::WHITE);
			EFont::active_font->draw(_batch, "L:" + std::to_string(master_block->socket_group_links.at(i)), master_position_x + xx, master_position_y + 2);

			xx += 30;
		}

		if ((master_block->red_sockets.at(i) > 0) && (xx + 15 < button_size_x))
		{
			_batch->setcolor(EColorCollection::RED);
			EFont::active_font->draw(_batch, std::to_string(master_block->red_sockets.at(i)), master_position_x + xx, master_position_y + 2);

			xx += 15;
		}

		if ((master_block->green_sockets.at(i) > 0) && (xx + 15 < button_size_x))
		{
			_batch->setcolor(EColorCollection::GREEN);
			EFont::active_font->draw(_batch, std::to_string(master_block->green_sockets.at(i)), master_position_x + xx, master_position_y + 2);

			xx += 15;
		}

		if ((master_block->blue_sockets.at(i) > 0) && (xx + 15 < button_size_x))
		{
			_batch->setcolor(EColorCollection::CYAN);
			EFont::active_font->draw(_batch, std::to_string(master_block->blue_sockets.at(i)), master_position_x + xx, master_position_y + 2);

			xx += 15;
		}

		if ((master_block->white_sockets.at(i) > 0) && (xx + 15 < button_size_x))
		{
			_batch->setcolor(EColorCollection::WHITE);
			EFont::active_font->draw(_batch, std::to_string(master_block->white_sockets.at(i)), master_position_x + xx, master_position_y + 2);

			xx += 15;
		}

		if ((master_block->abyss_sockets.at(i) > 0) && (xx + 15 < button_size_x))
		{
			_batch->setcolor(EColorCollection::DARK_GRAY);
			EFont::active_font->draw(_batch, std::to_string(master_block->abyss_sockets.at(i)), master_position_x + xx, master_position_y + 2);

			xx += 15;
		}

		if ((master_block->delve_sockets.at(i) > 0)&&(xx + 15 < button_size_x))
		{
			_batch->setcolor(EColorCollection::YELLOW);
			EFont::active_font->draw(_batch, std::to_string(master_block->delve_sockets.at(i)), master_position_x + xx, master_position_y + 2);

			xx += 15;
		}

		if (xx + 15 < button_size_x)
		{
			_batch->setcolor(EColorCollection::WHITE);
			EFont::active_font->draw(_batch, "]", master_position_x + xx, master_position_y + 2);
			xx += 15;
		}



		xx += 5;

		if (xx + 15 >= button_size_x)
		{
			_batch->setcolor(EColorCollection::WHITE);
			EFont::active_font->draw(_batch, "+", master_position_x + xx - 10, master_position_y + 2);

			break;
		}
	}
}

void EButtonSocketGroup::update_localisation()
{
}
