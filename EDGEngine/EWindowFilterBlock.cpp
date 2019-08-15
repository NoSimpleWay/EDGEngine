#include "EWindow.h"
#include "EWindowFilterBlock.h"
#include "EControl.h"
#include "Enums.h"
#include "StaticData.h"
#include "EButtonSlider.h"





	EWindowFilterBlock::EWindowFilterBlock(int _id, bool _can_be_closed) :EWindow(_id, _can_be_closed)
	{
		pos_x = 0;
		pos_y = 0;

		window_size_x = EWindow::SCR_WIDTH;
		window_size_y = EWindow::SCR_HEIGHT;

		align_x = Enums::PositionMode::LEFT;
		align_y = Enums::PositionMode::DOWN;

		have_bg = false;
		have_shadow = false;

		can_be_closed = false;

		EButton* but = new EButtonSlider(-7, -40, 20, EWindow::SCR_HEIGHT - 80.0f, Enums::ButtonType::BUTTON_FILTER_BLOCK_SCROLL);
		//but->master_block = this;
		but->master_window = this;
		button_list.push_back(but);
		link_to_slider = but;

	}

	int EWindowFilterBlock::get_id_of_filter_block(FilterBlock* _fb)
	{
		for (int i = 0; i < filter_block_list.size(); i++)
		{
			if (filter_block_list.at(i) == _fb)
			{
				return i;
			}
		}

		return 0;
	}
	
	void EWindowFilterBlock::draw(Batcher* _batch, float _delta)
	{
		window_size_x = EWindow::SCR_WIDTH;
		window_size_y = EWindow::SCR_HEIGHT;

		//std::cout << "<>" << std::endl;
		int block_index = 0;

		float yy = 60;
		int blocks_count = 0;
		int blocks_order = 0;

		int additional_scroll = 0;

		for (int i = 0; i < filter_block_list.size(); i++)
		{
			if (filter_block_list.at(i)->need_remove)
			{
				filter_block_list.erase(filter_block_list.begin() + i);

				i--;

				if (filter_block_list.size() <= 0)
				{
					filter_block_list.push_back(new FilterBlock());
				}
			}
		}

		for (int i = 0; i < filter_block_list.size(); i++)
		{
			block_index = i;
		



			if
			(
				(i < filter_block_list.size())
				&&
				(!filter_block_list.at(block_index)->is_deactivated)
				&&
				(blocks_order >= EControl::block_scroll)
				&&
				(blocks_count<8)
			)
			{
					blocks_count++;

					filter_block_list.at(block_index)->x = 5;
					filter_block_list.at(block_index)->y = EWindow::SCR_HEIGHT - filter_block_list.at(block_index)->size_y - yy;

					filter_block_list.at(block_index)->size_x = SCR_WIDTH - 40;

					yy += filter_block_list.at(block_index)->size_y + 15;

					filter_block_list.at(block_index)->update(_delta);
					filter_block_list.at(block_index)->draw(_batch);
			}

			if
			(
				(i < filter_block_list.size())
				&&
				(!filter_block_list.at(block_index)->is_deactivated)
			)
			{blocks_order++;}

		}


	}

	void EWindowFilterBlock::text_pass(Batcher* _batch)
	{
		int block_index = 0;

		float yy = 60;
		int blocks_count = 0;
		int blocks_order = 0;

		int additional_scroll = 0;

		for (int i = 0; i < filter_block_list.size(); i++)
		{
			block_index = i;




			if
				(
				(i < filter_block_list.size())
					&&
					(!filter_block_list.at(block_index)->is_deactivated)
					&&
					(blocks_order >= EControl::block_scroll)
					&&
					(blocks_count < 8)
					)
			{
				blocks_count++;

				filter_block_list.at(block_index)->text_pass(_batch);
			}

			if
				(
					(i < filter_block_list.size())
					&&
					(!filter_block_list.at(block_index)->is_deactivated)
					)
			{
				blocks_order++;
			}

		}
	}

	void EWindowFilterBlock::update_localisation()
	{
		//std::cout << "try update localisation in window. blocks count: " << filter_block_list.size() << std::endl;
		for (FilterBlock* fb: filter_block_list)
		{
			//std::cout << "buttons count: " << fb->button_list.size() << std::endl;
			fb->update_localisation();

			for (EButton* b : fb->button_list)
			{
				//std::cout << "button: " << b->text << std::endl;
				b->update_localisation();
			}
		}
	}

