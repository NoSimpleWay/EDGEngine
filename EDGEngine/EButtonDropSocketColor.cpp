#include "EButtonDropSocketColor.h"
#include "StaticData.h"





EButtonDropSocketColor::EButtonDropSocketColor(float _x, float _y, float _sx, float _sy, Enums::ButtonType _type) : EButton(_x, _y, _sx, _sy)   // конструктор класса SecondClass вызывает конструктор класса FirstClass
{
	button_type = _type;

	master_position = Enums::PositionMaster::FILTER_BLOCK;
	text_align_x = Enums::PositionMode::MID;

	have_text = true;
	have_icon = false;

	rama_thikness = 1;
	can_be_removed = false;

	have_list_color = true;
	//drop_list_color.push_back(EColorCollection::DARK_GRAY);
	drop_list_color.push_back(EColorCollection::RED);
	drop_list_color.push_back(EColorCollection::GREEN);
	drop_list_color.push_back(EColorCollection::BLUE);
	drop_list_color.push_back(EColorCollection::WHITE);
	drop_list_color.push_back(EColorCollection::GRAY);
	drop_list_color.push_back(EColorCollection::YELLOW);

	have_rama = true;
	rama_color->set(0.05f, 0.15f, 0.25f, 0.6f);
	is_drop_list = true;

	bg_color = drop_list_color.at(selected_element);

	drop_elements = 6;





}

void EButtonDropSocketColor::click_event()
{
}

void EButtonDropSocketColor::incoming_data(FilterBlock* _filter)
{

}

void EButtonDropSocketColor::drop_list_select_event()
{
	StaticData::window_manual_loot->socket_color.at(data_id) = selected_element;

	bg_color = drop_list_color.at(selected_element);
	//if ()
}

void EButtonDropSocketColor::update_localisation()
{
	drop_text.clear();

	//drop_text.push_back(EString::localize_it("socket_color_none"));
	drop_text.push_back(EString::localize_it("socket_color_red"));
	drop_text.push_back(EString::localize_it("socket_color_green"));
	drop_text.push_back(EString::localize_it("socket_color_blue"));
	drop_text.push_back(EString::localize_it("socket_color_white"));
	drop_text.push_back(EString::localize_it("socket_color_abyss"));
	drop_text.push_back(EString::localize_it("socket_color_delve"));

	text = drop_text.at(selected_element);
}




