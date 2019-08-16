#include "EWindow.h"
#include "EControl.h"
#include "Enums.h"
#include "EButtonService.h"

class EWindowSelectLocalisation : public EWindow
{
public:
	EWindowSelectLocalisation(int _id, bool _can_be_closed) :EWindow(_id, _can_be_closed)
	{

		align_x = Enums::PositionMode::MID;
		align_y = Enums::PositionMode::MID;

		bg_color->set(0.8f, 0.9f, 1.0f, 0.8f);

		window_size_x = 700;
		window_size_y = 400;

		EButton* but = new EButtonService(-373.0f, 0.0f, 333.0f, 333.0f, Enums::ButtonType::BUTTON_LOCALISATION_EN);
		but->master_window = this;
		but->master_position = Enums::PositionMaster::WINDOW;
		button_list.push_back(but);

		but = new EButtonService(-20.0f, 0.0f, 333.0f, 333.0f, Enums::ButtonType::BUTTON_LOCALISATION_RU);
		but->master_window = this;
		but->master_position = Enums::PositionMaster::WINDOW;
		button_list.push_back(but);

		is_active = true;

		
	}

	virtual void update(float _d)
	{
	}

	virtual void draw(Batcher* _batch, float _delta)
	{

	}

	virtual void update_localisation()
	{
		for (EButton* b : button_list)
		{
			b->update_localisation();
		}
	}
};