#include "EWindow.h"
#include "EControl.h"
#include "Enums.h"
#include "EButtonAddNewBaseData.h"
#include "StaticData.h"

class EWindowAddNewBaseData : public EWindow
{
public:
	//std::vector<FilterBlock*> filter_block_list;


	EWindowAddNewBaseData(int _id) :EWindow(_id)
	{
		pos_x = 0;
		pos_y = 0;

		window_size_x = 300;
		window_size_y = 100;

		align_x = Enums::PositionMode::MID;
		align_y = Enums::PositionMode::MID;

		have_bg = true;

		is_active = false;



	}



	virtual void update(float _d)
	{
		float pos_y=-25;
		for (EButton* b : button_list)
		{
			if (b->master_block->base_filter_separator.at(b->data_id))
			{
				pos_y -= 10;
			}

			b->button_y = pos_y;
			

			pos_y -= 23;

		}
	}



	virtual void button_event(EButton* _b)
	{
		window_size_y = 100;
		is_active = true;
		button_list.clear();
		int data_id = 0;

		for (bool b: _b->master_block->base_filter_data_active)
		{
			if (!b)
			{
				EButtonAddNewBaseData* but = new EButtonAddNewBaseData(0, 0, 200, 17);
				but->master_window = this;
				but->text = _b->master_block->base_filter_data_name.at(data_id);
				but->data_id = data_id;
				but->button_x = 0;

				but->master_window = this;
				but->master_block = _b->master_block;


				button_list.push_back(but);

				window_size_y += 23;
			}

			data_id++;
		}
	}

};