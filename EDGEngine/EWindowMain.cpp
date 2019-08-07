#include "EWindow.h"
#include "EControl.h"
#include "Enums.h"

class EWindowMain : public EWindow
{
public:
	EWindowMain(int _id, bool _can_be_closed) :EWindow(_id, _can_be_closed)
	{
		EButton* but = new EButtonService(5,-5,30,30,Enums::ButtonType::BUTTON_OPEN_LOOT_FILTER);
		but->master_window = this;

		button_list.push_back(but);


		but = new EButtonService(45, -5, 30, 30, Enums::ButtonType::BUTTON_SAVE_LOOT_FILTER);
		but->master_window = this;

		button_list.push_back(but);

		align_x = Enums::PositionMode::LEFT;
		align_y = Enums::PositionMode::UP;

		bg_color->set(0.8f, 0.9f, 1.0f, 0.8f);

	}

	virtual void update(float _d)
	{
		window_size_x = EWindow::SCR_WIDTH;
		window_size_y = 40;
	}


};