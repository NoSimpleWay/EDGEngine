#include "EWindow.h"
#include "EControl.h"
#include "EButtonClose.h"

EWindow::EWindow(int _id)
{
	id = _id;

	if (can_be_closed)
	{
		EButton* but = new EButtonClose(0, 0, 24, 24);
		but->master_window = this;
		default_button_list.push_back(but);
	}
	//button_list.push_back
}

EWindow::~EWindow()
{
}

bool EWindow::is_overlap()
{
	if (
			(EControl::mouse_x>=pos_x)
			&&
			(EControl::mouse_x <= pos_x+window_size_x)
			&&
			(EControl::mouse_y >= pos_y)
			&&
			(EControl::mouse_y <= pos_y + window_size_y)
		)
		{
			return true;
		}

	return false;
}

void EWindow::update(float _d)
{
}

void EWindow::default_update(float _d)
{
	if (align_x == Enums::PositionMode::MID) { pos_x = relative_x + (EWindow::SCR_WIDTH - window_size_x) / 2.0f; }
	if (align_x == Enums::PositionMode::LEFT) { pos_x = relative_x; }

	if (align_y == Enums::PositionMode::MID) { pos_y = relative_y + (EWindow::SCR_HEIGHT - window_size_y) / 2.0f; }
	if (align_y == Enums::PositionMode::DOWN) { pos_y = relative_y; }

	for (EButton* b : button_list)
	{
		b->update(_d);
	}

	for (EButton* b : default_button_list)
	{
		b->update(_d);
	}
}

void EWindow::defaul_draw(Batcher* _batch)
{
	_batch->setcolor(0.05f, 0.1f, 0.15f, 0.085f);
	if (have_shadow)
	{
		for (int i = 0; i < 15; i++)
		{
			_batch->draw_rect_with_uv(pos_x - 2.0f * i, pos_y - 2.0f * i,window_size_x, window_size_y,DefaultGabarite::gabarite_white);
		}
	}

	if (have_bg)
	{
		
		//pos_y = relative_y + (EWindow::SCR_WIDTH - window_size_y) / 2.0f;

		_batch->setcolor(bg_color);
		_batch->draw_rect_with_uv(pos_x, pos_y, window_size_x, window_size_y, DefaultGabarite::gabarite_white);
	}

	for (EButton* b : button_list)
	{
		b->default_draw(_batch);
	}

	for (EButton* b : default_button_list)
	{
		b->default_draw(_batch);
	}

	if (have_rama)
	{
		_batch->setcolor(rama_color);
		_batch->draw_rama(pos_x, pos_y, window_size_x, window_size_y, 2, DefaultGabarite::gabarite_white);
	}



}

/*
bool EWindow::is_overlap()
{
	return false;
}*/

void EWindow::draw(Batcher* _batch, float _delta)
{
	//std::cout << "F" << std::endl;
}

void EWindow::default_text_pass(Batcher* _batch)
{
	for (EButton* b : button_list)
	{
		b->text_pass(_batch);
	}

	for (EButton* b : default_button_list)
	{
		b->text_pass(_batch);
	}
}

void EWindow::text_pass(Batcher* _batch)
{

}



void EWindow::button_event(EButton* _b)
{
	//std::cout << "standart window button event" << std::endl;
}

void EWindow::input_event(EButton* _b)
{
}

void EWindow::manual_event()
{

}

