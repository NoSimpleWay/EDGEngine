#pragma once
#include "EButtonService.h"

#include "EWindow.h"
#include "EControl.h"
#include "Enums.h"
#include "FilterBlock.h"
#include "EButtonSlider.h"
#include "EButtonText.h"
#include "EUtils.h"
#include "EButtonCheck.h"


class EWindowFilterVisualEditor: public EWindow
{
public:
	//std::vector<FilterBlock*> filter_block_list;
	FilterBlock* master_block;

	float default_positiox_x=15.0;
	float default_positiox_y=315.0;
	
	float distance_between_x=350.0;
	float distance_between_y=20.0f;

	float button_size_x = 150.0f;

	float icon_button_base_x = 625.0f;
	float icon_button_base_y = 5.0f;

	std::vector<EButton*> link_to_sliders;

	std::vector<EButton*> link_to_icon_shape;
	std::vector<EButton*> link_to_icon_color;
	std::vector<EButton*> link_to_icon_size;

	EButton* link_to_icon_checker;
	


	void set_button_data(EButton* _b)
	{
		_b->master_window = this;
		_b->master_block = master_block;

		button_list.push_back(_b);
		link_to_sliders.push_back(_b);


		

		align_x = Enums::PositionMode::MID;
		align_y = Enums::PositionMode::MID;
	}

	EWindowFilterVisualEditor(int _id) :EWindow(_id)
	{
		pos_x = 0;
		pos_y = 0;

		window_size_x = 1000;
		window_size_y = 600;

		align_x = Enums::PositionMode::LEFT;
		align_y = Enums::PositionMode::DOWN;

		is_active = false;
		have_bg = true;

		set_button_data(new EButtonSlider(default_positiox_x + distance_between_x * 0.0f, default_positiox_y + distance_between_y * 3.0f, button_size_x, 17.0f, Enums::BUTTON_BG_H));
		set_button_data(new EButtonSlider(default_positiox_x + distance_between_x * 0.0f, default_positiox_y + distance_between_y * 2.0f, button_size_x, 17.0f, Enums::BUTTON_BG_S));
		set_button_data(new EButtonSlider(default_positiox_x + distance_between_x * 0.0f, default_positiox_y + distance_between_y * 1.0f, button_size_x, 17.0f, Enums::BUTTON_BG_V));
		set_button_data(new EButtonSlider(default_positiox_x + distance_between_x * 0.0f, default_positiox_y + distance_between_y * 0.0f, button_size_x, 17.0f, Enums::BUTTON_BG_ALPHA));

		set_button_data(new EButtonSlider(default_positiox_x + distance_between_x * 1.0f, default_positiox_y + distance_between_y * 3.0f, button_size_x, 17.0f, Enums::BUTTON_TEXT_H));
		set_button_data(new EButtonSlider(default_positiox_x + distance_between_x * 1.0f, default_positiox_y + distance_between_y * 2.0f, button_size_x, 17.0f, Enums::BUTTON_TEXT_S));
		set_button_data(new EButtonSlider(default_positiox_x + distance_between_x * 1.0f, default_positiox_y + distance_between_y * 1.0f, button_size_x, 17.0f, Enums::BUTTON_TEXT_V));
		set_button_data(new EButtonSlider(default_positiox_x + distance_between_x * 1.0f, default_positiox_y + distance_between_y * 0.0f, button_size_x, 17.0f, Enums::BUTTON_TEXT_ALPHA));

		set_button_data(new EButtonSlider(default_positiox_x + distance_between_x * 2.0f, default_positiox_y + distance_between_y * 3.0f, button_size_x, 17.0f, Enums::BUTTON_RAMA_H));
		set_button_data(new EButtonSlider(default_positiox_x + distance_between_x * 2.0f, default_positiox_y + distance_between_y * 2.0f, button_size_x, 17.0f, Enums::BUTTON_RAMA_S));
		set_button_data(new EButtonSlider(default_positiox_x + distance_between_x * 2.0f, default_positiox_y + distance_between_y * 1.0f, button_size_x, 17.0f, Enums::BUTTON_RAMA_V));
		set_button_data(new EButtonSlider(default_positiox_x + distance_between_x * 2.0f, default_positiox_y + distance_between_y * 0.0f, button_size_x, 17.0f, Enums::BUTTON_RAMA_ALPHA));

		EButton* but = new EButtonText(60, 50, 220, 40, Enums::ButtonType::BUTTON_OPEN_DEFAULT_DROP_SOUND_WINDOW);
		but->master_window = this;
		but->master_block = master_block;
		button_list.push_back(but);

		but = new EButtonText(60, 5, 220, 40, Enums::ButtonType::BUTTON_OPEN_CUSTOM_DROP_SOUND_WINDOW);
		but->master_window = this;
		but->master_block = master_block;
		button_list.push_back(but);

		EMath::rgb target_color;

		target_color.r = 255.0 / 255.0;
		target_color.g = 0.0 / 255.0;
		target_color.b = 0.0 / 255.0;

		EMath::hsv changed_color;

		changed_color = EMath::rgb2hsv(target_color);

		std::cout << "H: " << changed_color.h << " S: " << changed_color.s << " V: " << changed_color.v << std::endl;

		bg_color->set(0.1f, 0.2f, 0.3f, 0.95f);


		for (int i = 0; i < 6; i++)
		{
			but = new EButtonService(icon_button_base_x + 55.0f * i, icon_button_base_y+60.0*2.0f, 45.0f, 45.0f, Enums::ButtonType::BUTTON_MINIMAP_ICON_SELECT_SHAPE);
			but->gabarite = DefaultGabarite::gabarite_minimap_icon[i];
			but->data_id = i;

			but->master_block = master_block;
			but->master_window = this;

			link_to_icon_shape.push_back(but);
			button_list.push_back(but);



			but = new EButtonService(icon_button_base_x + 55.0f * i, icon_button_base_y + 60.0 * 1.0f, 45.0f, 45.0f, Enums::ButtonType::BUTTON_MINIMAP_ICON_SELECT_COLOR);
			but->gabarite = DefaultGabarite::gabarite_minimap_icon[i];
			but->data_id = i;

			but->master_block = master_block;
			but->master_window = this;

			link_to_icon_color.push_back(but);
			button_list.push_back(but);
		}

		for (int i = 0; i < 3; i++)
		{
			but = new EButtonText(icon_button_base_x + 110.0f * i, icon_button_base_y + 60.0 * 0.0f, 90.0f, 45.0f, Enums::ButtonType::BUTTON_MINIMAP_ICON_SELECT_SIZE);
			
			but->data_id = i;

			but->master_block = master_block;
			but->master_window = this;

			link_to_icon_size.push_back(but);
			button_list.push_back(but);
		}

		link_to_icon_size.at(0)->text = "Big";
		link_to_icon_size.at(1)->text = "Medium";
		link_to_icon_size.at(2)->text = "Small";

		but =new EButtonCheck(icon_button_base_x + 110.0f, icon_button_base_y + 60.0 * 3.0f, 30.0f, 30.0f, Enums::ButtonType::BUTTON_CHECKER_MINIMAP_ICON);
		but->master_block = master_block;
		but->master_window = this;
		but->master_position = Enums::PositionMaster::WINDOW;

		but->position_mode_x = Enums::PositionMode::LEFT;
		but->position_mode_y = Enums::PositionMode::DOWN;

		link_to_icon_checker = but;
		button_list.push_back(but);
	}

