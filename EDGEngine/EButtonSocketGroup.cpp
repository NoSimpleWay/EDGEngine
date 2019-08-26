#include "EButtonSocketGroup.h"


EButtonSocketGroup::EButtonSocketGroup(float _x, float _y, float _sx, float _sy, Enums::ButtonType _type): EButton(_x, _y, _sx, _sy)
{
	have_icon = false;
	gabarite = DefaultGabarite::gabarite_checked;
	have_text = false;

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
	//std::cout << "!" << std::endl;
	int xx = 2;
	//_batch->draw_rect_with_uv(master_position_x, master_position_y,button_size_x);
	EFont::active_font->align_x = Enums::PositionMode::LEFT;

	if (master_block->red_sockets > 0)
	{
		_batch->setcolor(EColorCollection::RED);
		EFont::active_font->draw(_batch, std::to_string(master_block->red_sockets),master_position_x+xx,master_position_y+2);

		xx += 15;
	}

	if (master_block->green_sockets > 0)
	{
		_batch->setcolor(EColorCollection::GREEN);
		EFont::active_font->draw(_batch, std::to_string(master_block->green_sockets), master_position_x + xx, master_position_y+2);

		xx += 15;
	}

	if (master_block->blue_sockets > 0)
	{
		_batch->setcolor(EColorCollection::BLUE);
		EFont::active_font->draw(_batch, std::to_string(master_block->blue_sockets), master_position_x + xx, master_position_y+2);

		xx += 15;
	}

	if (master_block->white_sockets > 0)
	{
		_batch->setcolor(EColorCollection::WHITE);
		EFont::active_font->draw(_batch, std::to_string(master_block->white_sockets), master_position_x + xx, master_position_y+2);

		xx += 15;
	}
}

void EButtonSocketGroup::update_localisation()
{
}
