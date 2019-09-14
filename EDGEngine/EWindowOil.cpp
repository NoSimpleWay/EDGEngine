#include "EWindowOil.h"
#include "EButtonService.h"
#include "EUtils.h"

EWindowOil::EWindowOil(int _id, bool _can_be_closed):EWindow (_id, _can_be_closed)
{
	window_size_x = 1400.0f;
	window_size_y = 800.0f;

	bg_color->set_alpha(EColorCollection::DARK_GRAY, 0.9f);

	int id = 0;

	

	for (int i = 0; i < 13; i++)
	for (int j = 0; j < 30; j++)
	{
		if (id < EString::notable_list.size())
		{
			EButton* but = new EButtonService(100.0f + j * 40.0f, 600.0f - i * 40.0f, 32.0f, 32.0f, Enums::ButtonType::BUTTON_PASSIVE);
			but->master_window = this;

			but->description_text = EString::notable_list.at(id)->passive_name + "\\n\\n";

			if (EString::notable_list.at(id)->need_amber_oil > 0)		{ but->description_text += "Amber oil: " + std::to_string(EString::notable_list.at(id)->need_amber_oil) + "\\n"; }
			if (EString::notable_list.at(id)->need_azure_oil > 0)		{ but->description_text += "Azure oil: " + std::to_string(EString::notable_list.at(id)->need_azure_oil) + "\\n"; }
			if (EString::notable_list.at(id)->need_black_oil > 0)		{ but->description_text += "Black oil: " + std::to_string(EString::notable_list.at(id)->need_black_oil) + "\\n"; }
			if (EString::notable_list.at(id)->need_clear_oil > 0)		{ but->description_text += "Clear oil: " + std::to_string(EString::notable_list.at(id)->need_clear_oil) + "\\n"; }
			if (EString::notable_list.at(id)->need_crimson_oil > 0)		{ but->description_text += "Clear oil: " + std::to_string(EString::notable_list.at(id)->need_crimson_oil) + "\\n"; }
			if (EString::notable_list.at(id)->need_golden_oil > 0)		{ but->description_text += "Golden oil: " + std::to_string(EString::notable_list.at(id)->need_golden_oil) + "\\n"; }
			if (EString::notable_list.at(id)->need_opacelent_oil > 0)	{ but->description_text += "Golden oil: " + std::to_string(EString::notable_list.at(id)->need_opacelent_oil) + "\\n"; }
			if (EString::notable_list.at(id)->need_sepia_oil > 0)		{ but->description_text += "Sepia oil: " + std::to_string(EString::notable_list.at(id)->need_sepia_oil) + "\\n"; }
			if (EString::notable_list.at(id)->need_silver_oil > 0)		{ but->description_text += "Silver oil: " + std::to_string(EString::notable_list.at(id)->need_silver_oil) + "\\n"; }
			if (EString::notable_list.at(id)->need_teal_oil > 0)		{ but->description_text += "Teal oil: " + std::to_string(EString::notable_list.at(id)->need_teal_oil) + "\\n"; }
			if (EString::notable_list.at(id)->need_verdant_oil > 0)		{ but->description_text += "Verdant oil: " + std::to_string(EString::notable_list.at(id)->need_verdant_oil) + "\\n"; }
			if (EString::notable_list.at(id)->need_violet_oil > 0)		{ but->description_text += "Violet oil: " + std::to_string(EString::notable_list.at(id)->need_violet_oil) + "\\n"; }
			
			but->description_text += "\\n" + EString::notable_list.at(id)->passive_description;

			but->gabarite = EString::notable_list.at(id)->gabarite;

			button_list.push_back(but);

			std::cout << "button_created: " << std::to_string(id) << std::endl;
			id++;
		}
	}
}

void EWindowOil::update(float _d)
{
}

void EWindowOil::draw(Batcher* _batch, float _delta)
{
}

void EWindowOil::update_localisation()
{
}
