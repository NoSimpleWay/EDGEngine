#include "EWindow.h"
#include "EControl.h"
#include "Enums.h"

class EWindowFilterBlock: public EWindow
{
public:
	std::vector<FilterBlock*> filter_block_list;


	EWindowFilterBlock(int _id):EWindow(_id)
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

	}

	int get_id_of_filter_block(FilterBlock* _fb)
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
	
	virtual void draw(Batcher* _batch, float _delta)
	{
		window_size_x = EWindow::SCR_WIDTH;
		window_size_y = EWindow::SCR_HEIGHT;

		//std::cout << "<>" << std::endl;
		int block_index = 0;

		float yy = 60;
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