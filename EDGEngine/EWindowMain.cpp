#include "EWindow.h"
#include "EControl.h"
#include "Enums.h"

class EWindowMain : public EWindow
{
public:
	EWindowMain(int _id, bool _can_be_closed) :EWindow(_id, _can_be_closed)
	{
		EButton*	but = new EButtonService(5, -5, 30, 30, Enums::ButtonType::BUTTON_NEW_LOOT_FILTER_WINDOW);
		but->master_window = this;
		button_list.push_back(but);

					but = new EButtonService(55,-5,30,30,Enums::ButtonType::BUTTON_OPEN_LOOT_FILTER);
		but->master_window = this;
		button_list.push_back(but);

					but = new EButtonService(95, -5, 30, 30, Enums::ButtonType::BUTTON_SAVE_LOOT_FILTER);
		but->master_window = this;
		button_list.push_back(but);

		align_x = Enums::PositionMode::LEFT;
		align_y = Enums::PositionMode::UP;

		bg_color->set(0.8f, 0.9f, 1.0f, 0.8f);

		but = new EButtonSlider(-5, -5, 250, 20, Enums::ButtonType::BUTTON_GLOBAL_DROP_SOUND_VOLUME);
		but->master_window = this;

		button_list.push_back(but);
	}

	virtual void update(float _d)
	{
		window_size_x = EWindow::SCR_WIDTH;
		window_size_y = 40;
	}

	virtual void draw(Batcher* _batch, float _delta)
	{
		_batch->setcolor_alpha(EColorCollection::BLACK, 0.8f);
		EFont::font_arial->set_align_once(Enums::PositionMode::RIGHT);

		EFont::font_arial->draw(_batch, "Громкость звуков", window_size_x - 270, pos_y + window_size_y - 22.0f);
	}
};