	void update_minimap_button()
	{
		for (int i = 0; i < 6; i++)
		{
			link_to_icon_shape.at(i)->bg_color->set(0.4f, 0.3f, 0.2f, 0.4f);
			link_to_icon_shape.at(i)->icon_color->set(EColorCollection::WHITE);

			link_to_icon_shape.at(i)->rama_color->set_alpha(EColorCollection::BLACK, 0.75f);

			link_to_icon_shape.at(i)->rama_thikness = 1;

			if (i == master_block->minimap_icon_shape)
			{
				link_to_icon_shape.at(i)->rama_color->set_alpha(EColorCollection::YELLOW, 0.90f);
				link_to_icon_shape.at(i)->rama_thikness = 4;
			}
		}

		for (int i = 0; i < 6; i++)
		{
			link_to_icon_color.at(i)->bg_color->set(0.4f, 0.3f, 0.2f, 0.4f);

			link_to_icon_color.at(i)->rama_color->set_alpha(EColorCollection::BLACK, 0.75f);
			link_to_icon_color.at(i)->icon_color->set(EColorCollection::MINIMAP_ICON_COLOR[i]);
			link_to_icon_color.at(i)->rama_thikness = 1;
			link_to_icon_color.at(i)->gabarite = DefaultGabarite::gabarite_minimap_icon[master_block->minimap_icon_shape];

			if (i == master_block->minimap_icon_color)
			{
				link_to_icon_color.at(i)->rama_color->set_alpha(EColorCollection::YELLOW, 0.90f);
				link_to_icon_color.at(i)->rama_thikness = 4;
			}
		}

		for (int i = 0; i < 3; i++)
		{
			link_to_icon_size.at(i)->bg_color->set(0.4f, 0.3f, 0.2f, 0.4f);

			link_to_icon_size.at(i)->rama_color->set_alpha(EColorCollection::BLACK, 0.75f);
			link_to_icon_size.at(i)->rama_thikness = 1;

			if (i == master_block->minimap_icon_size)
			{
				link_to_icon_size.at(i)->rama_color->set_alpha(EColorCollection::YELLOW, 0.90f);
				link_to_icon_size.at(i)->rama_thikness = 4;
			}
		}
	}

