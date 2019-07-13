#include "EButtonRemoveBaseData.h"

EButtonRemoveBaseData::EButtonRemoveBaseData(float _x, float _y, float _sx, float _sy, Enums::ButtonType _type):EButton(_x,_y,_sx,_sy)
{
	button_type = _type;
}

void EButtonRemoveBaseData::click_event()
{
	master_block->base_filter_data_active.at(data_id) = false;
}
