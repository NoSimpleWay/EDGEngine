#pragma once
#include "EWindow.h"
#include "EControl.h"
#include "Enums.h"
#include "EButtonChange.h"
#include "EButtonText.h"
class EWindowSocketGroup : public EWindow
{
public:
	//std::vector<FilterBlock*> filter_block_list;
	FilterBlock* block;
	int link_id = 0;

	std::vector<EButton*> text_button;
	void add_button(float _x, float _y, Enums::ButtonType _t, int _id)
	{
		EButton* but = new EButtonChange(_x, _y, 16, 16, _t, false);
		but->master_window = this;
		button_list.push_back(but);
		but->data_id = _id;

		but = new EButtonChange(_x + 40, _y, 16, 16, _t, true);
		but->master_window = this;
		button_list.push_back(but);
		but->data_id = _id;
	}


	EWindowSocketGroup(int _id, bool _can_be_closed) :EWindow(_id, _can_be_closed)
	{


		window_size_x = 500;
		window_size_y = 200;

		align_x = Enums::PositionMode::LEFT;
		align_y = Enums::PositionMode::DOWN;

		have_bg = true;
		bg_color->set(0.2f, 0.25f, 0.3f, 0.95f);

		is_active = false;

		for (int i = 0; i < 5; i++)
		{
			add_button(10.0f + i * 100.0f, 160.0f - 21.0f * 0.0f, Enums::ButtonType::BUTTON_SOCKET_LINKED, i);

			add_button(10.0f + i * 100.0f, 160.0f - 21.0f * 2.0f, Enums::ButtonType::BUTTON_SOCKET_RED, i);
			add_button(10.0f + i * 100.0f, 160.0f - 21.0f * 3.0f, Enums::ButtonType::BUTTON_SOCKET_GREEN, i);
			add_button(10.0f + i * 100.0f, 160.0f - 21.0f * 4.0f, Enums::ButtonType::BUTTON_SOCKET_BLUE, i);
			add_button(10.0f + i * 100.0f, 160.0f - 21.0f * 5.0f, Enums::ButtonType::BUTTON_SOCKET_WHITE, i);
			add_button(10.0f + i * 100.0f, 160.0f - 21.0f * 6.0f, Enums::ButtonType::BUTTON_SOCKET_ABYSS, i);
			add_button(10.0f + i * 100.0f, 160.0f - 21.0f * 7.0f, Enums::ButtonType::BUTTON_SOCKET_DELVE, i);
		}

		
		//EButton* but_link = new but(20,250,16,16, Enums::ButtonType::BUTTON_SOCKET_RED, false);

	}



	virtual void update(float _d)
	{

	}



	void draw(Batcher* _batch, float _delta)
	{
		for (int i = 0; i < block->red_sockets.size(); i++)
		{
			_batch->setcolor(EColorCollection::WHITE);
			EFont::active_font->draw(_batch, std::to_string(block->socket_group_links.at(i)), pos_x + 10.0f + 23.0f + i * 100.0f, pos_y + 163.0f - 21.0f * 0.0f);



			_batch->setcolor(EColorCollection::RED);
			EFont::active_font->draw(_batch, std::to_string(block->red_sockets.at(i)), pos_x + 10.0f + 23.0f + i * 100.0f, pos_y + 163.0f - 21.0f * 2.0f);

			_batch->setcolor(EColorCollection::GREEN);
			EFont::active_font->draw(_batch, std::to_string(block->green_sockets.at(i)), pos_x + 10.0f + 23.0f + i * 100.0f, pos_y + 163.0f - 21.0f * 3.0f);

			_batch->setcolor(EColorCollection::CYAN);
			EFont::active_font->draw(_batch, std::to_string(block->blue_sockets.at(i)), pos_x + 10.0f + 23.0f + i * 100.0f, pos_y + 163.0f - 21.0f * 4.0f);

			_batch->setcolor(EColorCollection::WHITE);
			EFont::active_font->draw(_batch, std::to_string(block->white_sockets.at(i)), pos_x + 10.0f + 23.0f + i * 100.0f, pos_y + 163.0f - 21.0f * 5.0f);

			_batch->setcolor(EColorCollection::DARK_GRAY);
			EFont::active_font->draw(_batch, std::to_string(block->abyss_sockets.at(i)), pos_x + 10.0f + 23.0f + i * 100.0f, pos_y + 163.0f - 21.0f * 6.0f);

			_batch->setcolor(EColorCollection::YELLOW);
			EFont::active_font->draw(_batch, std::to_string(block->delve_sockets.at(i)), pos_x + 10.0f + 23.0f + i * 100.0f, pos_y + 163.0f - 21.0f * 7.0f);
		}
	}


	virtual void button_event(EButton* _b)
	{
		relative_x = EControl::mouse_x;
		relative_y = EControl::mouse_y-window_size_y;

		for (EButton* b : button_list)
		{
			b->master_block = _b->master_block;
		}

		block = _b->master_block;
	}

	virtual void update_localisation()
	{
		for (EButton* b : button_list)
		{
			b->update_localisation();
		}
	}

};