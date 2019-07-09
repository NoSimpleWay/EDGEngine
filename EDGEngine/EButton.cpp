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



	

	EButton::EButton()
	{

	}

	EButton::EButton(float _x, float _y, float _sx, float _sy)
	{
		button_x = _x;
		button_y = _y;

		button_size_x = _sx;
		button_size_y = _sy;
	}



	EButton::~EButton()
	{

	}

	bool EButton::is_overlap()
	{
		
		//ETexture::texture[0] = 0;
		//std::cout << "" << std::endl;

		//std::cout << Helper::x << " " << Helper::y << " " << std::endl;
		//std::cout << "PIZDOS=" << EMouse::mouse_x<< endl;
		if ((EControl::mouse_x > master_position_x - bound_size_left) && (EControl::mouse_x < master_position_x + button_size_x+ bound_size_right) && (EControl::mouse_y > master_position_y -bound_size_down) && (EControl::mouse_y < master_position_y + button_size_y+ bound_size_up))
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

	void EButton::update(float _d)
	{

		//cout << main_window << endl;
		if (master_position == Enums::PositionMaster::FILTER_BLOCK)
		{
			if (position_mode_x == Enums::PositionMode::LEFT) { master_position_x = master_block->x + button_x; }
			if (position_mode_y == Enums::PositionMode::DOWN) { master_position_y = master_block->y + button_y; }
		}

		if (master_position == Enums::PositionMaster::WINDOW)
		{
			if (position_mode_x == Enums::PositionMode::LEFT) { master_position_x = master_window->pos_x + button_x; }
			if (position_mode_x == Enums::PositionMode::MID) { master_position_x = master_window->pos_x + (master_window->window_size_x-button_size_x)/2.0f+button_x; }

			if (position_mode_y == Enums::PositionMode::DOWN) { master_position_y = master_window->pos_y + button_y; }
			if (position_mode_y == Enums::PositionMode::MID) { master_position_y = master_window->pos_y + (master_window->window_size_y - button_size_y) / 2.0f + button_y; }
			if (position_mode_y == Enums::PositionMode::UP) { master_position_y = master_window->pos_y + master_window->window_size_y + button_y; }


		}

		if (master_position == Enums::PositionMaster::SCREEN)
		{
			if (position_mode_x == Enums::PositionMode::LEFT) { master_position_x = button_x; }
			if (position_mode_y == Enums::PositionMode::DOWN) { master_position_y = button_y; }
		}

		if (is_click())
		{
			

			EControl::button_pressed = true;
			std::cout << "Button pressed" << std::endl;

			if (is_drop_list)
			{
				is_expanded = !is_expanded;

				if (is_expanded)
				{
					bound_size_down = 150;
				}
				else
				{
					bound_size_down = 0;
				}
			}

			if ((have_input_mode) && (!is_input_mode_active))
			{
				is_input_mode_active = true;
			}

			click_event();
		}

		if (is_input_mode_active)
		{
			//std::cout << last_inputed_char << std::endl;
			if (EControl::last_inputed_char !=NULL )
			{
				text += EControl::last_inputed_char;
				EControl::last_inputed_char = NULL;

				input_event();
			}

			
			//is_button_pressed
			
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
				}
			}

			if (glfwGetKey(EWindow::main_window, GLFW_KEY_ENTER) == GLFW_PRESS)
			{
				is_input_mode_active = false;
			}
			
			
		}

		

	}

	void EButton::draw(Batcher* _batch)
	{
		//std::cout << "!" << std::endl;
		
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






		_batch->draw_rect_with_uv(master_position_x, master_position_y, button_size_x, button_size_y, DefaultGabarite::gabarite_white);

		float temp_w = 0;

		if (is_expanded)
		{
			for (int i = 0; i < drop_elements; i++)
			{
				_batch->draw_rect_with_uv(master_position_x, master_position_y - i * 27 - 30, button_size_x, 25, DefaultGabarite::gabarite_white);
			}
		}

		if (have_icon)
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

			_batch->setcolor(EColorCollection::WHITE);
			_batch->draw_rect_with_uv(master_position_x+(button_size_x- gabarite->size_x * mul_x)/2.0f, master_position_y, gabarite->size_x* mul_x, gabarite->size_y* mul_x, gabarite);
		}

		if (have_text)
		{
			

			if (text != "")
			{
				_batch->setcolor(0.0f, 0.0f, 0.0f, 1.0f);
				EFont::font_arial->draw(_batch, text, master_position_x + 2, master_position_y + 2);
			}

			if ((text == "")&&(input_hint!="")&&(is_input_mode_active))
			{
				_batch->setcolor(0.5f, 0.5f, 0.5f, 1.0f);
				EFont::font_arial->draw(_batch, input_hint, master_position_x + 2, master_position_y + 2);
			}
		}




	}

	void EButton::text_pass(Batcher* _batch)
	{
		
		if ((have_description) && (is_overlap()))
		{
			_batch->setcolor(EColorCollection::WHITE);
			_batch->draw_rect_with_uv(EControl::mouse_x+3, EControl::mouse_y-5, EFont::get_width(EFont::font_arial,description_text), 20, DefaultGabarite::gabarite_white);

			_batch->setcolor(EColorCollection::BLACK);
			EFont::font_arial->draw(_batch, description_text, EControl::mouse_x+3, EControl::mouse_y -2);
		}
	}


	void EButton::click_event()
	{
		std::cout << "STANDART click event" << std::endl;
	}

	void EButton::input_event()
	{
	}


