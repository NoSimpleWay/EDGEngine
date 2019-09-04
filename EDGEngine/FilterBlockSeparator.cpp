#include "FilterBlockSeparator.h"
#include "EButtonService.h"
#include "StaticData.h"
#include "EButtonInputBaseData.h"

FilterBlockSeparator::FilterBlockSeparator()
{
	EButton* but = new EButtonService(5.0f, 0.0f, 16.0f, 16.0f, Enums::ButtonType::BUTTON_SEPARATOR_COLLAPSE);
	but->master_separator = this;
	but->master_window = StaticData::window_filter_block;
	StaticData::window_filter_block->button_list.push_back(but);
	link_to_collapse = but;



	but = new EButtonInputBaseData(30.0f, 0.0f, 512.0f, 16.0f, Enums::ButtonType::BUTTON_SEPARATOR_CAPTION_TEXT);
	but->master_separator = this;
	but->master_window = StaticData::window_filter_block;
	StaticData::window_filter_block->button_list.push_back(but);
	link_to_caption_text = but;

	but = new EButtonService(600.0f, 0.0f, 16.0f, 16.0f, Enums::ButtonType::BUTTON_REMOVE_SEPARATOR);
	but->master_separator = this;
	but->master_window = StaticData::window_filter_block;
	StaticData::window_filter_block->button_list.push_back(but);
	link_to_remove = but;
}
