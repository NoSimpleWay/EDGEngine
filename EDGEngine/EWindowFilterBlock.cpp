#include "EWindow.h"
#include "EControl.h"
class EWindowFilterBlock: public EWindow
{
public:
	std::vector<FilterBlock*> filter_block_list;

	EWindowFilterBlock():EWindow()
	{

	}

	void update()
	{

	}

	
	virtual void draw(Batcher* _batch, float _delta)
	{
		//std::cout << "<>" << std::endl;
		int block_index = 0;

		for (int i = 0; i < 9; i++)
		{
			block_index = i + EControl::block_scroll;

			if (block_index < filter_block_list.size())
			{
				filter_block_list.at(block_index)->x = 15;
				filter_block_list.at(block_index)->y = EWindow::SCR_HEIGHT - filter_block_list.at(block_index)->size_y - 15 - i * 105;

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