	void deactivate_minimap_button()
	{
		for (int i = 0; i < 6; i++)
		{
			
			link_to_icon_shape.at(i)->rama_color->set_alpha(EColorCollection::BLACK, 0.75f);
			link_to_icon_shape.at(i)->rama_thikness = 1;
			link_to_icon_shape.at(i)->icon_color->set_alpha(EColorCollection::GRAY, 0.55f);
			link_to_icon_shape.at(i)->bg_color->set_alpha(EColorCollection::GRAY, 0.35f);
		}

		for (int i = 0; i < 6; i++)
		{
			
			link_to_icon_color.at(i)->rama_color->set_alpha(EColorCollection::BLACK, 0.75f);
			
			link_to_icon_color.at(i)->icon_color->set_alpha(EColorCollection::GRAY, 0.55f);
			link_to_icon_color.at(i)->bg_color->set_alpha(EColorCollection::GRAY, 0.35f);

			link_to_icon_color.at(i)->rama_thikness = 1;
			link_to_icon_color.at(i)->gabarite = DefaultGabarite::gabarite_minimap_icon[master_block->minimap_icon_shape];
		}

		for (int i = 0; i < 3; i++)
		{

			link_to_icon_size.at(i)->rama_color->set_alpha(EColorCollection::BLACK, 0.75f);
			link_to_icon_size.at(i)->rama_thikness = 1;

			link_to_icon_size.at(i)->icon_color->set_alpha(EColorCollection::GRAY, 0.55f);
			link_to_icon_size.at(i)->bg_color->set_alpha(EColorCollection::GRAY, 0.35f);
			
		}
	}

	virtual void draw(Batcher* _batch, float _delta)
	{
		EFont::font_arial->align_x = Enums::PositionMode::LEFT;
		_batch->setcolor(EColorCollection::WHITE);
		_batch->draw_rect_with_uv(pos_x + default_positiox_x + distance_between_x * 1.0f + (button_size_x - 320.0f) / 2.0f, default_positiox_y+pos_y + distance_between_y * 4.0f + 100.0f + (25.0f - 150.0f) / 2.0f, 320, 150, DefaultGabarite::gabarite_visual_editor_bg);

		_batch->setcolor_255(master_block->bg_red, master_block->bg_green, master_block->bg_blue, master_block->bg_alpha / 2.55f);
		_batch->draw_rect_with_uv(pos_x+default_positiox_x + distance_between_x * 1.0f, default_positiox_y + pos_y + distance_between_y * 4.0f+100.0f, button_size_x, 25.0f, DefaultGabarite::gabarite_white);

		_batch->setcolor_255(master_block->text_color_red, master_block->text_color_green, master_block->text_color_blue, master_block->text_color_alpha / 2.55f);
		EFont::font_arial->draw(_batch,"Sample text", round(pos_x + default_positiox_x + distance_between_x * 1.0f+(button_size_x -EFont::get_width(EFont::font_arial,"Sample text"))/2.0f), default_positiox_y + pos_y + distance_between_y * 4.0f+100.0f+10.0f);

		_batch->setcolor_255(master_block->rama_red, master_block->rama_green, master_block->rama_blue, master_block->rama_alpha / 2.55f);
		_batch->draw_rama(pos_x + default_positiox_x + distance_between_x * 1.0f, default_positiox_y + pos_y + distance_between_y * 4.0f+100.0f, button_size_x, 25.0f, 3, DefaultGabarite::gabarite_white);
	}

	virtual void text_pass(Batcher* _batch)
	{
		
	}

	virtual void button_event(EButton* _b)
	{
		master_block = _b->master_block;

		update_minimap_button();

		for (EButton* b : link_to_sliders)
		{
			b->master_block = _b->master_block;
		}

		for (EButton* b : button_list)
		{
			b->master_block = _b->master_block;
		}

		link_to_sliders.at(0)->slider_value = master_block->bg_hue / 360.0f;
		link_to_sliders.at(1)->slider_value = EMath::clamp_value_float(master_block->bg_saturation / 1.0f,0.01f,0.99f);
		link_to_sliders.at(2)->slider_value = master_block->bg_value / 255.0f;
		link_to_sliders.at(3)->slider_value = master_block->bg_alpha/255.0f;
		
		link_to_sliders.at(4)->slider_value = master_block->text_color_hue / 360.0f;
		link_to_sliders.at(5)->slider_value = EMath::clamp_value_float(master_block->text_color_saturation / 1.0f, 0.01f, 0.99f);
		link_to_sliders.at(6)->slider_value = master_block->text_color_value / 255.0f;
		link_to_sliders.at(7)->slider_value = master_block->text_color_alpha/255.0f;		

		link_to_sliders.at(8)->slider_value = master_block->rama_hue / 360.0f;
		link_to_sliders.at(9)->slider_value = EMath::clamp_value_float(master_block->rama_saturation / 1.0f, 0.01f, 0.99f);
		link_to_sliders.at(10)->slider_value = master_block->rama_value / 255.0f;
		link_to_sliders.at(11)->slider_value = master_block->rama_alpha/255.0f;


		//std::cout << "standart window button event" << std::endl;
	}

};