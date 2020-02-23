#include "EButtonCheck.h"
#include "StaticData.h"

EButtonCheck::EButtonCheck(float _x, float _y, float _sx, float _sy, Enums::ButtonType _type): EButton(_x,_y,_sx,_sy)
{
	have_icon = true;
	gabarite = DefaultGabarite::gabarite_checked;
	have_text = false;

	master_position = Enums::PositionMaster::FILTER_BLOCK;

	//description_text = "Кликни для изменения";

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

	if (button_type == Enums::ButtonType::BUTTON_MIRRORED_ITEM) { master_block->base_filter_data_bool.at(data_id) = is_checked; }

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

	if (button_type == Enums::ButtonType::BUTTON_CHECK_AUTOGEN)
	{
		master_block->autogen_include.at(data_id) = is_checked;
	}

	if (button_type == Enums::ButtonType::BUTTON_MANUAL_LOOT_ELDER_MAP)
	{
		StaticData::window_manual_loot->elder_map = is_checked;
	}

	if (button_type == Enums::ButtonType::BUTTON_MANUAL_LOOT_BLIGHT_MAP)
	{
		StaticData::window_manual_loot->blighted_map = is_checked;
	}

	if (button_type == Enums::ButtonType::BUTTON_IDENTIFIED)
	{
		StaticData::window_manual_loot->identified = is_checked;
	}

	if (button_type == Enums::ButtonType::BUTTON_MANUAL_LOOT_CORRUPTED)
	{
		StaticData::window_manual_loot->is_corrupted = is_checked;
	}

	if (button_type == Enums::ButtonType::BUTTON_MANUAL_LOOT_SHAPER_INFLUENCE)
	{StaticData::window_manual_loot->shaper_influence = is_checked;}

	if (button_type == Enums::ButtonType::BUTTON_MANUAL_LOOT_ELDER_INFLUENCE)
	{StaticData::window_manual_loot->elder_influence = is_checked;}

	if (button_type == Enums::ButtonType::BUTTON_MANUAL_LOOT_CRUSADER_INFLUENCE)
	{StaticData::window_manual_loot->crusader_influence = is_checked;}

	if (button_type == Enums::ButtonType::BUTTON_MANUAL_LOOT_REDEEMER_INFLUENCE)
	{StaticData::window_manual_loot->redeemer_influence = is_checked;}

	if (button_type == Enums::ButtonType::BUTTON_MANUAL_LOOT_HUNTER_INFLUENCE)
	{StaticData::window_manual_loot->hunter_influence = is_checked;}

	if (button_type == Enums::ButtonType::BUTTON_MANUAL_LOOT_WARLORD_INFLUENCE)
	{StaticData::window_manual_loot->warlord_influence = is_checked;}

	if (button_type == Enums::ButtonType::BUTTON_MANUAL_LOOT_FRACTURED)
	{StaticData::window_manual_loot->is_fractured = is_checked;}

	if (button_type == Enums::ButtonType::BUTTON_MANUAL_LOOT_SYNTHESISED)
	{StaticData::window_manual_loot->is_synthesised = is_checked;}

	if (button_type == Enums::ButtonType::BUTTON_MANUAL_LOOT_ENCHANTMENT)
	{StaticData::window_manual_loot->is_enchanted = is_checked;}

	if (button_type == Enums::ButtonType::BUTTON_MANUAL_LOOT_MIRRORED)
	{StaticData::window_manual_loot->is_mirrored = is_checked;}



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

void EButtonCheck::update_localisation()
{
	if (button_type == Enums::ButtonType::BUTTON_CHECK_AUTOGEN)
	{
		if (data_id == 0) { description_text = EString::localize_it("description_autogen_check_very_low"); }
		if (data_id == 1) { description_text = EString::localize_it("description_autogen_check_low"); }
		if (data_id == 2) { description_text = EString::localize_it("description_autogen_check_default"); }
		if (data_id == 3) { description_text = EString::localize_it("description_autogen_check_rich"); }
		if (data_id == 4) { description_text = EString::localize_it("description_autogen_check_very_rich"); }
	}
}

void EButtonCheck::incoming_data(FilterBlock* _filter)
{
	change_state(_filter->base_filter_data_bool.at(data_id));
}
