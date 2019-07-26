#include "EButtonExplicit.h"
#include "StaticData.h"

EButtonExplicit::EButtonExplicit(float _x, float _y, float _sx, float _sy) : EButton(_x, _y, _sx, _sy)
{
	bg_color->set(0.8f, 0.9f, 1.0f, 0.9f);

	master_position = Enums::PositionMaster::FILTER_BLOCK;

	position_mode_y = Enums::PositionMode::UP;

	have_input_mode = true;
	can_be_removed = true;
}

void EButtonExplicit::click_event()
{
	if (is_plus)
	{
		EButtonExplicit* explicit_button = new EButtonExplicit(0, 0, 100, 20);
		explicit_button->text = "new item";
		explicit_button->master_block = master_block;
		explicit_button->master_window = StaticData::window_filter_block;
		explicit_button->button_size_x = EFont::get_width(EFont::font_arial, "new item") + 5.0f;
		master_block->explicit_list.at(data_id)->button_list.push_back(explicit_button);

		master_block->button_list.push_back(explicit_button);
	}
}
