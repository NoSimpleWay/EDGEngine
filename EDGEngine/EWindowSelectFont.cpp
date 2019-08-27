#include "EWindowSelectFont.h"
#include "EButtonText.h"

EWindowSelectFont::EWindowSelectFont(int _id, bool _can_be_closed):EWindow (_id, _can_be_closed)
{

	create_font_button("Fontin", EFont::font_list.at(0), 0);
	create_font_button("Georgia", EFont::font_list.at(1), 1);
	create_font_button("Verdana", EFont::font_list.at(2), 2);
	create_font_button("Franklin", EFont::font_list.at(3), 3);
	create_font_button("Arial", EFont::font_list.at(4), 4);
	create_font_button("Trebuchet", EFont::font_list.at(5), 5);
	create_font_button("Times new roman", EFont::font_list.at(6), 6);
	create_font_button("Courier", EFont::font_list.at(7), 7);
	create_font_button("Palatino", EFont::font_list.at(8), 8);
	create_font_button("Impact", EFont::font_list.at(9), 9);


}

void EWindowSelectFont::create_font_button(std::string _s, EFont* _f, int _id)
{
	EButton* but;

	window_size_x = 300;
	window_size_y = 500;

	align_x = Enums::PositionMode::MID;
	align_y = Enums::PositionMode::MID;

	but = new EButtonText(0.0f, -25.0f - _id*35.0f, 256.0f, 20.0f, Enums::ButtonType::BUTTON_SELECT_FONT);
	but->master_window = this;
	but->data_id = _id;
	but->text = "I like '"+_s+"' font!";
	but->description_text = "The quick brown fox jumps over the lazy dog (1234567890)";
	but->force_font = _f;

	button_list.push_back(but);
}

void EWindowSelectFont::update(float _d)
{
}

void EWindowSelectFont::draw(Batcher* _batch, float _delta)
{
}

void EWindowSelectFont::update_localisation()
{
	for (EButton* b : button_list)
	{
		b->update_localisation();
	}
}
