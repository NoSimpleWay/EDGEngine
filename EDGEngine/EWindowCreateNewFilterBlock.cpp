#include "EWindowCreateNewLootFilter.h"
#include "EButtonText.h"

EWindowCreateNewLootFilter::EWindowCreateNewLootFilter(int _id, bool _can_be_closed) :EWindow(_id, _can_be_closed)
{
	window_size_x = 500;
	window_size_y = 100;

	EButton* but = new EButtonText(0, 0, 150.0f, 25.0f, Enums::BUTTON_NEW_LOOT_FILTER);
	but->master_window = this;

	is_active = false;
}

void EWindowCreateNewLootFilter::update(float _d)
{
}

void EWindowCreateNewLootFilter::input_event(EButton* _b)
{
}

void EWindowCreateNewLootFilter::draw(Batcher* _batch, float _delta)
{
}
