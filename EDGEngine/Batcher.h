#pragma once
class Batcher
{


public:
	Batcher();
	void init();
	void draw_rect(float _x, float _y, float _w, float _h, int _tx, int _ty);
	void draw_rect_without_color(float _x, float _y, float _w, float _h, int _tx, int _ty);
	void draw_rect_with_uv(float _x, float _y, float _w, float _h, float _start_x, float _start_y, float _end_x, float _end_y);
	void fill_indices();
	void setcolor_255(int _r, int _g, int _b, int _a);
	~Batcher();

	void reinit();

	unsigned int id = 0;
	unsigned int VBO, VAO, EBO=0;
	float vertices[250000];
	void draw_call();
	void reset();
};
