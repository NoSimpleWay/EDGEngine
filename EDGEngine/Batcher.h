#pragma once
class Batcher
{


public:
	Batcher();
	void init();
	void draw_rect(float _x, float _y, float _w, float _h, int _tx, int _ty);
	void draw_rect_without_color(float _x, float _y, float _w, float _h, int _tx, int _ty);
	void fill_indices();
	~Batcher();

	void reinit();

	unsigned int id = 0;
	unsigned int VBO, VAO, EBO=0;
	float vertices[250000];
	void draw_call();
};
