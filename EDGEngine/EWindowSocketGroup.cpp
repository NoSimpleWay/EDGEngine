#pragma once
#include "EWindow.h"
#include "EControl.h"
#include "Enums.h"
#include "EButtonChange.h"
#include "StaticData.h"
class EWindowSocketGroup : public EWindow
{
public:
	//std::vector<FilterBlock*> filter_block_list;

	void add_button(float _x, float _y, Enums::ButtonType _t)
	{
		EButtonChange* but = new EButtonChange(_x, _y, 16, 16, _t, false);
		but->master_window = this;
		button_list.push_back(but);

		but = new EButtonChange(_x + 40, _y, 16, 16, _t, true);
		but->master_window = this;
		button_list.push_back(but);
	}


	EWindowSocketGroup(int _id) :EWindow(_id)
	{


		window_size_x = 75;
		window_size_y = 105;

		align_x = Enums::PositionMode::LEFT;
		align_y = Enums::PositionMode::DOWN;

		have_bg = true;

		is_active = false;

		add_button(10.0f, 75.0f+21.0f*0.0f, Enums::ButtonType::BUTTON_SOCKET_RED);
		add_button(10.0f, 75.0f+21.0f*1.0f, Enums::ButtonType::BUTTON_SOCKET_GREEN);
		add_button(10.0f, 75.0f+21.0f*2.0f, Enums::ButtonType::BUTTON_SOCKET_BLUE);
		add_button(10.0f, 75.0f+21.0f*3.0f, Enums::ButtonType::BUTTON_SOCKET_WHITE);

		
		//EButton* but_link = new but(20,250,16,16, Enums::ButtonType::BUTTON_SOCKET_RED, false);

	}



	virtual void update(float _d)
	{

	}



	void draw(Batcher* _batch, float _delta)
	{

	}


	virtual void button_event(EButton* _b)
	{
		relative_x = EControl::mouse_x;
		relative_y = EControl::mouse_y;
	}

};