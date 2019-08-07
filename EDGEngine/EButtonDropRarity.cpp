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

	drop_text.push_back("Normal");
	drop_text.push_back("Magic");
	drop_text.push_back("Rare");
	drop_text.push_back("Unique");

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
		text = _filter->item_rarity;

		if (text == "Normal") { bg_color->set(EColorCollection::DAD_NORMAL); }
		if (text == "Magic") { bg_color->set(EColorCollection::DAD_MAGIC); }
		if (text == "Rare") { bg_color->set(EColorCollection::DAD_RARE); }
		if (text == "Unique") { bg_color->set(EColorCollection::DAD_UNIQUE); }
	}
}

void EButtonDropRarity::drop_list_select_event()
{
	if (button_type == Enums::ButtonType::BUTTON_RARITY)
	{
		master_block->item_rarity = text;

		if (text == "Normal") { bg_color->set(EColorCollection::DAD_NORMAL); }
		if (text == "Magic") { bg_color->set(EColorCollection::DAD_MAGIC); }
		if (text == "Rare") { bg_color->set(EColorCollection::DAD_RARE); }
		if (text == "Unique") { bg_color->set(EColorCollection::DAD_UNIQUE); }
	}
}

