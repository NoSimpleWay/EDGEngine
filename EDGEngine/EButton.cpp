#include <glad/glad.h>
#include "Batcher.h"
#include <iostream>
#include "Helper.h"
#include <GLFW/glfw3.h>
#include "EFont.h"

class EButton
{
public:
	float x=10;
	float y=10;

	float size_x=100;
	float size_y=25;

	std::string text = "!";

	bool have_input_mode=true;
	bool is_input_mode_active = false;

	bool is_active=true;

	EButton()
	{

	}



	~EButton()
	{

	}

	bool is_overlap()
	{
		
		//ETexture::texture[0] = 0;
		//std::cout << "" << std::endl;

		//std::cout << Helper::x << " " << Helper::y << " " << std::endl;

		if ((mouse_x >x) && (mouse_x < x+size_x) && (mouse_y > y) && (mouse_y < y + size_y))
		{
			return true;
		}
		else
		{
			return false;
		}
		//return false;
	}

	void update(float _d)
	{
		if ((mouse_pressed)&&(!button_pressed))
		{
			button_pressed = true;
			std::cout << "Button pressed" << std::endl;

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
					(button_backspace_released)
				)
			{
				button_backspace_released=false;

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

	void draw(Batcher* _batch)
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

		

		
		//std::cout << "red color is:" << _batch->batch_color_r;

		_batch->draw_rect_with_uv(x, y, size_x, size_y, 0, 0, 1, 1);
	}

	void text_pass(EFont* _font, Batcher* _batch)
	{
		_batch->setcolor(0.0f, 0.0f, 0.0f, 1.0f);
		_font->draw(_batch,text,x+2,y+2);
	}
};