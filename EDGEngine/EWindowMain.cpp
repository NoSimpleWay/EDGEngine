#include "EWindow.h"
#include "EControl.h"
#include "Enums.h"
#include "EButtonService.h"
#include "EButtonSlider.h"

class EWindowMain : public EWindow
{
public:
	std::string cached_text_sound_volume;

	std::vector <EButton*> tab_list;

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




					but = new EButtonService(145, -5, 30, 30, Enums::ButtonType::BUTTON_OPEN_SIMULATOR);
		but->master_window = this;
		button_list.push_back(but);

					but = new EButtonService(185, -5, 30, 30, Enums::ButtonType::BUTTON_OPEN_OIL_WINDOW);
		but->master_window = this;
		button_list.push_back(but);
		
					but = new EButtonService(235, -5, 30, 30, Enums::ButtonType::BUTTON_CONFIGUE_FONT);
		but->master_window = this;
		button_list.push_back(but);
		
					but = new EButtonService(275, -5, 30, 30, Enums::ButtonType::BUTTON_CONFIGUE_LANGUAGE);
		but->master_window = this;
		button_list.push_back(but);

		for (int i = 0; i < 5; i++)
		{
			but = new EButtonText(5.0f + 60.0f * i, -45.0f, 30.0f, 20.0f, Enums::BUTTON_FILTER_BLOCK_TAB);

			but->master_window = this;
			but->data_id = i;
			but->text = "Empty tab #" + std::to_string(i + 1);

			button_list.push_back(but);
			tab_list.push_back(but);
		} 

		align_x = Enums::PositionMode::LEFT;
		align_y = Enums::PositionMode::UP;

		bg_color->set(0.8f, 0.9f, 1.0f, 0.8f);

		but = new EButtonSlider(-5.0f, -5.0f, 250.0f, 20.0f, Enums::ButtonType::BUTTON_GLOBAL_DROP_SOUND_VOLUME);
		but->master_window = this;

		button_list.push_back(but);

		have_bg = false;
		have_rama = false;
	}

	virtual void update(float _d)
	{
		window_size_x = EWindow::SCR_WIDTH;
		window_size_y = 70.0f;

		float xx = 5;
		for (EButton* b:tab_list)
		{
			b->button_x = xx;

			xx += b->button_size_x + 5.0f;
		}
	}

	virtual void draw(Batcher* _batch, float _delta)
	{

		_batch->setcolor_alpha(EColorCollection::WHITE, 0.8f);
		EFont::active_font->set_align_once(Enums::PositionMode::RIGHT);

		EFont::active_font->draw(_batch, cached_text_sound_volume, window_size_x - 270, pos_y + window_size_y - 22.0f);
	}

	virtual void pre_draw(Batcher* _batch, float _delta)
	{
		_batch->setcolor(EColorCollection::WHITE);
		_batch->draw_rect_with_uv(pos_x, pos_y - 35.0f, 1920.0f, 105.0f, DefaultGabarite::gabarite_cap_rama);
	}

	virtual void update_localisation()
	{
		for (EButton* b : button_list)
		{b->update_localisation();}

		cached_text_sound_volume = EString::localize_it("text_sound_volume");
	}
};