#include "EButtonText.h"
#include "StaticData.h"



EButtonText::EButtonText(float _x, float _y, float _sx, float _sy, Enums::ButtonType _type):EButton(_x,_y,_sx,_sy)
{
	have_text = true;
	have_rama = true;
	have_icon = false;

	rama_thikness = 2;
	rama_color->set(.2f, .3f, .4f, .5f);

	button_type = _type;

	if (button_type == Enums::ButtonType::BUTTON_OPEN_DEFAULT_DROP_SOUND_WINDOW)
	{
		text_align_x = Enums::PositionMode::MID;
		text = "Select default drop sound";

		master_position = Enums::PositionMaster::WINDOW;
	}

	if (button_type == Enums::ButtonType::BUTTON_OPEN_CUSTOM_DROP_SOUND_WINDOW)
	{
		position_mode_y = Enums::PositionMode::UP;
		text = "Select custom drop sound";

		master_position = Enums::PositionMaster::WINDOW;
	}

	if (button_type == Enums::ButtonType::BUTTON_ADD_EXPLICIT_GROUP)
	{
		text_align_x = Enums::PositionMode::MID;
		position_mode_x = Enums::PositionMode::MID;
		position_mode_y = Enums::PositionMode::UP;

		text = "Add explicit group list";

		master_position = Enums::PositionMaster::WINDOW;


	}

	if (button_type == Enums::ButtonType::BUTTON_ADD_EXPLICIT_ELEMENT)
	{
		text_align_x = Enums::PositionMode::MID;
		position_mode_x = Enums::PositionMode::LEFT;
		position_mode_y = Enums::PositionMode::UP;

		text = "Add explicit group list";

		master_position = Enums::PositionMaster::WINDOW;
	}
}

void EButtonText::click_event()
{
	if (button_type == Enums::ButtonType::BUTTON_OPEN_DEFAULT_DROP_SOUND_WINDOW)
	{
		StaticData::window_find_item->is_active = true;
		StaticData::window_find_item->window_searchs_mode = Enums::WindowSearchMode::DEFAULT_DROP_SOUND;

		StaticData::window_find_item->button_event(this);

	}

	if (button_type == Enums::ButtonType::BUTTON_OPEN_CUSTOM_DROP_SOUND_WINDOW)
	{
		StaticData::window_find_item->is_active = true;
		StaticData::window_find_item->window_searchs_mode = Enums::WindowSearchMode::CUSTOM_DROP_SOUND;

		StaticData::window_find_item->button_event(this);
	}

	if (button_type == Enums::ButtonType::BUTTON_ADD_EXPLICIT_GROUP)
	{
		master_block->explicit_list.at(data_id)->is_active = true;
		master_block->explicit_list.at(data_id)->button_close->is_active = true;
		master_block->explicit_list.at(data_id)->button_add->is_active = true;

		StaticData::window_add_new_base_data->is_active = false;
	}

	if (button_type == Enums::ButtonType::BUTTON_ADD_EXPLICIT_ELEMENT)
	{

	}
}
