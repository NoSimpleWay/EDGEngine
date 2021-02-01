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


	if ((button_type == Enums::ButtonType::BUTTON_BASE_DATA_RARITY_REGULAR)||(button_type == Enums::ButtonType::BUTTON_MANUAL_LOOT_RARITY))
	{
		drop_elements = 4;



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

	if (button_type == Enums::ButtonType::BUTTON_KIND_OF_ALTERNATE_QUALITY)
	{
		drop_elements = 3;

		drop_text_base.push_back("Divergent");
		drop_text_base.push_back("Phantasmal");
		drop_text_base.push_back("Anomalous");

		have_list_color = true;
		drop_list_color.push_back(EColorCollection::PINK);
		drop_list_color.push_back(EColorCollection::GREEN);
		drop_list_color.push_back(EColorCollection::CYAN);
	}
	
	if (button_type == Enums::ButtonType::BUTTON_MANUAL_LOOT_ALTERNATE_QUALITY_TYPE)
	{
		drop_elements = 4;

		drop_text_base.push_back("None");
		drop_text_base.push_back("Divergent");
		drop_text_base.push_back("Phantasmal");
		drop_text_base.push_back("Anomalous");

		have_list_color = true;
		drop_list_color.push_back(EColorCollection::GRAY);
		drop_list_color.push_back(EColorCollection::PINK);
		drop_list_color.push_back(EColorCollection::GREEN);
		drop_list_color.push_back(EColorCollection::CYAN);
	}

	update_localisation();
}

void EButtonDropRarity::click_event()
{
}

void EButtonDropRarity::incoming_data(FilterBlock* _filter)
{
	//if (button_type == Enums::ButtonType::BUTTON_RARITY)
	//{
		/*if (_filter->item_rarity == drop_text_base.at(0)) { text = drop_text.at(0); selected_element = 0; }
		if (_filter->item_rarity == drop_text_base.at(1)) { text = drop_text.at(1); selected_element = 1; }
		if (_filter->item_rarity == drop_text_base.at(2)) { text = drop_text.at(2); selected_element = 2; }
		if (_filter->item_rarity == drop_text_base.at(3)) { text = drop_text.at(3); selected_element = 3; }

		if (text == drop_text.at(0)) { bg_color->set(EColorCollection::DAD_NORMAL); }
		if (text == drop_text.at(1)) { bg_color->set(EColorCollection::DAD_MAGIC); }
		if (text == drop_text.at(2)) { bg_color->set(EColorCollection::DAD_RARE); }
		if (text == drop_text.at(3)) { bg_color->set(EColorCollection::DAD_UNIQUE); }*/
	//}
}

void EButtonDropRarity::drop_list_select_event()
{
	if (button_type == Enums::ButtonType::BUTTON_RARITY)
	{
		//master_block->item_rarity = drop_text_base.at(selected_element);
	}

	if (button_type == Enums::ButtonType::BUTTON_MANUAL_LOOT_RARITY)
	{
		StaticData::window_manual_loot->rarity = drop_text_base.at(selected_element);
	}

	if (button_type == Enums::ButtonType::BUTTON_MANUAL_LOOT_ALTERNATE_QUALITY_TYPE)
	{
		StaticData::window_manual_loot->selected_alternate_quality = selected_element;
		
		if (selected_element > 0)
		{
			StaticData::window_manual_loot->any_alternate_quality = true;
		}
		else
		{
			StaticData::window_manual_loot->any_alternate_quality = false;
		}
	}

	if (have_list_color)
	{
		bg_color->set(drop_list_color.at(selected_element));
	}
	/*if (selected_element == 0) { bg_color->set(EColorCollection::DAD_NORMAL); }
	if (selected_element == 1) { bg_color->set(EColorCollection::DAD_MAGIC); }
	if (selected_element == 2) { bg_color->set(EColorCollection::DAD_RARE); }
	if (selected_element == 3) { bg_color->set(EColorCollection::DAD_UNIQUE); }*/
}

void EButtonDropRarity::update_localisation()
{
	drop_text.clear();

	if ((button_type == Enums::ButtonType::BUTTON_BASE_DATA_RARITY_REGULAR) || (button_type == Enums::ButtonType::BUTTON_MANUAL_LOOT_RARITY))
	{
		drop_text.push_back(EString::localize_it("rarity_name_normal"));
		drop_text.push_back(EString::localize_it("rarity_name_magic"));
		drop_text.push_back(EString::localize_it("rarity_name_rare"));
		drop_text.push_back(EString::localize_it("rarity_name_unique"));

		text = drop_text.at(selected_element);

		if (selected_element == 0) { bg_color->set(EColorCollection::DAD_NORMAL); }
		if (selected_element == 1) { bg_color->set(EColorCollection::DAD_MAGIC); }
		if (selected_element == 2) { bg_color->set(EColorCollection::DAD_RARE); }
		if (selected_element == 3) { bg_color->set(EColorCollection::DAD_UNIQUE); }
	}

	if (button_type == Enums::ButtonType::BUTTON_KIND_OF_ALTERNATE_QUALITY)
	{
		drop_text.push_back(EString::localize_it("alternate_quality_name_divergent"));
		drop_text.push_back(EString::localize_it("alternate_quality_name_phantasmal"));
		drop_text.push_back(EString::localize_it("alternate_quality_name_anomalous"));

		text = drop_text.at(selected_element);

		if (selected_element == 0) { bg_color->set(EColorCollection::PINK); }
		if (selected_element == 1) { bg_color->set(EColorCollection::GREEN); }
		if (selected_element == 2) { bg_color->set(EColorCollection::CYAN); }
	}
	
	if (button_type == Enums::ButtonType::BUTTON_MANUAL_LOOT_ALTERNATE_QUALITY_TYPE)
	{
		drop_text.push_back(EString::localize_it("alternate_quality_name_none"));
		drop_text.push_back(EString::localize_it("alternate_quality_name_divergent"));
		drop_text.push_back(EString::localize_it("alternate_quality_name_phantasmal"));
		drop_text.push_back(EString::localize_it("alternate_quality_name_anomalous"));

		text = drop_text.at(selected_element);

		if (selected_element == 0) { bg_color->set(EColorCollection::GRAY); }
		if (selected_element == 1) { bg_color->set(EColorCollection::PINK); }
		if (selected_element == 2) { bg_color->set(EColorCollection::GREEN); }
		if (selected_element == 3) { bg_color->set(EColorCollection::CYAN); }
	}
}

