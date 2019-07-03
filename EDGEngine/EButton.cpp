#include <glad/glad.h>
#include "Batcher.h"
#include <iostream>
#include "Helper.h"

class EButton
{
public:
	float x=10;
	float y=10;

	float size_x=100;
	float size_y=100;

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

		if ((x>x) && (mouse_x < x+size_x) && (mouse_y > y) && (mouse_y < y + size_y))
		{
			return true;
		}
		else
		{
			return false;
		}
		//return false;
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

		

		
		//std::cout << "red color is:" << _batch->batch_color_r;

		_batch->draw_rect_with_uv(x, y, size_x, size_y, 0, 0, 1, 1);
	}
};