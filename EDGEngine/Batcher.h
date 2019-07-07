#pragma once
#include "EColor.h"
#include "EGabarite.h"
class Batcher
{


public:
	Batcher();
	void init();
	void draw_rect(float _x, float _y, float _w, float _h);
	void draw_rect_position(float _x, float _y, float _x2, float _y2);
	void draw_rect_without_color(float _x, float _y, float _w, float _h, int _tx, int _ty);
	void draw_rect_with_uv(float _x, float _y, float _w, float _h, float _start_x, float _start_y, float _end_x, float _end_y);
	void draw_rect_with_uv(float _x, float _y, float _w, float _h, EGabarite* _g);
	void fill_indices();

	void setcolor_255(int _r, int _g, int _b, int _a);
	void setcolor(float _r, float _g, float _b, float _a);
	~Batcher();

	float batch_color_r;
	float batch_color_g;
	float batch_color_b;
	float batch_color_a;

	void reinit();

	unsigned int id = 0;
	unsigned int VBO, VAO, EBO=0;
	float vertices[250000];
	void draw_call();
	void reset();
	void setcolor(EColor_base* _color);
	void setcolor_alpha(EColor_base* _color, float _a);
};
