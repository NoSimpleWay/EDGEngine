#include "EWindowOil.h"
#include "EButtonService.h"
#include "EUtils.h"
#include "DADItem.h"
#include "ItemList.h"
#include "EButtonChange.h"
#include "EButtonInputSearchItem.h"



EWindowOil::EWindowOil(int _id, bool _can_be_closed):EWindow (_id, _can_be_closed)
{


	window_size_x = 1400.0f;
	window_size_y = 600.0f;

	bg_color->set_alpha(EColorCollection::DARK_GRAY, 0.9f);

	int id = 0;

	

	for (int i = 0; i < 15; i++)
	for (int j = 0; j < 43; j++)
	{
		if (id < EString::notable_list.size())
		{
			EButton* but = new EButtonService(10.0f + j * 32.0f, 400.0f - i * 32.0f, 28.0f, 28.0f, Enums::ButtonType::BUTTON_PASSIVE);
			but->master_window = this;

			but->description_text = EString::notable_list.at(id)->passive_name + "\\n\\n";

			if (EString::notable_list.at(id)->need_oil.at(Enums::OilId::AMBER) > 0)			{ but->description_text += "Amber oil: " + std::to_string(EString::notable_list.at(id)->need_oil.at(Enums::OilId::AMBER)) + "\\n"; }
			if (EString::notable_list.at(id)->need_oil.at(Enums::OilId::AZURE) > 0)			{ but->description_text += "Azure oil: " + std::to_string(EString::notable_list.at(id)->need_oil.at(Enums::OilId::AZURE)) + "\\n"; }
			if (EString::notable_list.at(id)->need_oil.at(Enums::OilId::BLACK) > 0)			{ but->description_text += "Black oil: " + std::to_string(EString::notable_list.at(id)->need_oil.at(Enums::OilId::BLACK)) + "\\n"; }
			if (EString::notable_list.at(id)->need_oil.at(Enums::OilId::CLEAR) > 0)			{ but->description_text += "Clear oil: " + std::to_string(EString::notable_list.at(id)->need_oil.at(Enums::OilId::CLEAR)) + "\\n"; }
			if (EString::notable_list.at(id)->need_oil.at(Enums::OilId::CRIMSON) > 0)		{ but->description_text += "Crimson oil: " + std::to_string(EString::notable_list.at(id)->need_oil.at(Enums::OilId::CRIMSON)) + "\\n"; }
			if (EString::notable_list.at(id)->need_oil.at(Enums::OilId::GOLDEN) > 0)		{ but->description_text += "Golden oil: " + std::to_string(EString::notable_list.at(id)->need_oil.at(Enums::OilId::GOLDEN)) + "\\n"; }
			if (EString::notable_list.at(id)->need_oil.at(Enums::OilId::OPALESCENT) > 0)	{ but->description_text += "Opalescent oil: " + std::to_string(EString::notable_list.at(id)->need_oil.at(Enums::OilId::OPALESCENT)) + "\\n"; }
			if (EString::notable_list.at(id)->need_oil.at(Enums::OilId::SEPIA) > 0)			{ but->description_text += "Sepia oil: " + std::to_string(EString::notable_list.at(id)->need_oil.at(Enums::OilId::SEPIA)) + "\\n"; }
			if (EString::notable_list.at(id)->need_oil.at(Enums::OilId::SILVER) > 0)		{ but->description_text += "Silver oil: " + std::to_string(EString::notable_list.at(id)->need_oil.at(Enums::OilId::SILVER)) + "\\n"; }
			if (EString::notable_list.at(id)->need_oil.at(Enums::OilId::TEAL) > 0)			{ but->description_text += "Teal oil: " + std::to_string(EString::notable_list.at(id)->need_oil.at(Enums::OilId::TEAL)) + "\\n"; }
			if (EString::notable_list.at(id)->need_oil.at(Enums::OilId::VERDANT) > 0)		{ but->description_text += "Verdant oil: " + std::to_string(EString::notable_list.at(id)->need_oil.at(Enums::OilId::VERDANT)) + "\\n"; }
			if (EString::notable_list.at(id)->need_oil.at(Enums::OilId::VIOLET) > 0)		{ but->description_text += "Violet oil: " + std::to_string(EString::notable_list.at(id)->need_oil.at(Enums::OilId::VIOLET)) + "\\n"; }
			
			but->description_text += "\\n" + EString::notable_list.at(id)->passive_description;

			but->gabarite = EString::notable_list.at(id)->gabarite;

			button_list.push_back(but);
			passive_button_list.push_back(but);

			//std::cout << "button_created: " << std::to_string(id) << " " << EString::notable_list.at(id)->passive_name << std::endl;
			id++;
		}
	}

			
			create_oil_button(0, "Clear Oil");
			create_oil_button(1, "Sepia Oil");
			create_oil_button(2, "Amber Oil");
			create_oil_button(3, "Verdant Oil");
			create_oil_button(4, "Teal Oil");
			create_oil_button(5, "Azure Oil");
			create_oil_button(6, "Violet Oil");
			create_oil_button(7, "Crimson Oil");
			create_oil_button(8, "Black Oil");
			create_oil_button(9, "Opalescent Oil");
			create_oil_button(10, "Silver Oil");
			create_oil_button(11, "Golden Oil");

			EButton* but = new EButtonInputSearchItem(100.0f, -130.0f, 300.0f, 20.0f, Enums::ButtonType::BUTTON_SEARCH_INPUT_FOR_PASSIVES);
			but->master_window = this;

			but->master_position = Enums::PositionMaster::WINDOW;
			but->position_mode_x = Enums::PositionMode::LEFT;
			but->position_mode_y = Enums::PositionMode::UP;

			button_list.push_back(but);
			link_to_search_button = but;

			update_passives_button();
}

