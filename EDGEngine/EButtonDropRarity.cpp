#include "EButtonDropRarity.h"

EButtonDropRarity::EButtonDropRarity(float _x, float _y, float _sx, float _sy, Enums::ButtonType _type) : EButton(_x, _y, _sx, _sy)
{
	button_type = _type;

	master_position = Enums::PositionMaster::FILTER_BLOCK;
	text_align_x = Enums::PositionMode::MID;

	have_text = true;
	have_icon = false;

	rama_thikness = 1;
	can_be_removed = false;



	have_rama = true;
	rama_color->set(0.05f, 0.15f, 0.25f, 0.6f);
	is_drop_list = true;



	drop_elements = 4;

	drop_text.push_back("Обычн.");
	drop_text.push_back("Магич.");
	drop_text.push_back("Редкий");
	drop_text.push_back("Уник.");

	drop_text_base.push_back("Normal");
	drop_text_base.push_back("Magic");
	drop_text_base.push_back("Rare");
	drop_text_base.push_back("Unique");

	have_list_color = true;
	drop_list_color.push_back(EColorCollection::DAD_NORMAL);
	drop_list_color.push_back(EColorCollection::DAD_MAGIC);
	drop_list_color.push_back(EColorCollection::DAD_RARE);
	drop_list_color.push_back(EColorCollection::DAD_UNIQUE);
	
}

void EButtonDropRarity::click_event()
{
}

void EButtonDropRarity::incoming_data(FilterBlock* _filter)
{
	if (button_type == Enums::ButtonType::BUTTON_RARITY)
	{
		if (_filter->item_rarity == drop_text_base.at(0)) { text = drop_text.at(0); selected_element = 0; }
		if (_filter->item_rarity == drop_text_base.at(1)) { text = drop_text.at(1); selected_element = 1; }
		if (_filter->item_rarity == drop_text_base.at(2)) { text = drop_text.at(2); selected_element = 2; }
		if (_filter->item_rarity == drop_text_base.at(3)) { text = drop_text.at(3); selected_element = 3; }

		if (text == drop_text.at(0)) { bg_color->set(EColorCollection::DAD_NORMAL); }
		if (text == drop_text.at(1)) { bg_color->set(EColorCollection::DAD_MAGIC); }
		if (text == drop_text.at(2)) { bg_color->set(EColorCollection::DAD_RARE); }
		if (text == drop_text.at(3)) { bg_color->set(EColorCollection::DAD_UNIQUE); }
	}
}

void EButtonDropRarity::drop_list_select_event()
{
	if (button_type == Enums::ButtonType::BUTTON_RARITY)
	{
		master_block->item_rarity = drop_text_base.at(selected_element);

		if (selected_element == 0) { bg_color->set(EColorCollection::DAD_NORMAL); }
		if (selected_element == 1) { bg_color->set(EColorCollection::DAD_MAGIC); }
		if (selected_element == 2) { bg_color->set(EColorCollection::DAD_RARE); }
		if (selected_element == 3) { bg_color->set(EColorCollection::DAD_UNIQUE); }
	}
}

