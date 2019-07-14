#include "EWindow.h"
#include "EControl.h"
#include "Enums.h"

class EWindowAddNewBaseData : public EWindow
{
public:



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
		


	}

	virtual void text_pass(Batcher* _batch)
	{
		
	}

	void button_event(EButton* _b)
	{
		button_list->clear();
	}
	

};