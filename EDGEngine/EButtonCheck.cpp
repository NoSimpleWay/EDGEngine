#include "EButtonCheck.h"
#include "StaticData.h"

EButtonCheck::EButtonCheck(float _x, float _y, float _sx, float _sy, Enums::ButtonType _type): EButton(_x,_y,_sx,_sy)
{
	have_icon = true;
	gabarite = DefaultGabarite::gabarite_checked;
	have_text = false;

	master_position = Enums::PositionMaster::FILTER_BLOCK;

	description_text = "Кликни для изменения";

	button_type = _type;


}



void EButtonCheck::click_event()
{
	std::cout << "C L I C K" << std::endl;
	is_checked = !is_checked;

	if (is_checked)
	{
		gabarite = DefaultGabarite::gabarite_checked;
	}
	else
	{
		gabarite = DefaultGabarite::gabarite_unchecked;
	}

	if (button_type == Enums::ButtonType::BUTTON_CORRUPTION) { master_block->base_filter_data_bool.at(data_id) = is_checked; }

	if (button_type == Enums::ButtonType::BUTTON_SHAPER_ITEM) { master_block->base_filter_data_bool.at(data_id) = is_checked; }
	if (button_type == Enums::ButtonType::BUTTON_ELDER_ITEM) { master_block->base_filter_data_bool.at(data_id) = is_checked; }

	if (button_type == Enums::ButtonType::BUTTON_SYNTHESISED) { master_block->base_filter_data_bool.at(data_id) = is_checked; }
	if (button_type == Enums::ButtonType::BUTTON_FRACTURED) { master_block->base_filter_data_bool.at(data_id) = is_checked; }

	if (button_type == Enums::ButtonType::BUTTON_ANY_ENCHANTMENT) { master_block->base_filter_data_bool.at(data_id) = is_checked; }

	if (button_type == Enums::ButtonType::BUTTON_IDENTIFIED) { master_block->base_filter_data_bool.at(data_id) = is_checked; }

	if (button_type == Enums::ButtonType::BUTTON_SHAPER_MAP) { master_block->base_filter_data_bool.at(data_id) = is_checked; }
	if (button_type == Enums::ButtonType::BUTTON_ELDER_MAP) { master_block->base_filter_data_bool.at(data_id) = is_checked; }

	if (button_type == Enums::ButtonType::BUTTON_CHECKER_MINIMAP_ICON)
	{
		master_block->is_minimap_icon = is_checked;

		if (is_checked)
		{
			StaticData::window_filter_visual_editor->update_minimap_button();
			//master_block->is_min
		}
		else
		{
			StaticData::window_filter_visual_editor->deactivate_minimap_button();
		}
	}

	/*BUTTON_CORRUPTION,
	BUTTON_SHAPER_ITEM,
	BUTTON_ELDER_ITEM,
	BUTTON_SYNTHESISED,
	BUTTON_FRACTURED,
	BUTTON_ANY_ENCHANTMENT,
	BUTTON_IDENTIFIED,*/
}

void EButtonCheck::change_state(bool _b)
{
	is_checked = _b;

	if (is_checked)
	{
		gabarite = DefaultGabarite::gabarite_checked;
	}
	else
	{
		gabarite = DefaultGabarite::gabarite_unchecked;
	}
}

void EButtonCheck::incoming_data(FilterBlock* _filter)
{
	change_state(_filter->base_filter_data_bool.at(data_id));
}