void EWindowOil::create_oil_button(int _oil_id, std::string _name)
{
	EButton* but = new EButtonService(100.0f + _oil_id * 100.0f, -20.0f, 78.0f, 78.0f, Enums::ButtonType::BUTTON_CHECK_OIL);
	but->master_window = this;
	//but->gabarite = _g;
	but->data_id = _oil_id;


	but->gabarite =	DefaultGabarite::gabarite_oil[_oil_id];

	button_list.push_back(but);
	oil_button_list.push_back(but);

	but = new EButtonChange(110.0f + _oil_id * 100.0f, -20.0f - 85.0f, 16.0f, 16.0f, Enums::ButtonType::BUTTON_CHANGE_OIL_COUNT, false);
	but->master_window = this;
	button_list.push_back(but);
	but->data_id = _oil_id;
	but->position_mode_x = Enums::PositionMode::LEFT;
	but->position_mode_y = Enums::PositionMode::UP;

	but = new EButtonChange(90.0f + _oil_id * 100.0f + 62.0f, -20.0f - 85.0f, 16.0f, 16.0f, Enums::ButtonType::BUTTON_CHANGE_OIL_COUNT, true);
	but->master_window = this;
	button_list.push_back(but);
	but->data_id = _oil_id;
	but->position_mode_x = Enums::PositionMode::LEFT;
	but->position_mode_y = Enums::PositionMode::UP;
}

void EWindowOil::update_passives_button()
{

	int but_id = 0;

	for (NotablePassive* p : EString::notable_list)
	{
		bool enough_oil = true;

		if (EString::to_lower(passive_button_list.at(but_id)->description_text).find(link_to_search_button->text) == std::string::npos)
		{
			enough_oil = false;
		}
		

		for (int i=0; i<12; i++)
		{
			if (oil_count.at(i) < p->need_oil.at(i))
			{
				enough_oil = false;
			}
		}

		

		if (enough_oil)
		{
			passive_button_list.at(but_id)->icon_color->set(EColorCollection::WHITE);
			passive_button_list.at(but_id)->rama_thikness = 2;
			passive_button_list.at(but_id)->rama_color->set_alpha(EColorCollection::DAD_UNIQUE, 0.75);
		}
		else
		{
			passive_button_list.at(but_id)->icon_color->set_alpha(EColorCollection::GRAY, 0.25f);
			passive_button_list.at(but_id)->rama_thikness = 1;
			passive_button_list.at(but_id)->rama_color->set_alpha(EColorCollection::RED, 0.20);
		}


		
		but_id++;
	}
}

void EWindowOil::update(float _d)
{
}

