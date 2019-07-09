#include "EWindow.h"

EWindow::EWindow()
{
}

EWindow::~EWindow()
{
}

void EWindow::update(float _d)
{
}

void EWindow::defaul_draw(Batcher* _batch)
{
	if (have_bg)
	{
		_batch->setcolor(bg_color);
		_batch->draw_rect_with_uv((EWindow::SCR_WIDTH - size_x) / 2.0f, (EWindow::SCR_HEIGHT - size_y) / 2.0f, size_x, size_y, DefaultGabarite::gabarite_white);
	}
}

void EWindow::draw(Batcher* _batch, float _delta)
{
	std::cout << "F" << std::endl;
}



void EWindow::button_event(EButton* _b)
{
	//std::cout << "standart window button event" << std::endl;
}

void EWindow::input_event(EButton* _b)
{
}

