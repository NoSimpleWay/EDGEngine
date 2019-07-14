#include "EButtonRemoveBaseData.h"

EButtonRemoveBaseData::EButtonRemoveBaseData(float _x, float _y, float _sx, float _sy, Enums::ButtonType _type):EButton(_x,_y,_sx,_sy)
{
	master_position = Enums::PositionMaster::FILTER_BLOCK;

	position_mode_x = Enums::PositionMode::LEFT;
	position_mode_y = Enums::PositionMode::DOWN;

	text_align_x = Enums::PositionMode::MID;

	have_text = false;
	have_icon = true;
	have_rama = true;
	is_drop_list = false;
	can_be_removed = false;

	gabarite = DefaultGabarite::gabarite_remove;

	rama_thikness = 1;


	rama_color->set(0.05f, 0.15f, 0.25f, 0.6f);


	button_type = _type;
}

void EButtonRemoveBaseData::click_event()
{
	master_block->base_filter_data_active.at(data_id) = false;
}
