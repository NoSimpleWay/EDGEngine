
#include "EButton.h"

#include <glad/glad.h>
#include "Batcher.h"
#include <iostream>
#include "Helper.h"
#include <GLFW/glfw3.h>
#include "EFont.h"
#include "EControl.h"


	

	EButton::EButton()
	{

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
		if ((EControl::mouse_x > button_x- bound_size_left) && (EControl::mouse_x < button_x+ button_size_x+ bound_size_right) && (EControl::mouse_y > button_y-bound_size_down) && (EControl::mouse_y < button_y + button_size_y+ bound_size_up))
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
		if ((EControl::mouse_pressed)&&(!EControl::button_pressed))
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
			_batch->setcolor_255(255, 200, 100, 100);
		}
		else
		{
			_batch->setcolor_255(255, 255, 255, 100);
		}

		if (is_input_mode_active)
		{
			_batch->setcolor_255(128, 128, 128, 100);
		}

		if (is_expanded)
		{
			for (int i = 0; i < drop_elements; i++)
			{
				_batch->draw_rect_with_uv(button_x, button_y-i*27-30, button_size_x, 25, 0, 0, 1, 1);
			}
		}

		
		//std::cout << "red color is:" << _batch->batch_color_r;

		_batch->draw_rect_with_uv(button_x, button_y, button_size_x, button_size_y, 0, 0, 1, 1);
	}

	void EButton::text_pass(EFont* _font, Batcher* _batch)
	{
		_batch->setcolor(0.0f, 0.0f, 0.0f, 1.0f);
		_font->draw(_batch,text, button_x+2, button_y+2);
	}
