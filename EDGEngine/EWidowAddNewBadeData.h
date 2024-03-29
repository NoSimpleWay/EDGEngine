#include "EWindow.h"
#include "EControl.h"
#include "Enums.h"

class EWindowAddNewBaseData : public EWindow
{



	EWindowAddNewBaseData(int _id) :EWindow(_id)
	{
		pos_x = 0;
		pos_y = 0;

		window_size_x = EWindow::SCR_WIDTH;
		window_size_y = EWindow::SCR_HEIGHT;

		align_x = Enums::PositionMode::LEFT;
		align_y = Enums::PositionMode::DOWN;

		have_bg = true;

	}



	virtual void draw(Batcher* _batch, float _delta)
	{
		window_size_x = EWindow::SCR_WIDTH;
		window_size_y = EWindow::SCR_HEIGHT;

		//std::cout << "<>" << std::endl;
		
		int block_index = 0;

		float yy = 30;
		for (int i = 0; i < 9; i++)
		{
			block_index = i + EControl::block_scroll;

			if (block_index < filter_block_list.size())
			{

				filter_block_list.at(block_index)->x = 15;
				filter_block_list.at(block_index)->y = EWindow::SCR_HEIGHT - filter_block_list.at(block_index)->size_y - yy;

				yy += filter_block_list.at(block_index)->size_y + 15;

				filter_block_list.at(block_index)->size_x = SCR_WIDTH - 30;

				filter_block_list.at(block_index)->update(_delta);
				filter_block_list.at(block_index)->draw(_batch);
			}
		}


	}

	virtual void text_pass(Batcher* _batch)
	{
		int block_index = 0;
		for (int i = 0; i < 9; i++)
		{
			block_index = i + EControl::block_scroll;

			if (block_index < filter_block_list.size())
			{
				filter_block_list.at(block_index)->text_pass(_batch);
			}
		}
	}

};