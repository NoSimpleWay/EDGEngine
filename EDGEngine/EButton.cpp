#pragma once
#include "EButton.h"

#include <glad/glad.h>
#include "Batcher.h"
#include <iostream>
#include "Helper.h"
#include <GLFW/glfw3.h>
#include "EFont.h"
#include "EControl.h"

#include "FilterBlock.h"

#include "EUtils.h"
#include "StaticData.h"

#include <windows.h>

	int EButton::top_window_id=-1;

	EButton::EButton()
	{
		update_localisation();
	}

	EButton::EButton(float _x, float _y, float _sx, float _sy)
	{
		button_x = _x;
		button_y = _y;

		button_size_x = _sx;
		button_size_y = _sy;

		button_min_size_x = _sx;
		button_min_size_y = _sy;

		update_localisation();
	}

	EButton::EButton(float _x, float _y, float _sx, float _sy, Enums::ButtonType _type)
	{
		button_x = _x;
		button_y = _y;

		button_size_x = _sx;
		button_size_y = _sy;

		button_type = _type;

		update_localisation();
	}



	EButton::~EButton()
	{

	}

	bool EButton::is_number(char _c)
	{
		if
		(
			(_c == '0') ||
			(_c == '1') ||
			(_c == '2') ||
			(_c == '3') ||
			(_c == '4') ||
			(_c == '5') ||
			(_c == '6') ||
			(_c == '7') ||
			(_c == '8') ||
			(_c == '9')
		)
		{
			return true;
		}

		return false;
	}

	bool EButton::is_overlap()
	{
		
		//ETexture::texture[0] = 0;
		//std::cout << "" << std::endl;

		//std::cout << Helper::x << " " << Helper::y << " " << std::endl;
		//std::cout << "PIZDOS=" << EMouse::mouse_x<< endl;
		if (
				(EControl::mouse_x > master_position_x - bound_size_left)
				&&
				(EControl::mouse_x < master_position_x + button_size_x+ bound_size_right)
				&&
				(EControl::mouse_y > master_position_y -bound_size_down)
				&&
				(EControl::mouse_y < master_position_y + button_size_y+ bound_size_up)
				&&
				(top_window_id==master_window->id)
			)
		{
			return true;
		}
		else
		{
			return false;
		}
		//return false;
	}

	bool EButton::is_click()
	{
		if ((EControl::mouse_pressed) && (!EControl::button_pressed) && (is_overlap())) { return true; }

		return false;
	}

	bool EButton::is_outclick()
	{
		if ((EControl::mouse_pressed) && (!is_overlap()) && (!outclick_protection)) { return true; }

		return false;
	}

	bool EButton::is_right_click()
	{
		if ((EControl::mouse_right_pressed) && (!EControl::button_right_pressed) && (is_overlap())) { EControl::button_right_pressed = true; return true; }

		return false;
	}

	void EButton::update(float _d)
	{

		if
		(
			(can_receive_paste)
			&&
			(is_overlap())
			&&
			(glfwGetKey(EWindow::main_window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
			&&
			(glfwGetKey(EWindow::main_window, GLFW_KEY_V) == GLFW_PRESS)
		)
		{
			if (!OpenClipboard(nullptr))
			{}

			// Get handle of clipboard object for ANSI text
			HANDLE hData = GetClipboardData(CF_TEXT);
			if (hData == nullptr)
			{}

			// Lock the handle to get the actual text pointer
			char* pszText = static_cast<char*>(GlobalLock(hData));
			if (pszText == nullptr)
			{}

			// Save text in a string class instance
			std::string clipboard_text(pszText);
			text = clipboard_text;

			// Release the lock
			GlobalUnlock(hData);

			// Release the clipboard
			CloseClipboard();

			if (is_input_mode_active)
			{
				input_event();
			}

			if (master_block != NULL) { StaticData::window_filter_block->unsave_change = true; }
			if (master_separator != NULL) { StaticData::window_filter_block->unsave_change = true; }
		}

		if
			(
				(is_overlap())
				&&
				(glfwGetKey(EWindow::main_window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
				&&
				(glfwGetKey(EWindow::main_window, GLFW_KEY_C) == GLFW_PRESS)
				)
		{
			const char* output = text.c_str();
			const size_t len = strlen(output) + 1;
			HGLOBAL hMem = GlobalAlloc(GMEM_MOVEABLE, len);
			memcpy(GlobalLock(hMem), output, len);
			GlobalUnlock(hMem);
			OpenClipboard(0);
			EmptyClipboard();
			SetClipboardData(CF_TEXT, hMem);
			CloseClipboard();
		}
		//std::cout << "clipboard [" << (text) << "]" << std::endl;

		if (is_outclick())
		{
			if ((is_expanded) && (is_drop_list))
			{
				is_expanded = false;
			}

			if ((have_input_mode) && (is_input_mode_active))
			{
				is_input_mode_active = false;

				if ((input_only_numbers) && (text == ""))
				{
					text = "0";
				}
				input_finish_event();
			}
		}

		if (!EControl::mouse_pressed)
		{
			outclick_protection = false;
		}

		//cout << main_window << endl;
		if (master_position == Enums::PositionMaster::FILTER_BLOCK)
		{
			if (position_mode_x == Enums::PositionMode::LEFT) { master_position_x = master_block->x + button_x; }
			if (position_mode_x == Enums::PositionMode::RIGHT) { master_position_x = master_block->x + button_x-button_size_x+master_block->size_x;}
			if (position_mode_x == Enums::PositionMode::MID) { master_position_x = master_block->x + (master_block->size_x - button_size_x) / 2.0f;}


			if (position_mode_y == Enums::PositionMode::UP) { master_position_y = master_block->y + button_y+master_block->size_y-button_size_y; }
			if (position_mode_y == Enums::PositionMode::DOWN) { master_position_y = master_block->y + button_y; }
			if (position_mode_y == Enums::PositionMode::MID) { master_position_y = master_block->y + (master_block->size_y - button_size_y) / 2.0f + button_y; }
		}



		if (master_position == Enums::PositionMaster::WINDOW)
		{
			if (position_mode_x == Enums::PositionMode::LEFT) { master_position_x = master_window->pos_x + button_x; }
			if (position_mode_x == Enums::PositionMode::MID) { master_position_x = master_window->pos_x + (master_window->window_size_x-button_size_x)/2.0f + button_x; }
			if (position_mode_x == Enums::PositionMode::RIGHT) { master_position_x = master_window->pos_x + master_window->window_size_x + button_x - button_size_x; }

			if (position_mode_y == Enums::PositionMode::DOWN) { master_position_y = master_window->pos_y + button_y; }
			if (position_mode_y == Enums::PositionMode::MID) { master_position_y = master_window->pos_y + (master_window->window_size_y - button_size_y) / 2.0f + button_y; }
			if (position_mode_y == Enums::PositionMode::UP) { master_position_y = master_window->pos_y + master_window->window_size_y + button_y-button_size_y; }
		}

		if (master_position == Enums::PositionMaster::SCREEN)
		{
			if (position_mode_x == Enums::PositionMode::LEFT) { master_position_x = button_x; }
			if (position_mode_y == Enums::PositionMode::DOWN) { master_position_y = button_y; }
		}

		if (master_position == Enums::PositionMaster::SEPARATOR)
		{
			if (position_mode_x == Enums::PositionMode::LEFT) { master_position_x = master_separator->x + button_x; }
			if (position_mode_x == Enums::PositionMode::RIGHT) { master_position_x = master_separator->x + button_x - button_size_x + master_separator->size_x; }
			if (position_mode_x == Enums::PositionMode::MID) { master_position_x = master_separator->x + (master_separator->size_x - button_size_x) / 2.0f; }


			if (position_mode_y == Enums::PositionMode::UP) { master_position_y = master_separator->y + button_y + master_separator->size_y - button_size_y; }
			if (position_mode_y == Enums::PositionMode::DOWN) { master_position_y = master_separator->y + button_y; }
			if (position_mode_y == Enums::PositionMode::MID) { master_position_y = master_separator->y + (master_separator->size_y - button_size_y) / 2.0f + button_y; }
		}

		if (is_right_click())
		{
			right_click_event();

			if (can_be_removed)
			{
				std::cout << "TRY REMOVE" << std::endl;
				need_remove = true;

				if (master_block != NULL) {StaticData::window_filter_block->unsave_change = true;}
			}
		}

		if (is_click())
		{
			
			if (master_block != NULL) {StaticData::window_filter_block->unsave_change = true;}

			if (!is_holdable) { EControl::button_pressed = true; }
			//std::cout << "Button pressed" << std::endl;

			if (is_drop_list)
			{
				if (is_expanded)
				{
					selected_element = (int)((master_position_y - EControl::mouse_y) / 22.0f);

					if (selected_element < 0) { selected_element = 0; }
					if (selected_element > drop_elements) { selected_element = drop_elements; }

					text = drop_text.at(selected_element);
					drop_list_select_event();
				}

				is_expanded = !is_expanded;
				
				
			}

			if ((have_input_mode) && (!is_input_mode_active))
			{
				if (input_auto_clear_text) { text = ""; }
				is_input_mode_active = true;
			}



			if (is_slider) { slider_activate = true; }

			
			click_event();
		}

		if (!EControl::mouse_pressed)
		{
			slider_activate = false;
		}

		if ((is_slider)&&(slider_activate)&&(slider_is_horizontal))
		{
			slider_value = (EControl::mouse_x - master_position_x) / button_size_x;
			slider_value = EMath::clamp_value_float(slider_value, 0.0f, 1.0f);

			slide_drag_event();
			if (master_block != NULL) { StaticData::window_filter_block->unsave_change = true; }
		}

		if ((is_slider) && (slider_activate) && (!slider_is_horizontal))
		{
			slider_value = 1.0f - (EControl::mouse_y - master_position_y) / button_size_y;
			slider_value = EMath::clamp_value_float(slider_value, 0.0f, 1.0f);

			slide_drag_event();
			if (master_block != NULL) { StaticData::window_filter_block->unsave_change = true; }
		}

		if (is_input_mode_active)
		{
			//std::cout << last_inputed_char << std::endl;
			if
			(
				(EControl::last_inputed_char !=NULL )
				&&
				(
					(!input_only_numbers)
					||
					(is_number(EControl::last_inputed_char))
				)
				&&
				(
					(EFont::active_font->get_width(EFont::active_font, text + EControl::last_inputed_char) < button_size_x)
					||
					(dynamic_input_width)
				)
			)
			{
				text += EControl::last_inputed_char;
				EControl::last_inputed_char = NULL;

				if (master_block != NULL) { StaticData::window_filter_block->unsave_change = true; }
				input_event();
			}

			
			//is_button_pressed
			
			if ((EControl::delete_button_hold_time > 0.5f) && (is_input_mode_active))
			{
				text = "";

				input_event();
			}

			if
				(
					(
						(glfwGetKey(EWindow::main_window, GLFW_KEY_BACKSPACE) == GLFW_PRESS)
						||
						(glfwGetKey(EWindow::main_window, GLFW_KEY_DELETE) == GLFW_PRESS)
					)
					&&
					(EControl::button_backspace_released)
				)
			{
				EControl::button_backspace_released=false;

				if (text.length() > 1)
				{
					
					text = text.substr(0, text.length() - 1.0f);
					input_event();
				}
				else
				{
					text = "";
					input_event();
					if (master_block != NULL) { StaticData::window_filter_block->unsave_change = true; }
				}

				//input_event();

				
			}



			if
			(
				(glfwGetKey(EWindow::main_window, GLFW_KEY_ENTER) == GLFW_PRESS)
				||
				(glfwGetKey(EWindow::main_window, GLFW_KEY_KP_ENTER) == GLFW_PRESS)
			)
			{
				is_input_mode_active = false;

				if ((input_only_numbers) && (text == ""))
				{
					text = "0";
				}

				input_finish_event();
			}
			
			
		}

		flash_cooldown-=_d;
		if (flash_cooldown < 0)
		{
			flash_cooldown += 0.25f;

			flash_line_active = !flash_line_active;
		}

		update_additional(_d);

	}

	void EButton::update_additional(float _d)
	{
	}

	void EButton::default_draw(Batcher* _batch)
	{
		//std::cout << "!" << std::endl;
		EFont::active_font->scale = 1.0f;
		if (is_overlap())
		{
			_batch->setcolor_255(0, 200, 0, 100);
		}
		else
		{
			_batch->setcolor_255(20, 30, 45, 17);
		}

		if (is_input_mode_active)
		{
			_batch->setcolor_255(220, 255, 200, 100);
		}



		
		//std::cout << "red color is:" << _batch->batch_color_r;




		if (have_bg)
		{
			_batch->setcolor(bg_color);
			_batch->draw_rect_with_uv(master_position_x, master_position_y, button_size_x, button_size_y, DefaultGabarite::gabarite_wood_button_bg);
		}

		float temp_w = 0;




		if ((have_icon) && (gabarite != NULL))
		{
			if (icon_adaptation)
			{
				float mul_x = 1;
				float mul_y = 1;

				if ((gabarite->size_x > button_size_x) || (gabarite->size_y > button_size_y))
				{
					if (gabarite->size_x > gabarite->size_y)
					{
						mul_x = button_size_x / gabarite->size_x;
						mul_y = button_size_x / gabarite->size_x;
					}
					else
					{
						mul_x = button_size_y / gabarite->size_y;
						mul_y = button_size_y / gabarite->size_y;
					}
				}

				_batch->setcolor(icon_color);
				_batch->draw_rect_with_uv(master_position_x + (button_size_x - gabarite->size_x * mul_x) / 2.0f, master_position_y, gabarite->size_x * mul_x, gabarite->size_y * mul_x, gabarite);
			}
			else
			{
				_batch->setcolor(EColorCollection::WHITE);
				_batch->draw_rect_with_uv(master_position_x, master_position_y, button_size_x, button_size_y, gabarite);
			}
		}

		if (have_text)
		{
			EFont* target_font = EFont::active_font;

			//if (EFont::get_width(EFont::active_font, text) + 5.0f > button_size_x)
			//{
			if (dynamic_input_width)
			{
				button_size_x = EFont::get_width(EFont::active_font, text) + 10.0f;
			}
			//}

				if (button_size_x < button_min_size_x)
				{
					button_size_x = button_min_size_x;
				}

			if (force_font != NULL) { target_font = force_font;}

			float added_x = 0;

			if (text_align_x == Enums::PositionMode::MID) { added_x = round(button_size_x / 2.0f); }
			else { added_x = 3.0f; }
			target_font->align_x = text_align_x;

			if (text != "")
			{
				_batch->setcolor(text_color);
				target_font->draw(_batch, text, master_position_x + 0.0f +added_x, master_position_y + round((button_size_y-20.0f)/2.0f + 4.0f));
			}

			if ((text == "")&&(input_hint!=""))
			{
				_batch->setcolor(hint_color);
				target_font->draw(_batch, input_hint, master_position_x + 0.0f +added_x, master_position_y + round((button_size_y - 20.0f) / 2.0f + 4.0f));
			}

			if (is_input_mode_active)
			{
				if (flash_line_active)
				{
					_batch->setcolor(EColorCollection::BLACK);
					_batch->draw_rect_with_uv(master_position_x + 0.0f + EFont::get_width(target_font,text)+added_x, master_position_y + (button_size_y - 20.0f) / 2.0f + 4.0f, 3.0f, 17, DefaultGabarite::gabarite_white);
				}
			}
		}


		if (have_rama)
		{
			_batch->setcolor(rama_color);
			_batch->draw_rama(master_position_x, master_position_y, button_size_x, button_size_y,rama_thikness,DefaultGabarite::gabarite_wood_button_bg);
		}

		if (is_slider)
		{
			if (slider_is_horizontal)
			{
				if (slider_trail_texture != NULL)
				{
					_batch->setcolor(EColorCollection::WHITE);
					_batch->draw_rect_gabarite_custom_uv
					(
						master_position_x,
						master_position_y,
						(slider_trail_texture->size_x - slider_head_texture->size_x) * slider_value + slider_head_texture->size_x * 0.5f,
						button_size_y,
						slider_trail_texture,
						0.0f,
						0.0f,
						(slider_trail_texture->size_x - slider_head_texture->size_x) * slider_value + slider_head_texture->size_x * 0.5f,
						slider_trail_texture->size_y
					);
				}

				if (slider_head_texture == NULL)
				{
					_batch->setcolor(EColorCollection::WHITE);
					_batch->draw_rect_with_uv(master_position_x + (button_size_x - 3.0f) * slider_value - 1, master_position_y - 1, 5, button_size_y + 2, DefaultGabarite::gabarite_white);


					_batch->setcolor(EColorCollection::BLACK);
					_batch->draw_rect_with_uv(master_position_x + (button_size_x - 3.0f) * slider_value, master_position_y, 3, button_size_y, DefaultGabarite::gabarite_white);
				}
				else
				{
					_batch->setcolor(EColorCollection::WHITE);
					_batch->draw_rect_with_uv(master_position_x + (button_size_x - slider_head_texture->size_x) * slider_value , master_position_y + (button_size_y - slider_head_texture->size_y) / 2.0f, slider_head_texture->size_x, slider_head_texture->size_y, slider_head_texture);
				}
			}
			else
			{
				_batch->setcolor(EColorCollection::WHITE);
				_batch->draw_rect_with_uv(master_position_x - 1,	master_position_y - 31.0f + button_size_y - (button_size_y - 32.0f) * slider_value,	button_size_x + 2,		32.0f,		DefaultGabarite::gabarite_white);

				_batch->setcolor(EColorCollection::BLACK);
				_batch->draw_rect_with_uv(master_position_x,		master_position_y - 30.0f + button_size_y - (button_size_y - 32.0f) * slider_value,		button_size_x,		32.0f,		DefaultGabarite::gabarite_white);
			}

			
		}

		additional_draw(_batch);

		if ((is_overlap()) & (can_be_highlighted))
		{
			_batch->setcolor_alpha(EColorCollection::GREEN, 0.25f);
			_batch->draw_rect_with_uv(master_position_x - 3.0f, master_position_y - 3.0f, button_size_x + 6.0f, button_size_y + 6.0f, DefaultGabarite::gabarite_white);
		}

	}

	void EButton::additional_draw(Batcher* _batch)
	{
		//std::cout << "Default" << std::endl;
	}

	void EButton::text_pass(Batcher* _batch)
	{
		catched_element = (int)((master_position_y - EControl::mouse_y) / 22.0f);
		if (is_expanded)
		{
			bound_size_down = drop_elements*22;

			for (int i = 0; i < drop_elements; i++)
			{
				if (catched_element==i)
				{ _batch->setcolor(0.05f, 0.10f, 0.06f, 1.0f);}
				else
				{
					if (have_list_color)
					{
						_batch->setcolor(drop_list_color.at(i));
					}
					else
					{_batch->setcolor(0.8f, 0.9f, 1.0f, 1.0f);}
				}

				_batch->draw_rect_with_uv(master_position_x, master_position_y - i * 22 - 20, button_size_x, 20, DefaultGabarite::gabarite_white);

				_batch->setcolor(0.0f,0.1f,0.2f,0.9f);
				_batch->draw_rama(master_position_x, master_position_y - i * 22 - 20, button_size_x, 20, rama_thikness, DefaultGabarite::gabarite_white);

				if (catched_element == i)
				{
					_batch->setcolor(0.95f, 0.90f, 0.94f, 1.0f);
				}
				else
				{
					_batch->setcolor(EColorCollection::BLACK);
				}
				EFont::active_font->set_align_once(Enums::PositionMode::MID);
				EFont::active_font->draw(_batch, drop_text.at(i), master_position_x+button_size_x/2.0f, master_position_y - i * 22 - 20+3);
			}
		}
		else
		{
			bound_size_down = 0;
		}

		/*if (prev_description_text != description_text)
		{
			

			//std::cout << "description changed from <" << prev_description_text << "> to [" << description_text << ">" << std::endl;

			//prev_description_text = description_text;
		}*/

		if ((have_description) && (is_overlap())&&(description_text != ""))
		//if (is_overlap() && (have_description))
		{

			EFont* target_font = EFont::active_font;

			float th = EFont::get_height(target_font, description_text) + 5.0f;

			if (force_font != NULL)
			{
				target_font = force_font;
			}

			float x_description= EControl::mouse_x + 20.0f;
			if (x_description + EFont::get_width(target_font, description_text) + 5>EWindow::SCR_WIDTH)
			{
				x_description += EWindow::SCR_WIDTH - (x_description + EFont::get_width(target_font, description_text) + 5.0f);
			}

			target_font->align_x=Enums::PositionMode::LEFT;

			_batch->setcolor(EColorCollection::WHITE);
			_batch->draw_rect_with_uv(x_description, EControl::mouse_y - 20.0f - th, EFont::get_width(target_font, description_text)+8, th, DefaultGabarite::gabarite_white);

			_batch->setcolor(EColorCollection::BLACK);
			target_font->draw(_batch, description_text, x_description + 5.0f, EControl::mouse_y - 34.0f);

			_batch->draw_rama(x_description, EControl::mouse_y - 20.0f - th, EFont::get_width(target_font, description_text)+8, th, 2, DefaultGabarite::gabarite_white);
		}
	}

	void EButton::incoming_data(FilterBlock* _block)
	{

	}


	void EButton::click_event()
	{
		std::cout << "STANDART click event" << std::endl;
	}

	void EButton::right_click_event()
	{
	}

	void EButton::input_event()
	{
	}

	void EButton::input_finish_event()
	{
	}

	void EButton::drop_list_select_event()
	{
	}

	void EButton::slide_drag_event()
	{
	}

	void EButton::activate()
	{
		icon_color->set(icon_color_default);
		rama_color->set(rama_color_default);
		bg_color->set(bg_color_default);
	}

	void EButton::deactivate()
	{
		icon_color->set(icon_color_deactivated);
		rama_color->set(icon_color_deactivated);
		bg_color->set(bg_color_deactivated);
	}

	void EButton::update_localisation()
	{
		//std::cout << "DEFAULT LOCAL" << std::endl;
	}



