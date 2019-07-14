#include "EButtonAddNewBaseData.h"
#include "StaticData.h"

EButtonAddNewBaseData::EButtonAddNewBaseData(float _x, float _y, float _sx, float _sy):EButton(_x,_y,_sx,_sy)
{
	master_position = Enums::PositionMaster::WINDOW;

	position_mode_x = Enums::PositionMode::MID;
	position_mode_y = Enums::PositionMode::UP;

	text_align_x = Enums::PositionMode::MID;

	have_text = true;
	have_icon = false;
	have_rama = true;
	is_drop_list = false;
	can_be_removed = false;

	gabarite = DefaultGabarite::gabarite_remove;

	rama_thikness = 2;


	rama_color->set(0.05f, 0.15f, 0.25f, 0.6f);


}

void EButtonAddNewBaseData::click_event()
{
	StaticData::window_add_new_base_data->is_active = false;
	master_block->base_filter_data_active.at(data_id) = true;
}



void EButtonAddNewBaseData::input_finish_event()
{
}
