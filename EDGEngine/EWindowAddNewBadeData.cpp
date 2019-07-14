#include "EWindow.h"
#include "EControl.h"
#include "Enums.h"
#include "EButtonAddNewBaseData.h"
#include "StaticData.h"

class EWindowAddNewBaseData : public EWindow
{
public:
	std::vector<FilterBlock*> filter_block_list;


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







	virtual void button_event(EButton* _b)
	{
		button_list.clear();

		StaticData::

		for (bool b: _b->master_block->base_filter_data_active)
		{
			if (b)
			{
				EButtonAddNewBaseData* but = new EButtonAddNewBaseData(0, 0, 200, 17);
				but->master_window = this;


				button_list.push_back(but);
			}
		}
	}

};