void EWindowOil::draw(Batcher* _batch, float _delta)
{
	_batch->setcolor(EColorCollection::GREEN);

	EFont::active_font->align_x = Enums::PositionMode::MID;
	for (int i = 0; i < 12; i++)
	{
		EFont::active_font->draw(_batch, std::to_string(oil_count.at(i)), 100.0f + i * 100.0f + 39.0f + pos_x, pos_y + window_size_y - 120.0f);
	}

	EFont::active_font->align_x = Enums::PositionMode::LEFT;
}

void EWindowOil::update_localisation()
{
	for (EButton* b : button_list)
	{b->update_localisation();}

	for (int i = 0; i < passive_button_list.size(); i++)
	{
		if (EString::active_localisation == Enums::LocalisationList::EN)
		{
			passive_button_list.at(i)->description_text = EString::notable_list.at(i)->passive_name + "\\n\\n";

			if (EString::notable_list.at(i)->need_oil.at(Enums::OilId::AMBER) > 0) { passive_button_list.at(i)->description_text += "Amber oil: " + std::to_string(EString::notable_list.at(i)->need_oil.at(Enums::OilId::AMBER)) + "\\n"; }
			if (EString::notable_list.at(i)->need_oil.at(Enums::OilId::AZURE) > 0) { passive_button_list.at(i)->description_text += "Azure oil: " + std::to_string(EString::notable_list.at(i)->need_oil.at(Enums::OilId::AZURE)) + "\\n"; }
			if (EString::notable_list.at(i)->need_oil.at(Enums::OilId::BLACK) > 0) { passive_button_list.at(i)->description_text += "Black oil: " + std::to_string(EString::notable_list.at(i)->need_oil.at(Enums::OilId::BLACK)) + "\\n"; }
			if (EString::notable_list.at(i)->need_oil.at(Enums::OilId::CLEAR) > 0) { passive_button_list.at(i)->description_text += "Clear oil: " + std::to_string(EString::notable_list.at(i)->need_oil.at(Enums::OilId::CLEAR)) + "\\n"; }
			if (EString::notable_list.at(i)->need_oil.at(Enums::OilId::CRIMSON) > 0) { passive_button_list.at(i)->description_text += "Crimson oil: " + std::to_string(EString::notable_list.at(i)->need_oil.at(Enums::OilId::CRIMSON)) + "\\n"; }
			if (EString::notable_list.at(i)->need_oil.at(Enums::OilId::GOLDEN) > 0) { passive_button_list.at(i)->description_text += "Golden oil: " + std::to_string(EString::notable_list.at(i)->need_oil.at(Enums::OilId::GOLDEN)) + "\\n"; }
			if (EString::notable_list.at(i)->need_oil.at(Enums::OilId::OPALESCENT) > 0) { passive_button_list.at(i)->description_text += "Opalescent oil: " + std::to_string(EString::notable_list.at(i)->need_oil.at(Enums::OilId::OPALESCENT)) + "\\n"; }
			if (EString::notable_list.at(i)->need_oil.at(Enums::OilId::SEPIA) > 0) { passive_button_list.at(i)->description_text += "Sepia oil: " + std::to_string(EString::notable_list.at(i)->need_oil.at(Enums::OilId::SEPIA)) + "\\n"; }
			if (EString::notable_list.at(i)->need_oil.at(Enums::OilId::SILVER) > 0) { passive_button_list.at(i)->description_text += "Silver oil: " + std::to_string(EString::notable_list.at(i)->need_oil.at(Enums::OilId::SILVER)) + "\\n"; }
			if (EString::notable_list.at(i)->need_oil.at(Enums::OilId::TEAL) > 0) { passive_button_list.at(i)->description_text += "Teal oil: " + std::to_string(EString::notable_list.at(i)->need_oil.at(Enums::OilId::TEAL)) + "\\n"; }
			if (EString::notable_list.at(i)->need_oil.at(Enums::OilId::VERDANT) > 0) { passive_button_list.at(i)->description_text += "Verdant oil: " + std::to_string(EString::notable_list.at(i)->need_oil.at(Enums::OilId::VERDANT)) + "\\n"; }
			if (EString::notable_list.at(i)->need_oil.at(Enums::OilId::VIOLET) > 0) { passive_button_list.at(i)->description_text += "Violet oil: " + std::to_string(EString::notable_list.at(i)->need_oil.at(Enums::OilId::VIOLET)) + "\\n"; }

			passive_button_list.at(i)->description_text += "\\n" + EString::notable_list.at(i)->passive_description;
		}

		if (EString::active_localisation == Enums::LocalisationList::RU)
		{
			passive_button_list.at(i)->description_text = EString::notable_list.at(i)->passive_ru_name + "\\n\\n";

			if (EString::notable_list.at(i)->need_oil.at(Enums::OilId::AMBER) > 0) { passive_button_list.at(i)->description_text += "Янтарное масло: " + std::to_string(EString::notable_list.at(i)->need_oil.at(Enums::OilId::AMBER)) + "\\n"; }
			if (EString::notable_list.at(i)->need_oil.at(Enums::OilId::AZURE) > 0) { passive_button_list.at(i)->description_text += "Лазурное масло: " + std::to_string(EString::notable_list.at(i)->need_oil.at(Enums::OilId::AZURE)) + "\\n"; }
			if (EString::notable_list.at(i)->need_oil.at(Enums::OilId::BLACK) > 0) { passive_button_list.at(i)->description_text += "Чёрное масло: " + std::to_string(EString::notable_list.at(i)->need_oil.at(Enums::OilId::BLACK)) + "\\n"; }
			if (EString::notable_list.at(i)->need_oil.at(Enums::OilId::CLEAR) > 0) { passive_button_list.at(i)->description_text += "Прозрачное масло: " + std::to_string(EString::notable_list.at(i)->need_oil.at(Enums::OilId::CLEAR)) + "\\n"; }
			if (EString::notable_list.at(i)->need_oil.at(Enums::OilId::CRIMSON) > 0) { passive_button_list.at(i)->description_text += "Алое масло: " + std::to_string(EString::notable_list.at(i)->need_oil.at(Enums::OilId::CRIMSON)) + "\\n"; }
			if (EString::notable_list.at(i)->need_oil.at(Enums::OilId::GOLDEN) > 0) { passive_button_list.at(i)->description_text += "Золотое масло: " + std::to_string(EString::notable_list.at(i)->need_oil.at(Enums::OilId::GOLDEN)) + "\\n"; }
			if (EString::notable_list.at(i)->need_oil.at(Enums::OilId::OPALESCENT) > 0) { passive_button_list.at(i)->description_text += "Перламутровое масло: " + std::to_string(EString::notable_list.at(i)->need_oil.at(Enums::OilId::OPALESCENT)) + "\\n"; }
			if (EString::notable_list.at(i)->need_oil.at(Enums::OilId::SEPIA) > 0) { passive_button_list.at(i)->description_text += "Коричневое масло: " + std::to_string(EString::notable_list.at(i)->need_oil.at(Enums::OilId::SEPIA)) + "\\n"; }
			if (EString::notable_list.at(i)->need_oil.at(Enums::OilId::SILVER) > 0) { passive_button_list.at(i)->description_text += "Серебряное масло: " + std::to_string(EString::notable_list.at(i)->need_oil.at(Enums::OilId::SILVER)) + "\\n"; }
			if (EString::notable_list.at(i)->need_oil.at(Enums::OilId::TEAL) > 0) { passive_button_list.at(i)->description_text += "Бирюзовое масло: " + std::to_string(EString::notable_list.at(i)->need_oil.at(Enums::OilId::TEAL)) + "\\n"; }
			if (EString::notable_list.at(i)->need_oil.at(Enums::OilId::VERDANT) > 0) { passive_button_list.at(i)->description_text += "Изумрудное масло: " + std::to_string(EString::notable_list.at(i)->need_oil.at(Enums::OilId::VERDANT)) + "\\n"; }
			if (EString::notable_list.at(i)->need_oil.at(Enums::OilId::VIOLET) > 0) { passive_button_list.at(i)->description_text += "Фиолетовое масло: " + std::to_string(EString::notable_list.at(i)->need_oil.at(Enums::OilId::VIOLET)) + "\\n"; }

			passive_button_list.at(i)->description_text += "\\n" + EString::notable_list.at(i)->passive_ru_description;
		}
	}

	/*
	for (int i = 0; i < EString::oil_name_list.size(); i++)
	{
		oil_button_list.at(i)->description_text = EString::localize_it(EString::oil_name_list.at(i));
	}*/
}

void EWindowOil::input_event(EButton* _b)
{
	update_passives_button();
}
