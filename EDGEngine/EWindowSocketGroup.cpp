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

	std::vector<EButton*> text_button;
	void add_button(float _x, float _y, Enums::ButtonType _t)
	{
		EButton* but = new EButtonChange(_x, _y, 16, 16, _t, false);
		but->master_window = this;
		button_list.push_back(but);

		but = new EButtonChange(_x + 40, _y, 16, 16, _t, true);
		but->master_window = this;
		button_list.push_back(but);

	}


	EWindowSocketGroup(int _id, bool _can_be_closed) :EWindow(_id, _can_be_closed)
	{


		window_size_x = 75;
		window_size_y = 125;

		align_x = Enums::PositionMode::LEFT;
		align_y = Enums::PositionMode::DOWN;

		have_bg = true;
		bg_color->set(0.2f, 0.25f, 0.3f, 0.95f);

		is_active = false;

		add_button(10.0f, 75.0f-21.0f*0.0f, Enums::ButtonType::BUTTON_SOCKET_RED);
		add_button(10.0f, 75.0f-21.0f*1.0f, Enums::ButtonType::BUTTON_SOCKET_GREEN);
		add_button(10.0f, 75.0f-21.0f*2.0f, Enums::ButtonType::BUTTON_SOCKET_BLUE);
		add_button(10.0f, 75.0f-21.0f*3.0f, Enums::ButtonType::BUTTON_SOCKET_WHITE);

		
		//EButton* but_link = new but(20,250,16,16, Enums::ButtonType::BUTTON_SOCKET_RED, false);

	}



	virtual void update(float _d)
	{

	}



	void draw(Batcher* _batch, float _delta)
	{
		_batch->setcolor(EColorCollection::RED);
		EFont::font_arial->draw(_batch, std::to_string(block->red_sockets), pos_x+10.0f + 25.0f, pos_y + 75.0f - 21.0f * 0.0f);

		_batch->setcolor(EColorCollection::GREEN);
		EFont::font_arial->draw(_batch, std::to_string(block->green_sockets), pos_x + 10.0f + 25.0f, pos_y + 75.0f - 21.0f * 1.0f);

		_batch->setcolor(EColorCollection::CYAN);
		EFont::font_arial->draw(_batch, std::to_string(block->blue_sockets), pos_x + 10.0f + 25.0f, pos_y + 75.0f - 21.0f * 2.0f);

		_batch->setcolor(EColorCollection::WHITE);
		EFont::font_arial->draw(_batch, std::to_string(block->white_sockets), pos_x + 10.0f + 25.0f, pos_y + 75.0f - 21.0f * 3.0f);
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