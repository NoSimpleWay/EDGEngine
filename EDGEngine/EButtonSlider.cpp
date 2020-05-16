#include "EButtonSlider.h"
#include "EUtils.h"
#include "StaticData.h"

std::string cached_text_hue;
std::string cached_text_saturation;
std::string cached_text_brightness;
std::string cached_text_alpha;
std::string cached_text_font_size;
std::string cached_text_sound_volume;
std::string cached_text_scroll;

EButtonSlider::EButtonSlider(float _x, float _y, float _sx, float _sy, Enums::ButtonType _type): EButton(_x, _y, _sx, _sy)
{
	button_type = _type;
	//description_text = "Change value";

	master_position = Enums::PositionMaster::WINDOW;

	have_icon = true;

	if (
		(button_type == Enums::ButtonType::BUTTON_BG_H) ||
		(button_type == Enums::ButtonType::BUTTON_TEXT_H) ||
		(button_type == Enums::ButtonType::BUTTON_RAMA_H)
		)
	{
		gabarite = DefaultGabarite::gabarite_slider_hue;
	}

	if (
		(button_type == Enums::ButtonType::BUTTON_BG_S) ||
		(button_type == Enums::ButtonType::BUTTON_TEXT_S) ||
		(button_type == Enums::ButtonType::BUTTON_RAMA_S)
		)
	{
		gabarite = DefaultGabarite::gabarite_slider_saturation;
		
	}

	if (
		(button_type == Enums::ButtonType::BUTTON_BG_V) ||
		(button_type == Enums::ButtonType::BUTTON_TEXT_V) ||
		(button_type == Enums::ButtonType::BUTTON_RAMA_V)
		)
	{
		gabarite = DefaultGabarite::gabarite_slider_value;
		
	}

	if (
		(button_type == Enums::ButtonType::BUTTON_BG_ALPHA) ||
		(button_type == Enums::ButtonType::BUTTON_TEXT_ALPHA) ||
		(button_type == Enums::ButtonType::BUTTON_RAMA_ALPHA)
		)
	{
		gabarite = DefaultGabarite::gabarite_slider_alpha;

		
	}

	if (button_type == Enums::ButtonType::BUTTON_SLIDER_FONT_SIZE)
	{
		gabarite = DefaultGabarite::gabarite_slider_value;

		
	}

	if (button_type == Enums::ButtonType::BUTTON_GLOBAL_DROP_SOUND_VOLUME)
	{
		have_bg = false;

		gabarite =				DefaultGabarite::gabarite_shaper_slider_bg;
		slider_head_texture	=	DefaultGabarite::gabarite_shaper_slider_head;
		slider_trail_texture =	DefaultGabarite::gabarite_shaper_slider_trail;

		can_be_highlighted = false;

		master_position = Enums::PositionMaster::WINDOW;

		position_mode_x = Enums::PositionMode::RIGHT;
		position_mode_y = Enums::PositionMode::UP;

		slider_value = 0.5f;



		
	}

	if (button_type == Enums::ButtonType::BUTTON_FILTER_BLOCK_SCROLL)
	{
		slider_is_horizontal = false;
		master_position = Enums::PositionMaster::WINDOW;
		position_mode_x = Enums::PositionMode::RIGHT;
		position_mode_y = Enums::PositionMode::UP;

	}


	if (button_type == Enums::ButtonType::SLIDER_LOOT_DROP_SIZE)
	{
		gabarite = DefaultGabarite::gabarite_slider_value;
		master_position = Enums::PositionMaster::WINDOW;

		position_mode_x = Enums::PositionMode::LEFT;
		position_mode_y = Enums::PositionMode::UP;

		slider_value =1.0f;
	}
	is_slider = true;
	//is_holdable = true;

	have_text = false;

	icon_adaptation = false;

	

}

