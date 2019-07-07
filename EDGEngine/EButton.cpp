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

	void EButton::update(float _d)
	{

		//cout << main_window << endl;
		if (master_position == Enums::ButtonPositionMaster::FILTER_BLOCK)
		{
			if (position_mode_x == Enums::ButtonPositionMode::LEFT) { master_position_x = master_block->x + button_x; }
			if (position_mode_y == Enums::ButtonPositionMode::DOWN) { master_position_y = master_block->y + button_y; }
		}

		if (master_position == Enums::ButtonPositionMaster::SCREEN)
		{
			if (position_mode_x == Enums::ButtonPositionMode::LEFT) { master_position_x = button_x; }
			if (position_mode_y == Enums::ButtonPositionMode::DOWN) { master_position_y = button_y; }
		}

		if ((EControl::mouse_pressed)&&(!EControl::button_pressed)&&(is_overlap()))
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
		}

		if (is_input_mode_active)
		{
			//std::cout << last_inputed_char << std::endl;
			if (last_inputed_char !=NULL )
			{
				text += last_inputed_char;
				last_inputed_char = NULL;
			}

			
			//is_button_pressed
			
			if
				(
					(
						(glfwGetKey(main_window, GLFW_KEY_BACKSPACE) == GLFW_PRESS)
						||
						(glfwGetKey(main_window, GLFW_KEY_DELETE) == GLFW_PRESS)
					)
					&&
					(EControl::button_backspace_released)
				)
			{
				EControl::button_backspace_released=false;

				if (text.length() > 1)
				{
					text = text.substr(0, text.length() - 1);
				}
				else
				{
					text = "";
				}
			}

			if (glfwGetKey(main_window, GLFW_KEY_ENTER) == GLFW_PRESS)
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
			_batch->setcolor_255(128, 128, 128, 100);
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
			_batch->setcolor(EColor::WHITE);
			_batch->draw_rect_with_uv(master_position_x+(button_size_x- gabarite->size_x / 2.0f)/2.0f, master_position_y, gabarite->size_x/2.0f, gabarite->size_y/2.0f, gabarite);
		}



	}

	void EButton::text_pass(EFont* _font, Batcher* _batch)
	{
		if (have_text)
		{
			_batch->setcolor(0.0f, 0.0f, 0.0f, 1.0f);

			_font->draw(_batch, text, master_position_x + 2, master_position_y + 2);
		}

		
		if ((have_description)&&(is_overlap()))
		{
			_batch->setcolor(EColor::WHITE);
			_batch->draw_rect_with_uv(master_position_x, master_position_y - 21, 100, 20, DefaultGabarite::gabarite_white);

			_batch->setcolor(EColor::BLACK);
			_font->draw(_batch, description_text, master_position_x, master_position_y - 21);
		}
	}
