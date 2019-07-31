#pragma once
#include "EButtonItemSearch.h"
#include "StaticData.h"


EButtonItemSearch::EButtonItemSearch(float _x, float _y, float _sx, float _sy, Enums::ButtonType _type) : EButton(_x, _y, _sx, _sy)
{
	is_active = false;
	have_icon = true;
	have_text = false;
	have_description = true;

	position_mode_x = Enums::PositionMode::LEFT;
	position_mode_y = Enums::PositionMode::UP;

	master_position = Enums::PositionMaster::WINDOW;

	description_text = "none";

	have_rama = true;

	rama_color->set(0.2f, 0.15f, 0.05f, 0.6f);
	bg_color->set(0.2f, 0.15f, 0.05f, 0.2f);

	button_type = _type;
}

void EButtonItemSearch::click_event()
{
	if (button_type == Enums::ButtonType::BUTTON_SEARCH_ITEM)
	{
		StaticData::window_find_item->is_active = false;
		StaticData::window_find_item->target_button->description_text = description_text;
		StaticData::window_find_item->target_button->gabarite = gabarite;

		//StaticData::window_find_item->input_button->text = "";
	}

	if (button_type == Enums::ButtonType::BUTTON_SEARCH_DEFAULT_SOUND)
	{

		StaticData::window_find_item->is_active = false;

		if (data_id >= 1)
		{
			StaticData::window_find_item->master_block->alert_sound_id = Enums::DefaultAlertSound(data_id);
			StaticData::window_find_item->master_block->alert_sound_name = text;
			StaticData::window_find_item->master_block->is_alert_sound = true;

			master_block->sound_button_link->activate();
		}
		else
		{
			if ((!master_block->is_alert_sound)&&(!master_block->is_custom_alert_sound))
			{
				master_block->sound_button_link->deactivate();
			}

			master_block->is_alert_sound = false;

			master_block->alert_sound_id = Enums::DefaultAlertSound(0);
			master_block->alert_sound_name = "";
		}
	}

	if (button_type == Enums::ButtonType::BUTTON_SEARCH_BASE_CLASS)
	{
		StaticData::window_find_item->target_button->text = text;

		StaticData::window_find_item->is_active = false;
	}

	if (button_type == Enums::ButtonType::BUTTON_SEARCH_PROPHECY)
	{
		StaticData::window_find_item->target_button->text = text;
		StaticData::window_find_item->target_button->button_size_x = EFont::get_width(EFont::font_arial, text ) + 7.0f;

		StaticData::window_find_item->is_active = false;
	}

	if (button_type == Enums::ButtonType::BUTTON_SEARCH_CUSTOM_SOUND)
	{

		StaticData::window_find_item->is_active = false;

		if (data_id >= 1)
		{
			StaticData::window_find_item->master_block->custom_alert_sound_name = text;
			StaticData::window_find_item->master_block->is_custom_alert_sound = true;

			master_block->sound_button_link->activate();
		}
		else
		{
			if ((!master_block->is_alert_sound)&&(!master_block->is_custom_alert_sound))
			{
				master_block->sound_button_link->deactivate();
			}

			master_block->is_custom_alert_sound = false;

			master_block->custom_alert_sound_name = "";
		}
	}
	//StaticData::window_find_item->fill_search_array();

}

void EButtonItemSearch::right_click_event()
{
	if (button_type == Enums::ButtonType::BUTTON_SEARCH_DEFAULT_SOUND)
	{
		if
		(
			(data_id >= 1)
			&&
			(data_id < ESound::default_drop_sound_name.size())
		)
		{
			ESound::engine->play2D(ESound::default_drop_sound.at(data_id));
		}
	}

	if (button_type == Enums::ButtonType::BUTTON_SEARCH_CUSTOM_SOUND)
	{
		if
		(
			(data_id >= 1)
			&&
			(data_id < ESound::custom_drop_sound_name.size())
		)
		{
			ESound::engine->play2D(ESound::custom_drop_sound.at(data_id));
		}
	}
}

	/*void EButton::click_event()
	{
		std::cout << "STANDART click event" << std::endl;
	}
	*/
	/*void EButton::click_event()
	{
		//std::cout << " ### pressed ### " << std::endl;

//		StaticData::window_find_item->is_active=false;
	}*/



