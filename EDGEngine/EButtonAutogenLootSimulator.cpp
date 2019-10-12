#include "EButtonAutogenLootSimulator.h"
#include "StaticData.h"





EButtonAutogenLootSimulator::EButtonAutogenLootSimulator(float _x, float _y, float _sx, float _sy, Enums::ButtonType _type) : EButton(_x, _y, _sx, _sy)   // конструктор класса SecondClass вызывает конструктор класса FirstClass
{
	button_type = _type;

	master_position = Enums::PositionMaster::WINDOW;

	position_mode_x = Enums::PositionMode::LEFT;
	position_mode_y = Enums::PositionMode::UP;

	text_align_x = Enums::PositionMode::MID;

	have_text = true;
	have_icon = false;

	rama_thikness = 1;
	can_be_removed = false;



	have_rama = true;
	rama_color->set(0.05f, 0.15f, 0.25f, 0.6f);
	is_drop_list = true;

	drop_elements = 5;

	drop_text.push_back("Very Low");
	drop_text.push_back("Low");
	drop_text.push_back("Default");
	drop_text.push_back("Rich");
	drop_text.push_back("Very rich");

	drop_text_base.push_back("Very Low");
	drop_text_base.push_back("Low");
	drop_text_base.push_back("Default");
	drop_text_base.push_back("Rich");
	drop_text_base.push_back("Very rich");

	selected_element = 0;
	text = drop_text.at(0);


}

void EButtonAutogenLootSimulator::click_event()
{
}

void EButtonAutogenLootSimulator::incoming_data(FilterBlock* _filter)
{
	//if (button_type == Enums::ButtonType::BUTTON_CONDITION_AUTOGEN_LOOT_SIMULATOR) { text = _filter->required_level_condition; }
}

void EButtonAutogenLootSimulator::drop_list_select_event()
{
	if (button_type == Enums::ButtonType::BUTTON_CONDITION_AUTOGEN_LOOT_SIMULATOR)
	{ 
		for (int i = 0; i < 87; i++)
		for (int j = 0; j < 125; j++)
		{
			StaticData::window_loot_simulator->free_space[j][i] = true;
		}

		for (LootItem* _l : StaticData::window_loot_simulator->main_loot_item_list)
		{
			StaticData::window_loot_simulator->find_filter_block(_l, StaticData::window_filter_block, false);
		}

		for (LootItem* _l : StaticData::window_loot_simulator->main_loot_item_list)
		{
			StaticData::window_loot_simulator->place(_l);
		}

		EFont::active_font->scale = 1.0f;
	}

}

void EButtonAutogenLootSimulator::update_localisation()
{
	if (button_type == Enums::ButtonType::BUTTON_CONDITION_AUTOGEN_LOOT_SIMULATOR)
	{
		description_text = EString::localize_it("description_drop_list_autogen_loot_simulator");

		drop_text.at(0) = EString::localize_it("drop_list_element_very_low");
		drop_text.at(1) = EString::localize_it("drop_list_element_low");
		drop_text.at(2) = EString::localize_it("drop_list_element_default");
		drop_text.at(3) = EString::localize_it("drop_list_element_rich");
		drop_text.at(4) = EString::localize_it("drop_list_element_very_rich");

		text = drop_text.at(selected_element);
	}
}




