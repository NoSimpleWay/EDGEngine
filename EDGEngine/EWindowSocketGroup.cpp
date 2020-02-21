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

	std::vector <EButton*> link_to_sockets_link_or_count;

	Enums::WindowSocketsColorMode window_mode = Enums::WindowSocketsColorMode::WINDOW_MODE_SOCKET_GROUP;

	std::vector<EButton*> text_button;
	void add_button(float _x, float _y, Enums::ButtonType _t, int _id)
	{
		EButton* but = new EButtonChange(_x, _y, 16, 16, _t, false);
		but->master_window = this;
		button_list.push_back(but);
		but->data_id = _id;
		//if (_t == Enums::ButtonType::BUTTON_SOCKET_LINKED) { link_to_sockets_link_or_count.push_back(but); }

		but = new EButtonChange(_x + 40, _y, 16, 16, _t, true);
		but->master_window = this;
		button_list.push_back(but);
		but->data_id = _id;
		//if (_t == Enums::ButtonType::BUTTON_SOCKET_LINKED) { link_to_sockets_link_or_count.push_back(but); }
	}

	void change_button_type()
	{
		if (window_mode == Enums::WindowSocketsColorMode::WINDOW_MODE_SOCKET_GROUP)
		for (int i = 0; i < 5; i++)
		{
			button_list.at(i * 14 + 0)->button_type = Enums::ButtonType::BUTTON_SOCKET_LINKED;//left
			button_list.at(i * 14 + 1)->button_type = Enums::ButtonType::BUTTON_SOCKET_LINKED;//right

			button_list.at(i * 14 + 2)->button_type = Enums::ButtonType::BUTTON_SOCKET_GROUP_RED;//left
			button_list.at(i * 14 + 3)->button_type = Enums::ButtonType::BUTTON_SOCKET_GROUP_RED;//right

			button_list.at(i * 14 + 4)->button_type = Enums::ButtonType::BUTTON_SOCKET_GROUP_GREEN;//left
			button_list.at(i * 14 + 5)->button_type = Enums::ButtonType::BUTTON_SOCKET_GROUP_GREEN;//right

			button_list.at(i * 14 + 6)->button_type = Enums::ButtonType::BUTTON_SOCKET_GROUP_BLUE;//left
			button_list.at(i * 14 + 7)->button_type = Enums::ButtonType::BUTTON_SOCKET_GROUP_BLUE;//right

			button_list.at(i * 14 + 8)->button_type = Enums::ButtonType::BUTTON_SOCKET_GROUP_WHITE;//left
			button_list.at(i * 14 + 9)->button_type = Enums::ButtonType::BUTTON_SOCKET_GROUP_WHITE;//right

			button_list.at(i * 14 + 10)->button_type = Enums::ButtonType::BUTTON_SOCKET_GROUP_ABYSS;//left
			button_list.at(i * 14 + 11)->button_type = Enums::ButtonType::BUTTON_SOCKET_GROUP_ABYSS;//right

			button_list.at(i * 14 + 12)->button_type = Enums::ButtonType::BUTTON_SOCKET_GROUP_DELVE;//left
			button_list.at(i * 14 + 13)->button_type = Enums::ButtonType::BUTTON_SOCKET_GROUP_DELVE;//right
		}

		if (window_mode == Enums::WindowSocketsColorMode::WINDOW_MODE_SOCKET)
		for (int i = 0; i < 5; i++)
		{
			button_list.at(i * 14 + 0)->button_type = Enums::ButtonType::BUTTON_SOCKET_COUNT;//left
			button_list.at(i * 14 + 1)->button_type = Enums::ButtonType::BUTTON_SOCKET_COUNT;//right

			button_list.at(i * 14 + 2)->button_type = Enums::ButtonType::BUTTON_SOCKET_RED;//left
			button_list.at(i * 14 + 3)->button_type = Enums::ButtonType::BUTTON_SOCKET_RED;//right

			button_list.at(i * 14 + 4)->button_type = Enums::ButtonType::BUTTON_SOCKET_GREEN;//left
			button_list.at(i * 14 + 5)->button_type = Enums::ButtonType::BUTTON_SOCKET_GREEN;//right

			button_list.at(i * 14 + 6)->button_type = Enums::ButtonType::BUTTON_SOCKET_BLUE;//left
			button_list.at(i * 14 + 7)->button_type = Enums::ButtonType::BUTTON_SOCKET_BLUE;//right

			button_list.at(i * 14 + 8)->button_type = Enums::ButtonType::BUTTON_SOCKET_WHITE;//left
			button_list.at(i * 14 + 9)->button_type = Enums::ButtonType::BUTTON_SOCKET_WHITE;//right

			button_list.at(i * 14 + 10)->button_type = Enums::ButtonType::BUTTON_SOCKET_ABYSS;//left
			button_list.at(i * 14 + 11)->button_type = Enums::ButtonType::BUTTON_SOCKET_ABYSS;//right

			button_list.at(i * 14 + 12)->button_type = Enums::ButtonType::BUTTON_SOCKET_DELVE;//left
			button_list.at(i * 14 + 13)->button_type = Enums::ButtonType::BUTTON_SOCKET_DELVE;//right
		}
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

			add_button(10.0f + i * 100.0f, 160.0f - 21.0f * 2.0f, Enums::ButtonType::BUTTON_SOCKET_GROUP_RED, i);
			add_button(10.0f + i * 100.0f, 160.0f - 21.0f * 3.0f, Enums::ButtonType::BUTTON_SOCKET_GROUP_GREEN, i);
			add_button(10.0f + i * 100.0f, 160.0f - 21.0f * 4.0f, Enums::ButtonType::BUTTON_SOCKET_GROUP_BLUE, i);
			add_button(10.0f + i * 100.0f, 160.0f - 21.0f * 5.0f, Enums::ButtonType::BUTTON_SOCKET_GROUP_WHITE, i);
			add_button(10.0f + i * 100.0f, 160.0f - 21.0f * 6.0f, Enums::ButtonType::BUTTON_SOCKET_GROUP_ABYSS, i);
			add_button(10.0f + i * 100.0f, 160.0f - 21.0f * 7.0f, Enums::ButtonType::BUTTON_SOCKET_GROUP_DELVE, i);
		}

		
		//EButton* but_link = new but(20,250,16,16, Enums::ButtonType::BUTTON_SOCKET_RED, false);

	}



	virtual void update(float _d)
	{

	}



	void draw(Batcher* _batch, float _delta)
	{

		if (window_mode == Enums::WindowSocketsColorMode::WINDOW_MODE_SOCKET_GROUP)
		for (int i = 0; i < block->red_sockets_group.size(); i++)
		{
			_batch->setcolor(EColorCollection::WHITE);
			EFont::active_font->draw(_batch, std::to_string(block->socket_group_links.at(i)), pos_x + 10.0f + 23.0f + i * 100.0f, pos_y + 163.0f - 21.0f * 0.0f);



			_batch->setcolor(EColorCollection::RED);
			EFont::active_font->draw(_batch, std::to_string(block->red_sockets_group.at(i)), pos_x + 10.0f + 23.0f + i * 100.0f, pos_y + 163.0f - 21.0f * 2.0f);

			_batch->setcolor(EColorCollection::GREEN);
			EFont::active_font->draw(_batch, std::to_string(block->green_sockets_group.at(i)), pos_x + 10.0f + 23.0f + i * 100.0f, pos_y + 163.0f - 21.0f * 3.0f);

			_batch->setcolor(EColorCollection::CYAN);
			EFont::active_font->draw(_batch, std::to_string(block->blue_sockets_group.at(i)), pos_x + 10.0f + 23.0f + i * 100.0f, pos_y + 163.0f - 21.0f * 4.0f);

			_batch->setcolor(EColorCollection::WHITE);
			EFont::active_font->draw(_batch, std::to_string(block->white_sockets_group.at(i)), pos_x + 10.0f + 23.0f + i * 100.0f, pos_y + 163.0f - 21.0f * 5.0f);

			_batch->setcolor(EColorCollection::DARK_GRAY);
			EFont::active_font->draw(_batch, std::to_string(block->abyss_sockets_group.at(i)), pos_x + 10.0f + 23.0f + i * 100.0f, pos_y + 163.0f - 21.0f * 6.0f);

			_batch->setcolor(EColorCollection::YELLOW);
			EFont::active_font->draw(_batch, std::to_string(block->delve_sockets_group.at(i)), pos_x + 10.0f + 23.0f + i * 100.0f, pos_y + 163.0f - 21.0f * 7.0f);
		}

		if (window_mode == Enums::WindowSocketsColorMode::WINDOW_MODE_SOCKET)
			for (int i = 0; i < block->socket_count.size(); i++)
			{
				_batch->setcolor(EColorCollection::WHITE);
				EFont::active_font->draw(_batch, std::to_string(block->socket_count.at(i)), pos_x + 10.0f + 23.0f + i * 100.0f, pos_y + 163.0f - 21.0f * 0.0f);



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
		relative_x = EControl::mouse_x + 32.0f;
		relative_y = EControl::mouse_y-window_size_y -32.0f;

		for (EButton* b : button_list)
		{
			b->master_block = _b->master_block;
		}

		/*
		for (EButton* b : link_to_sockets_link_or_count)
		{
			if (window_mode == Enums::WindowSocketsColorMode::SOCKET_GROUP)
			{b->button_type = Enums::BUTTON_SOCKET_LINKED;}

			if (window_mode == Enums::WindowSocketsColorMode::SOCKET)
			{b->button_type = Enums::BUTTON_SOCKET_COUNT;}
		}*/

		block = _b->master_block;

		change_button_type();
		update_localisation();
	}

	virtual void update_localisation()
	{
		for (EButton* b : button_list)
		{
			b->update_localisation();
		}
	}

};