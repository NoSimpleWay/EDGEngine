#pragma once
#include "EButtonService.h"
#include "EWindowFilterVisualEditor.h"

#include "EWindow.h"
#include "EControl.h"
#include "Enums.h"
#include "FilterBlock.h"
#include "EButtonSlider.h"
#include "EButtonText.h"
#include "EUtils.h"
#include "EButtonCheck.h"
#include "StaticData.h"




	


	void EWindowFilterVisualEditor::set_button_data(EButton* _b)
	{
		_b->master_window = this;
		_b->master_block = master_block;

		button_list.push_back(_b);
		link_to_sliders.push_back(_b);


		

		align_x = Enums::PositionMode::MID;
		align_y = Enums::PositionMode::MID;
	}

	EWindowFilterVisualEditor::EWindowFilterVisualEditor(int _id, bool _can_be_closed):EWindow(_id, _can_be_closed)
	{
		pos_x = 0;
		pos_y = 0;

		window_size_x = 970;
		window_size_y = 600;

		align_x = Enums::PositionMode::LEFT;
		align_y = Enums::PositionMode::DOWN;

		is_active = false;
		have_bg = true;

		set_button_data(new EButtonSlider(default_position_x + distance_between_x * 0.0f, default_position_y + distance_between_y * 3.0f, button_size_x, 17.0f, Enums::BUTTON_BG_H));
		set_button_data(new EButtonSlider(default_position_x + distance_between_x * 0.0f, default_position_y + distance_between_y * 2.0f, button_size_x, 17.0f, Enums::BUTTON_BG_S));
		set_button_data(new EButtonSlider(default_position_x + distance_between_x * 0.0f, default_position_y + distance_between_y * 1.0f, button_size_x, 17.0f, Enums::BUTTON_BG_V));
		set_button_data(new EButtonSlider(default_position_x + distance_between_x * 0.0f, default_position_y + distance_between_y * 0.0f, button_size_x, 17.0f, Enums::BUTTON_BG_ALPHA));

		set_button_data(new EButtonSlider(default_position_x + distance_between_x * 1.0f, default_position_y + distance_between_y * 3.0f, button_size_x, 17.0f, Enums::BUTTON_TEXT_H));
		set_button_data(new EButtonSlider(default_position_x + distance_between_x * 1.0f, default_position_y + distance_between_y * 2.0f, button_size_x, 17.0f, Enums::BUTTON_TEXT_S));
		set_button_data(new EButtonSlider(default_position_x + distance_between_x * 1.0f, default_position_y + distance_between_y * 1.0f, button_size_x, 17.0f, Enums::BUTTON_TEXT_V));
		set_button_data(new EButtonSlider(default_position_x + distance_between_x * 1.0f, default_position_y + distance_between_y * 0.0f, button_size_x, 17.0f, Enums::BUTTON_TEXT_ALPHA));

		set_button_data(new EButtonSlider(default_position_x + distance_between_x * 2.0f, default_position_y + distance_between_y * 3.0f, button_size_x, 17.0f, Enums::BUTTON_RAMA_H));
		set_button_data(new EButtonSlider(default_position_x + distance_between_x * 2.0f, default_position_y + distance_between_y * 2.0f, button_size_x, 17.0f, Enums::BUTTON_RAMA_S));
		set_button_data(new EButtonSlider(default_position_x + distance_between_x * 2.0f, default_position_y + distance_between_y * 1.0f, button_size_x, 17.0f, Enums::BUTTON_RAMA_V));
		set_button_data(new EButtonSlider(default_position_x + distance_between_x * 2.0f, default_position_y + distance_between_y * 0.0f, button_size_x, 17.0f, Enums::BUTTON_RAMA_ALPHA));

		set_button_data(new EButtonSlider(default_position_x + distance_between_x * 3.0f, default_position_y + distance_between_y * 3.0f, button_size_x, 17.0f, Enums::BUTTON_SLIDER_FONT_SIZE));

		EButton* but = new EButtonText(5, 50, 220, 40, Enums::ButtonType::BUTTON_OPEN_DEFAULT_DROP_SOUND_WINDOW);
		but->master_window = this;
		but->master_block = master_block;
		but->master_position = Enums::PositionMaster::WINDOW;
		but->text_align_x = Enums::PositionMode::MID;
		button_list.push_back(but);

		but = new EButtonText(5, 5, 220, 40, Enums::ButtonType::BUTTON_OPEN_CUSTOM_DROP_SOUND_WINDOW);
		but->master_window = this;
		but->master_block = master_block;
		button_list.push_back(but);

		EMath::rgb target_color;

		target_color.r = 255.0 / 255.0;
		target_color.g = 0.0 / 255.0;
		target_color.b = 0.0 / 255.0;

		EMath::hsv changed_color;

		changed_color = EMath::rgb2hsv(target_color);

		//std::cout << "H: " << changed_color.h << " S: " << changed_color.s << " V: " << changed_color.v << std::endl;

		bg_color->set(0.60f, 0.7f, 0.75f, 0.80f);

		for (int j = 0; j < 2; j++)
		for (int i = 0; i < 6; i++)
		{
			but = new EButtonService(icon_button_base_x + 55.0f * i, icon_button_base_y+90.0*2.0f - 50.0f * j, 45.0f, 45.0f, Enums::ButtonType::BUTTON_MINIMAP_ICON_SELECT_SHAPE);
			but->gabarite = DefaultGabarite::gabarite_minimap_icon[i + j * 6];
			but->data_id = i + j * 6;

			but->master_block = master_block;
			but->master_window = this;

			link_to_icon_shape.push_back(but);
			button_list.push_back(but);
			



		}

		for (int i = 0; i < 10; i++)
		{
			but = new EButtonService(icon_button_base_x + 32.0f * i, icon_button_base_y + 55.0 * 1.0f, 29.0f, 29.0f, Enums::ButtonType::BUTTON_MINIMAP_ICON_SELECT_COLOR);
			but->gabarite = DefaultGabarite::gabarite_minimap_icon[i];
			but->data_id = i;

			but->master_block = master_block;
			but->master_window = this;

			link_to_icon_color.push_back(but);
			button_list.push_back(but);
		}

		for (int i = 0; i < 3; i++)
		{
			but = new EButtonText(icon_button_base_x + 110.0f * i, icon_button_base_y + 60.0 * 0.0f, 105.0f, 45.0f, Enums::ButtonType::BUTTON_MINIMAP_ICON_SELECT_SIZE);
			
			but->data_id = i;

			but->master_block = master_block;
			but->master_window = this;
			but->text_color = EColorCollection::WHITE;

			link_to_icon_size.push_back(but);
			button_list.push_back(but);
		}

		but =new EButtonCheck(icon_button_base_x + 110.0f * 0.0f, icon_button_base_y + 80.0 * 3.0f, 25.0f, 25.0f, Enums::ButtonType::BUTTON_CHECKER_MINIMAP_ICON);
		but->master_block = master_block;
		but->master_window = this;
		but->master_position = Enums::PositionMaster::WINDOW;

		but->position_mode_x = Enums::PositionMode::LEFT;
		but->position_mode_y = Enums::PositionMode::DOWN;

		link_to_icon_checker = but;
		button_list.push_back(but);

		for (int j = 0; j < 2; j++)
		for (int i = 0; i < 6; i++)
		{
			but = new EButtonService(255.0f + (i)*49.0f, icon_button_base_y + 25.0f + j * 65.0f, 30.0f, 60.0f, Enums::ButtonType::BUTTON_SELECT_RAY_COLOR);

			but->bg_color->set(0.2f, 0.2f, 0.2f, 0.8f);

			if (i + j * 6 > 0)
			{
				but->icon_color->set(EColorCollection::MINIMAP_RAY_COLOR[i + j * 6 - 1]);

				but->gabarite = DefaultGabarite::gabarite_ray_icon;
			}
			else
			{
				but->icon_color->set(EColorCollection::WHITE);
				but->gabarite = DefaultGabarite::gabarite_ray_icon_remove;
			}

			but->rama_color->set_alpha(EColorCollection::BLACK, 0.75f);

			but->data_id = i + j * 6 - 1;

			but->master_block = master_block;
			but->master_window = this;

			but->master_position = Enums::PositionMaster::WINDOW;
			but->position_mode_x = Enums::PositionMode::LEFT;
			but->position_mode_y = Enums::PositionMode::DOWN;

			link_to_ray_color.push_back(but);
			button_list.push_back(but);
		}

		but = new EButtonText(255.0f, icon_button_base_y + 0.0f, 135.0f, 20.0f, Enums::ButtonType::BUTTON_SET_RAY_IS_TEMPOTARY);
		but->master_window = this;
		but->bg_color->set(0.2f, 0.2f, 0.2f, 0.8f);
		but->master_block = master_block;
		but->text_color = EColorCollection::WHITE;

		but->master_position = Enums::PositionMaster::WINDOW;
		but->position_mode_x = Enums::PositionMode::LEFT;
		but->position_mode_y = Enums::PositionMode::DOWN;

		button_list.push_back(but);
		link_to_ray_tempotary = but;


		but = new EButtonText(395.0f, icon_button_base_y + 0.0f, 135.0f, 20.0f, Enums::ButtonType::BUTTON_SET_RAY_IS_CONSTANT);
		but->master_window = this;
		but->bg_color->set(0.2f, 0.2f, 0.2f, 0.8f);
		but->master_block = master_block;
		but->master_window = this;
		but->text_color = EColorCollection::WHITE;

		but->master_position = Enums::PositionMaster::WINDOW;
		but->position_mode_x = Enums::PositionMode::LEFT;
		but->position_mode_y = Enums::PositionMode::DOWN;

		button_list.push_back(but);
		link_to_ray_constant = but;
	}

	void EWindowFilterVisualEditor::update_ray_button()
	{
			for (int i = 0; i < 12; i++)
			{
				link_to_ray_color.at(i)->rama_color->set_alpha(EColorCollection::BLACK, 0.75f);
				link_to_ray_color.at(i)->bg_color->set(0.4f, 0.3f, 0.2f, 0.4f);

				if (i - 1 >= 0)
				{
					link_to_ray_color.at(i)->icon_color->set(EColorCollection::MINIMAP_RAY_COLOR[i - 1]);
				}
				else
				{
					link_to_ray_color.at(i)->icon_color->set(EColorCollection::WHITE);
					link_to_ray_color.at(i)->gabarite = DefaultGabarite::gabarite_ray_icon_remove;
				}

				link_to_ray_color.at(i)->rama_thikness = 2.0f;

				if ((master_block->is_ray) && (master_block->ray_color == i - 1))
				{
					link_to_ray_color.at(i)->rama_color->set_alpha(EColorCollection::YELLOW, 0.90f);
				}

				if ((i == 0) && (!master_block->is_ray))
				{
					link_to_ray_color.at(i)->rama_color->set_alpha(EColorCollection::YELLOW, 0.90f);
				}
			}

			if (master_block->ray_is_temp)
			{
				link_to_ray_constant->rama_color->set_alpha(EColorCollection::BLACK, 0.75f);
				link_to_ray_constant->bg_color->set(0.4f, 0.3f, 0.2f, 0.4f);

				link_to_ray_tempotary->rama_color->set_alpha(EColorCollection::YELLOW, 0.90f);
				link_to_ray_tempotary->bg_color->set(0.5f, 0.5f, 0.2f, 0.4f);
			}
			else
			{
				link_to_ray_constant->rama_color->set_alpha(EColorCollection::YELLOW, 0.90f);
				link_to_ray_constant->bg_color->set(0.5f, 0.5f, 0.2f, 0.4f);

				link_to_ray_tempotary->rama_color->set_alpha(EColorCollection::BLACK, 0.75f);
				link_to_ray_tempotary->bg_color->set(0.4f, 0.3f, 0.2f, 0.4f);
			}
		
		/*
		{
			for (int i = 0; i < 7; i++)
			{
				link_to_ray_color.at(i)->rama_thikness = 1.0f;
				link_to_ray_color.at(i)->rama_color->set_alpha(EColorCollection::BLACK, 0.5f);
				link_to_ray_color.at(i)->bg_color->set_alpha(EColorCollection::GRAY, 0.35f);
				link_to_ray_color.at(i)->icon_color->set_alpha(EColorCollection::GRAY, 0.50f);
			}
		}*/
	}

	void EWindowFilterVisualEditor::update_minimap_button()
	{
		for (int i = 0; i < 12; i++)
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

		for (int i = 0; i < 10; i++)
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

	void EWindowFilterVisualEditor::deactivate_minimap_button()
	{
		for (int i = 0; i < 12; i++)
		{
			
			link_to_icon_shape.at(i)->rama_color->set_alpha(EColorCollection::BLACK, 0.75f);
			link_to_icon_shape.at(i)->rama_thikness = 1;
			link_to_icon_shape.at(i)->icon_color->set_alpha(EColorCollection::GRAY, 0.55f);
			link_to_icon_shape.at(i)->bg_color->set_alpha(EColorCollection::GRAY, 0.35f);
		}

		for (int i = 0; i < 10; i++)
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

	void EWindowFilterVisualEditor::draw(Batcher* _batch, float _delta)
	{
		EFont::active_font->scale = master_block->font_size / 32.0f;

		float text_w = EFont::get_width(EFont::active_font, "Sample text");
		float text_h = 20.0f * master_block->font_size / 32.0f;

		float rx = text_w + 10.0f;
		float ry = text_h + 6.0F;

		EFont::active_font->align_x = Enums::PositionMode::LEFT;
		_batch->setcolor(EColorCollection::WHITE);
		_batch->draw_rect_with_uv(pos_x + default_position_x + distance_between_x * 1.0f + (button_size_x - 320.0f) / 2.0f, default_position_y+pos_y + distance_between_y * 4.0f + 100.0f + (25.0f - 150.0f) / 2.0f, 320, 150, DefaultGabarite::gabarite_visual_editor_bg);

		_batch->setcolor_255(master_block->bg_red, master_block->bg_green, master_block->bg_blue, master_block->bg_alpha / 2.55f);
		_batch->draw_rect_with_uv
		(
			pos_x+default_position_x + distance_between_x * 1.0f + (button_size_x - rx)/2.0f,
			default_position_y + pos_y + distance_between_y * 4.0f+100.0f,

			rx,
			ry,

			DefaultGabarite::gabarite_white
		);

		

		_batch->setcolor_255(master_block->text_color_red, master_block->text_color_green, master_block->text_color_blue, master_block->text_color_alpha / 2.55f);
		EFont::active_font->draw
		(
			_batch,
			"Sample text",

			round(pos_x + default_position_x + distance_between_x * 1.0f+(button_size_x -EFont::get_width(EFont::active_font,"Sample text"))/2.0f),
			default_position_y + pos_y + distance_between_y * 4.0f+100.0f+7.0f
		);

		_batch->setcolor_255(master_block->rama_red, master_block->rama_green, master_block->rama_blue, master_block->rama_alpha / 2.55f);
		_batch->draw_rama
		(
			pos_x + default_position_x + distance_between_x * 1.0f + (button_size_x - rx) / 2.0f,
			default_position_y + pos_y + distance_between_y * 4.0f + 100.0f,

			rx,
			ry,

			3,

			DefaultGabarite::gabarite_white
		);

		_batch->setcolor_alpha(EColorCollection::BLACK, 0.2f);
		_batch->draw_rama(pos_x + default_position_x + distance_between_x * 0.0f - 5.0f, /**/ pos_y + default_position_y - 5.0f, /**/ button_size_x + 10.0f, /**/ distance_between_y * 4.0f + 22.0f, /**/ 2.0f, /**/ DefaultGabarite::gabarite_white);
		_batch->draw_rama(pos_x + default_position_x + distance_between_x * 1.0f - 5.0f, /**/ pos_y + default_position_y - 5.0f, /**/ button_size_x + 10.0f, /**/ distance_between_y * 4.0f + 22.0f, /**/ 2.0f, /**/ DefaultGabarite::gabarite_white);
		_batch->draw_rama(pos_x + default_position_x + distance_between_x * 2.0f - 5.0f, /**/ pos_y + default_position_y - 5.0f, /**/ button_size_x + 10.0f, /**/ distance_between_y * 4.0f + 22.0f, /**/ 2.0f, /**/ DefaultGabarite::gabarite_white);
		_batch->draw_rama(pos_x + default_position_x + distance_between_x * 3.0f - 5.0f, /**/ pos_y + default_position_y - 5.0f, /**/ button_size_x + 10.0f, /**/ distance_between_y * 4.0f + 22.0f, /**/ 2.0f, /**/ DefaultGabarite::gabarite_white);

		EFont::active_font->scale = 1.0f;
		_batch->setcolor(EColorCollection::LIGHT_GRAY);
		EFont::active_font->align_x = Enums::PositionMode::MID;

		EFont::active_font->draw(_batch, cached_text_bg_color,		pos_x + default_position_x + distance_between_x * 0.0f + button_size_x / 2.0f, pos_y + default_position_y + distance_between_y * 4.0f + 3.0f);
		EFont::active_font->draw(_batch, cached_text_color,			pos_x + default_position_x + distance_between_x * 1.0f + button_size_x / 2.0f, pos_y + default_position_y + distance_between_y * 4.0f + 3.0f);
		EFont::active_font->draw(_batch, cached_text_border_color,	pos_x + default_position_x + distance_between_x * 2.0f + button_size_x / 2.0f, pos_y + default_position_y + distance_between_y * 4.0f + 3.0f);
		EFont::active_font->draw(_batch, cached_text_size,			pos_x + default_position_x + distance_between_x * 3.0f + button_size_x / 2.0f, pos_y + default_position_y + distance_between_y * 4.0f + 3.0f);

		float siz = 1.0 / (master_block->minimap_icon_size * 0.5f + 1.0);

		_batch->setcolor(EColorCollection::MINIMAP_ICON_COLOR[master_block->minimap_icon_color]);
		_batch->draw_rect_with_uv(pos_x + icon_button_base_x + 55.0f * 5.0f, pos_y + icon_button_base_y + 80.0 * 3.0f, 45.0f * siz, 45.0f * siz, DefaultGabarite::gabarite_minimap_icon[master_block->minimap_icon_shape]);
		
		_batch->setcolor_alpha(EColorCollection::BLACK, 0.5f);
		_batch->draw_rama(pos_x + icon_button_base_x + 55.0f * 5.0f, pos_y + icon_button_base_y + 80.0 * 3.0f, 45.0f * siz, 45.0f * siz, 2.0f, DefaultGabarite::gabarite_white);
	}

	void EWindowFilterVisualEditor::text_pass(Batcher* _batch)
	{
		
	}

	void EWindowFilterVisualEditor::button_event(EButton* _b)
	{
		
		master_block = _b->master_block;

		if (master_block->is_minimap_icon)
		{update_minimap_button();}
		else
		{deactivate_minimap_button();}

		((EButtonCheck*)link_to_icon_checker)->change_state(master_block->is_minimap_icon);



		for (EButton* b : link_to_sliders)
		{
			b->master_block = _b->master_block;
		}

		for (EButton* b : button_list)
		{
			b->master_block = _b->master_block;
		}

		link_to_sliders.at(0)->slider_value = master_block->bg_hue / 360.0f;
		link_to_sliders.at(1)->slider_value = EMath::clamp_value_float(master_block->bg_saturation / 1.0f,0.00f,1.00f);
		link_to_sliders.at(2)->slider_value = master_block->bg_value / 255.0f;
		link_to_sliders.at(3)->slider_value = master_block->bg_alpha/255.0f;
		
		link_to_sliders.at(4)->slider_value = master_block->text_color_hue / 360.0f;
		link_to_sliders.at(5)->slider_value = EMath::clamp_value_float(master_block->text_color_saturation / 1.0f, 0.00f, 1.0f);
		link_to_sliders.at(6)->slider_value = master_block->text_color_value / 255.0f;
		link_to_sliders.at(7)->slider_value = master_block->text_color_alpha/255.0f;		

		link_to_sliders.at(8)->slider_value = master_block->rama_hue / 360.0f;
		link_to_sliders.at(9)->slider_value = EMath::clamp_value_float(master_block->rama_saturation / 1.0f, 0.00f, 1.00f);
		link_to_sliders.at(10)->slider_value = master_block->rama_value / 255.0f;
		link_to_sliders.at(11)->slider_value = master_block->rama_alpha/255.0f;

		link_to_sliders.at(12)->slider_value = (master_block->font_size - 18.0f) / 27.0f;
		//std::cout << "standart window button event" << std::endl;

		update_ray_button();
	}

	void EWindowFilterVisualEditor::update_localisation()
	{
		//std::cout << "try update localisation in window. blocks count: " << filter_block_list.size() << std::endl;

		for (EButton* b : button_list)
		{
			//std::cout << "button: " << b->text << std::endl;
			b->update_localisation();
		}

		cached_text_border_color	=	EString::localize_it("text_border_color");
		cached_text_color			=	EString::localize_it("text_text_color");
		cached_text_bg_color		=	EString::localize_it("text_bg_color");
		cached_text_size			=	EString::localize_it("text_text_size");


	}

	void EWindowFilterVisualEditor::close_action()
	{
		StaticData::window_loot_simulator->align_x = Enums::PositionMode::MID;
		StaticData::window_filter_visual_editor ->align_x = Enums::PositionMode::MID;
	}
