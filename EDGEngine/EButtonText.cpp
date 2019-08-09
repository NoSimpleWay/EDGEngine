#include "EButtonText.h"
#include "StaticData.h"



EButtonText::EButtonText(float _x, float _y, float _sx, float _sy, Enums::ButtonType _type):EButton(_x,_y,_sx,_sy)
{
	have_text = true;
	have_rama = true;
	have_icon = false;

	rama_thikness = 2;
	rama_color->set(.2f, .3f, .4f, .5f);

	button_type = _type;

	if (button_type == Enums::ButtonType::BUTTON_OPEN_DEFAULT_DROP_SOUND_WINDOW)
	{
		text_align_x = Enums::PositionMode::MID;
		text = "Стандартный звук";
		description_text = "Открыть список звуков, встроенных в игру";

		master_position = Enums::PositionMaster::WINDOW;
	}

	if (button_type == Enums::ButtonType::BUTTON_OPEN_CUSTOM_DROP_SOUND_WINDOW)
	{
		text_align_x = Enums::PositionMode::MID;
		text = "Пользовательский звук";
		description_text = "Открыть список пользовательских звуков из папки Path of Exile";

		master_position = Enums::PositionMaster::WINDOW;
	}

	if (button_type == Enums::ButtonType::BUTTON_ADD_EXPLICIT_GROUP)
	{
		text_align_x = Enums::PositionMode::MID;
		position_mode_x = Enums::PositionMode::MID;
		position_mode_y = Enums::PositionMode::UP;

		text = "Добавить аффикс";
		description_text = "Добавить название определенного суффикса/префикса";

		master_position = Enums::PositionMaster::WINDOW;

		bg_color->set(0.5f,0.5f,0.8f,0.5f);
	}

	if (button_type == Enums::ButtonType::BUTTON_ACTIVE_BASE_CLASS_LIST)
	{
		text_align_x = Enums::PositionMode::MID;
		position_mode_x = Enums::PositionMode::MID;
		position_mode_y = Enums::PositionMode::UP;

		text = "Добавить класс";
		description_text = "Добавить список классов предмета (сапоги, перчатки, валюта, и т.д.)";

		master_position = Enums::PositionMaster::WINDOW;

		bg_color->set(0.5f, 0.8f, 0.5f, 0.5f);
	}
	
	if (button_type == Enums::ButtonType::BUTTON_ACTIVE_PROPHECY_LIST)
	{
		text_align_x = Enums::PositionMode::MID;
		position_mode_x = Enums::PositionMode::MID;
		position_mode_y = Enums::PositionMode::UP;

		text = "Добавить пророчество";
		description_text = "Добавить список пророчеств по названию";

		master_position = Enums::PositionMaster::WINDOW;

		bg_color->set(0.8f, 0.5f, 0.8f, 0.5f);
	}

	if (button_type == Enums::ButtonType::BUTTON_ADD_EXPLICIT_ELEMENT)
	{
		text_align_x = Enums::PositionMode::MID;
		position_mode_x = Enums::PositionMode::LEFT;
		position_mode_y = Enums::PositionMode::UP;

		text = "Добавить аффикс";

		master_position = Enums::PositionMaster::WINDOW;
	}

	if (button_type == Enums::ButtonType::BUTTON_MINIMAP_ICON_SELECT_SIZE)
	{
		text_align_x = Enums::PositionMode::MID;
		position_mode_x = Enums::PositionMode::LEFT;
		position_mode_y = Enums::PositionMode::DOWN;

		//text = "Select size of minimap icon";

		master_position = Enums::PositionMaster::WINDOW;
	}

	if (button_type == Enums::ButtonType::BUTTON_SET_RAY_IS_TEMPOTARY)
	{
		text_align_x = Enums::PositionMode::MID;
		text = "Временный";

		master_position = Enums::PositionMaster::WINDOW;
	}

	if (button_type == Enums::ButtonType::BUTTON_SET_RAY_IS_CONSTANT)
	{
		text_align_x = Enums::PositionMode::MID;
		text = "Постоянный";

		master_position = Enums::PositionMaster::WINDOW;
	}

	if (button_type == Enums::ButtonType::BUTTON_CANCEL_REMOVE_FILTER_BLOCK)
	{
		text_align_x = Enums::PositionMode::MID;

		position_mode_x = Enums::PositionMode::MID;
		position_mode_y = Enums::PositionMode::MID;

		master_position = Enums::PositionMaster::FILTER_BLOCK;
		text = "ОТМЕНИТЬ";
	}
}

void EButtonText::click_event()
{
	if (button_type == Enums::ButtonType::BUTTON_OPEN_DEFAULT_DROP_SOUND_WINDOW)
	{
		StaticData::window_find_item->is_active = true;
		StaticData::window_find_item->window_searchs_mode = Enums::WindowSearchMode::DEFAULT_DROP_SOUND;

		StaticData::window_find_item->button_event(this);

	}

	if (button_type == Enums::ButtonType::BUTTON_OPEN_CUSTOM_DROP_SOUND_WINDOW)
	{
		StaticData::window_find_item->is_active = true;
		StaticData::window_find_item->window_searchs_mode = Enums::WindowSearchMode::CUSTOM_DROP_SOUND;

		StaticData::window_find_item->button_event(this);
	}

	if (button_type == Enums::ButtonType::BUTTON_ADD_EXPLICIT_GROUP)
	{
		master_block->explicit_list.at(data_id)->is_active = true;
		master_block->explicit_list.at(data_id)->button_close->is_active = true;
		master_block->explicit_list.at(data_id)->button_add->is_active = true;

		StaticData::window_add_new_base_data->is_active = false;
	}

	if (button_type == Enums::ButtonType::BUTTON_ADD_EXPLICIT_ELEMENT)
	{

	}

	if (button_type == Enums::ButtonType::BUTTON_ACTIVE_BASE_CLASS_LIST)
	{
		master_block->plus_class_button_link->is_active = true;
		master_block->remove_base_class_button->is_active = true;
		master_block->is_base_class_active=true;

		StaticData::window_add_new_base_data->is_active = false;
	}

	if (button_type == Enums::ButtonType::BUTTON_ACTIVE_PROPHECY_LIST)
	{
		master_block->plus_prophecy_button_link->is_active = true;
		master_block->remove_prophecy_button->is_active = true;
		master_block->is_prophecy_active = true;

		StaticData::window_add_new_base_data->is_active = false;
	}

	if ((button_type == Enums::ButtonType::BUTTON_MINIMAP_ICON_SELECT_SIZE)&&(master_block->is_minimap_icon))
	{
		master_block->minimap_icon_size = Enums::IconSize(data_id);
		StaticData::window_filter_visual_editor->update_minimap_button();
	}

	if ((button_type == Enums::ButtonType::BUTTON_SET_RAY_IS_CONSTANT))
	{
		master_block->ray_is_temp = false;

		StaticData::window_filter_visual_editor->update_ray_button();
	}

	if ((button_type == Enums::ButtonType::BUTTON_SET_RAY_IS_TEMPOTARY))
	{
		master_block->ray_is_temp = true;

		StaticData::window_filter_visual_editor->update_ray_button();
	}

	if ((button_type == Enums::ButtonType::BUTTON_CANCEL_REMOVE_FILTER_BLOCK))
	{
		master_block->remove_timer = -100;

		is_active = false;
	}
}
