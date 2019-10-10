#include "EWindowSelectLootPattern.h"
#include "EUtils.h"
#include "EButtonText.h"

EWindowSelectLootPattern::EWindowSelectLootPattern(int _id, bool _can_be_closed):EWindow(_id, _can_be_closed)
{
	window_size_x = 1000.0f;
	window_size_y = 500.0f;

	float x_position = 30.0f;
	float y_position = -30.0f;

	for (int i = 0; i < EString::loot_pattern_name.size(); i++)
	{
		EButton* but = new EButtonText(x_position, y_position, 200.0f, 25.0f, Enums::ButtonType::BUTTON_SELECT_LOOT_PATTERN);

		but->data_id = i;

		but->text = EString::loot_pattern_name.at(i);

		but->master_window = this;
		button_list.push_back(but);

		y_position -= 30.0f;

		if (pos_y - y_position + 30.0f > window_size_y)
		{
			y_position = -30.0f;
			x_position += 220.0f;
		}
	}
}

void EWindowSelectLootPattern::update(float _d)
{
}

void EWindowSelectLootPattern::draw(Batcher* _batch, float _delta)
{
	_batch->setcolor_alpha(EColorCollection::BLACK, 0.6f);

	float x_position = 30.0f;
	float y_position = -30.0f;

	for (int i = 0; i < 100; i++)

	{
		if (i >= EString::loot_pattern_name.size())
		{
			_batch->draw_simple_rect(pos_x + x_position, pos_y + window_size_y + y_position - 26.0f, 200, 25.0f);
		}

		y_position -= 30.0f;

		if (-y_position + 30.0f > window_size_y)
		{
			y_position = -30.0f;
			x_position += 220.0f;
		}

		if (x_position + 200 > window_size_x)
		{
			break;
		}
	}
}

void EWindowSelectLootPattern::update_localisation()
{
	for (EButton* b : button_list)
	{
		b->update_localisation();
	}
}

void EWindowSelectLootPattern::input_event(EButton* _b)
{
}

void EWindowSelectLootPattern::pre_draw(Batcher* _batch, float _delta)
{

}
