#include "EButtonRemove.h"
#include "ExplicitGroup.h"

EButtonRemove::EButtonRemove(float _x, float _y, float _sx, float _sy, Enums::ButtonType _type):EButton(_x,_y,_sx,_sy)
{
	button_type = _type;
	master_position = Enums::PositionMaster::FILTER_BLOCK;

	position_mode_x = Enums::PositionMode::LEFT;
	position_mode_y = Enums::PositionMode::DOWN;

	if (button_type == Enums::ButtonType::BUTTON_REMOVE_EXPLICIT_GROUP)
	{
		position_mode_x = Enums::PositionMode::LEFT;
		position_mode_y = Enums::PositionMode::UP;
	}

	if (button_type == Enums::ButtonType::BUTTON_REMOVE_BASE_CLASS)
	{
		position_mode_x = Enums::PositionMode::LEFT;
		position_mode_y = Enums::PositionMode::UP;
	}

	if (button_type == Enums::ButtonType::BUTTON_REMOVE_PROPHECY)
	{
		position_mode_x = Enums::PositionMode::LEFT;
		position_mode_y = Enums::PositionMode::UP;
	}

	text_align_x = Enums::PositionMode::MID;

	have_text = false;
	have_icon = true;
	have_rama = true;
	is_drop_list = false;
	can_be_removed = false;

	gabarite = DefaultGabarite::gabarite_remove;

	rama_thikness = 1;


	rama_color->set(0.05f, 0.15f, 0.25f, 0.6f);



}

void EButtonRemove::click_event()
{
	if (button_type == Enums::ButtonType::BUTTON_REMOVE_BASE_DATA)
	{
		master_block->base_filter_data_active.at(data_id) = false;
	}

	if (button_type == Enums::ButtonType::BUTTON_REMOVE_EXPLICIT_GROUP)
	{
		master_block->explicit_list.at(data_id)->is_active = false;
		master_block->explicit_list.at(data_id)->button_add->is_active=false;

		for (EButton* b : master_block->explicit_list.at(data_id)->button_list)
		{
			b->need_remove = true;
		}

		is_active = false;
	}

	if (button_type == Enums::ButtonType::BUTTON_REMOVE_BASE_CLASS)
	{
		master_block->is_base_class_active = false;

		master_block->plus_class_button_link->is_active = false;

		for (EButton* b : master_block->base_class_list)
		{
			b->need_remove = true;
		}

		is_active = false;
	}

	if (button_type == Enums::ButtonType::BUTTON_REMOVE_PROPHECY)
	{
		master_block->is_prophecy_active = false;

		master_block->plus_prophecy_button_link->is_active = false;

		for (EButton* b : master_block->prophecy_list)
		{
			b->need_remove = true;
		}

		is_active = false;
	}
}

void EButtonRemove::update_localisation()
{
	if (button_type == Enums::ButtonType::BUTTON_REMOVE_EXPLICIT_GROUP)
	{
		description_text = EString::localize_it("description_remove_explicit_group");
	}

	if (button_type == Enums::ButtonType::BUTTON_REMOVE_BASE_CLASS)
	{
		description_text = EString::localize_it("description_remove_class");
	}

	if (button_type == Enums::ButtonType::BUTTON_REMOVE_PROPHECY)
	{
		description_text = EString::localize_it("description_remove_prophecies");
	}
}
