#include "EButtonText.h"
#include "EWindowCreateNewLootFilter.h"

EWindowCreateNewLootFilter::EWindowCreateNewLootFilter(int _id, bool _can_be_closed) :EWindow(_id, _can_be_closed)
{
	window_size_x = 500;
	window_size_y = 100;

	EButton* but = new EButtonText(10.0f, 0, 200.0f, 25.0f, Enums::BUTTON_NEW_LOOT_FILTER_NAME);
	but->master_window = this;
	button_list.push_back(but);
	link_to_input_button = but;

	but = new EButtonText (220.0f, 0, 50.0f, 25.0f, Enums::BUTTON_NEW_LOOT_FILTER_OK);
	but->master_window = this;
	button_list.push_back(but);
	link_to_accept_button = but;

	but->bg_color->set_alpha(EColorCollection::GRAY, 1.0f);

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

void EWindowCreateNewLootFilter::update_localisation()
{
	//std::cout << "try update localisation in window. blocks count: " << filter_block_list.size() << std::endl;

		for (EButton* b : button_list)
		{
			//std::cout << "button: " << b->text << std::endl;
			b->update_localisation();
		}
}
