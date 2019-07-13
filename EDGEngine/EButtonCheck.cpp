#include "EButtonCheck.h"

EButtonCheck::EButtonCheck(float _x, float _y, float _sx, float _sy, Enums::ButtonType _type): EButton(_x,_y,_sx,_sy)
{
	have_icon = true;
	gabarite = DefaultGabarite::gabarite_checked;
	have_text = false;

	master_position = Enums::PositionMaster::FILTER_BLOCK;

	description_text = "Click to change";


}

void EButtonCheck::click_event()
{
	is_checked = !is_checked;

	if (is_checked)
	{
		gabarite = DefaultGabarite::gabarite_checked;
	}
	else
	{
		gabarite = DefaultGabarite::gabarite_unchecked;
	}
	if (button_type == Enums::ButtonType::BUTTON_CORRUPTION) { master_block->base_filter_data_active.at(Enums::BaseDataOrder::DATA_CORRUPTED) = is_checked; }

	if (button_type == Enums::ButtonType::BUTTON_SHAPER_ITEM) { master_block->base_filter_data_active.at(Enums::BaseDataOrder::DATA_SHAPER_ITEM) = is_checked; }
	if (button_type == Enums::ButtonType::BUTTON_ELDER_ITEM) { master_block->base_filter_data_active.at(Enums::BaseDataOrder::DATA_ELDER_ITEM) = is_checked; }

	if (button_type == Enums::ButtonType::BUTTON_SYNTHESISED) { master_block->base_filter_data_active.at(Enums::BaseDataOrder::DATA_SYNTHESISED) = is_checked; }
	if (button_type == Enums::ButtonType::BUTTON_FRACTURED) { master_block->base_filter_data_active.at(Enums::BaseDataOrder::DATA_FRACTURED) = is_checked; }

	if (button_type == Enums::ButtonType::BUTTON_ANY_ENCHANTMENT) { master_block->base_filter_data_active.at(Enums::BaseDataOrder::DATA_ENCHANTMENT) = is_checked; }

	if (button_type == Enums::ButtonType::BUTTON_IDENTIFIED) { master_block->base_filter_data_active.at(Enums::BaseDataOrder::DATA_IDENTIFIED) = is_checked; }

	if (button_type == Enums::ButtonType::BUTTON_SHAPER_MAP) { master_block->base_filter_data_active.at(Enums::BaseDataOrder::DATA_SHAPER_MAP) = is_checked; }
	if (button_type == Enums::ButtonType::BUTTON_ELDER_MAP) { master_block->base_filter_data_active.at(Enums::BaseDataOrder::DATA_ELDER_MAP) = is_checked; }

	/*BUTTON_CORRUPTION,
	BUTTON_SHAPER_ITEM,
	BUTTON_ELDER_ITEM,
	BUTTON_SYNTHESISED,
	BUTTON_FRACTURED,
	BUTTON_ANY_ENCHANTMENT,
	BUTTON_IDENTIFIED,*/
}