void EButtonSlider::click_event()
{
}

 void EButtonSlider::slide_drag_event()
{
	 if (button_type == Enums::ButtonType::BUTTON_BG_H)
	 {
		 master_block->is_bg_color_active = true;

		 master_block->bg_hue = slider_value * 360.0f;
		 FilterBlock::change_color_extract(master_block);

		 description_text = cached_text_hue + std::to_string((int)round(slider_value * 360.0f));
	 }

	if (button_type == Enums::ButtonType::BUTTON_BG_S)
	{
		master_block->is_bg_color_active = true;

		 master_block->bg_saturation = slider_value;
		 FilterBlock::change_color_extract(master_block);

		 description_text = cached_text_saturation + std::to_string((int)round(slider_value * 100.0f)) + "%";
	}

	 if (button_type == Enums::ButtonType::BUTTON_BG_V)
	 {
		 master_block->is_bg_color_active = true;

		 master_block->bg_value = slider_value*255.0;
		FilterBlock::change_color_extract(master_block);

		description_text = cached_text_brightness + std::to_string((int)round(slider_value * 100.0f)) + "%";
	 }

	 if (button_type == Enums::ButtonType::BUTTON_BG_ALPHA)
	 {
		 master_block->is_bg_color_active = true;

		 master_block->bg_alpha = slider_value*255.0;
		 FilterBlock::change_color_extract(master_block);

		 description_text = cached_text_alpha + std::to_string((int)round(slider_value * 100.0f)) + "%";
	 }

	 //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	 if (button_type == Enums::ButtonType::BUTTON_TEXT_H)
	 {
		 master_block->is_text_color_active = true;

		 master_block->text_color_hue = slider_value * 360.0;
		 FilterBlock::change_color_extract(master_block);

		 description_text = cached_text_hue + std::to_string((int)round(slider_value * 360.0f));
	 }

	 if (button_type == Enums::ButtonType::BUTTON_TEXT_S)
	 {
		 master_block->is_text_color_active = true;

		 master_block->text_color_saturation = slider_value;
		 FilterBlock::change_color_extract(master_block);

		 description_text = cached_text_saturation + std::to_string((int)round(slider_value * 100.0f)) + "%";
	 }

	 if (button_type == Enums::ButtonType::BUTTON_TEXT_V)
	 {
		 master_block->is_text_color_active = true;

		 master_block->text_color_value = slider_value*255.0;
		 FilterBlock::change_color_extract(master_block);

		 description_text = cached_text_brightness + std::to_string((int)round(slider_value * 100.0f)) + "%";
	 }

	 if (button_type == Enums::ButtonType::BUTTON_TEXT_ALPHA)
	 {
		 master_block->is_text_color_active = true;

		 master_block->text_color_alpha = slider_value*255.0;
		 FilterBlock::change_color_extract(master_block);

		 description_text = cached_text_alpha + std::to_string((int)round(slider_value * 100.0f)) + "%";
	 }

	 //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	 if (button_type == Enums::ButtonType::BUTTON_RAMA_H)
	 {
		 master_block->is_rama_color_active = true;

		 master_block->rama_hue = slider_value * 360.0;
		 FilterBlock::change_color_extract(master_block);

		 description_text = cached_text_hue + std::to_string((int)round(slider_value * 360.0f));
	 }

	 if (button_type == Enums::ButtonType::BUTTON_RAMA_S)
	 { 
		master_block->is_rama_color_active = true; 

		master_block->rama_saturation = slider_value;
		FilterBlock::change_color_extract(master_block);
		
		description_text = cached_text_saturation + std::to_string((int)round(slider_value * 100.0f)) + "%";
	 }

	 if (button_type == Enums::ButtonType::BUTTON_RAMA_V)
	 {
		master_block->is_rama_color_active = true;

		master_block->rama_value = slider_value*255.0;
		FilterBlock::change_color_extract(master_block);

		description_text = cached_text_brightness + std::to_string((int)round(slider_value * 100.0f)) + "%";

	 }

	 if (button_type == Enums::ButtonType::BUTTON_RAMA_ALPHA)
	 {
		master_block->is_rama_color_active = true;

		 master_block->rama_alpha = slider_value*255.0;
		FilterBlock::change_color_extract(master_block);

		description_text = cached_text_alpha + std::to_string((int)round(slider_value * 100.0f)) + "%";
	 }


	 if (button_type == Enums::ButtonType::BUTTON_SLIDER_FONT_SIZE)
	 {
		 master_block->is_font_size_active = true;

		 master_block->font_size = round(18.0 + slider_value * 27.0f);

		 description_text = cached_text_font_size + std::to_string(master_block->font_size);

		 if (StaticData::window_loot_simulator->is_active)
		 {
			for (int i = 0; i < 87; i++)
			for (int j = 0; j < 125; j++)
			{
				 StaticData::window_loot_simulator->free_space[j][i] = true;
			}

			for (LootItem* _l : StaticData::window_loot_simulator->main_loot_item_list)
			{
				StaticData::window_loot_simulator->place(_l);
			}
		 }

	 }

	 if (button_type == Enums::ButtonType::BUTTON_GLOBAL_DROP_SOUND_VOLUME)
	 {
		 StaticData::window_filter_block->sound_volume = slider_value * slider_value;

		 description_text = cached_text_sound_volume + std::to_string((int)round(slider_value * 100.0f)) + "%";
	 }

	 if (button_type == Enums::ButtonType::BUTTON_FILTER_BLOCK_SCROLL)
	 {
		 int active_block_count = 0;

		 for (FilterBlock* fb:StaticData::window_filter_block->filter_block_list)
		 {
			 if (!fb->is_deactivated) { active_block_count++; }
		 }

		 EControl::block_scroll = round(slider_value * active_block_count - 5.0f);
		 if (EControl::block_scroll < 0) { EControl::block_scroll = 0; }


		 description_text = cached_text_scroll + std::to_string(EControl::block_scroll);
		 //description_text = "List size=" + std::to_string(StaticData::window_filter_block->filter_block_list.size()) + " scroll value=" + std::to_string(EControl::block_scroll) + " slider value=" + std::to_string(slider_value);
	 }


	 if (button_type == Enums::ButtonType::SLIDER_LOOT_DROP_SIZE)
	 {

		 description_text = std::to_string(round (slider_value * 100.0f))+"%";

		 if (StaticData::window_loot_simulator->is_active)
		 {

			StaticData::window_loot_simulator->font_scale_factor = slider_value;

			for (int i = 0; i < 87; i++)
			for (int j = 0; j < 125; j++)
			{
				StaticData::window_loot_simulator->free_space[j][i] = true;
			}

			for (LootItem* _l : StaticData::window_loot_simulator->main_loot_item_list)
			{
				StaticData::window_loot_simulator->place(_l);
			}
		 }

	 }

	 /*
	 std::cout << "===============================" << std::endl;

	 std::cout << "bg hue			" << master_block->bg_hue << std::endl;
	 std::cout << "b saturation		" << master_block->bg_saturation << std::endl;
	 std::cout << "bg value			" << master_block->bg_value << std::endl;
	 std::cout << "-" << std::endl;*/
}

 void EButtonSlider::update_additional(float _d)
 {
	 if (button_type == Enums::ButtonType::BUTTON_FILTER_BLOCK_SCROLL)
	 {button_size_y = EWindow::SCR_HEIGHT - 80.0f;}
 }

 void EButtonSlider::update_localisation()
 {
	 cached_text_hue =				EString::localize_it("text_hue");
	 cached_text_saturation =		EString::localize_it("text_saturation");;
	 cached_text_brightness =		EString::localize_it("text_brightness");;
	 cached_text_alpha =			EString::localize_it("text_alpha");;
	 cached_text_font_size =		EString::localize_it("text_font_size");;
	 cached_text_sound_volume =		EString::localize_it("text_sound_volume");;
	 cached_text_scroll =			EString::localize_it("text_scroll");;

	 if (button_type == Enums::ButtonType::BUTTON_FILTER_BLOCK_SCROLL)
	 {
		 description_text = EString::localize_it("description_scroll");;
	 }
 }
