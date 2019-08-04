#pragma once
#include <string>
#include "Batcher.h"
#include "Enums.h"
using namespace std;

class EFont
{
public:
	float x[512];
	float y[512];

	float size_x[512];
	float size_y[512];

	float offset_x[512];
	float offset_y[512];

	float advance[512];
	string name[512];

	float real_size_x[512];
	float real_size_y[512];

	EFont();
	~EFont();
	float get_data_from_sub_data(string _s);
	void final_draw(Batcher* _batcher, string _s, float _x, float _y);
	void draw(Batcher* _batcher, string _s, float _x, float _y);
	void add_draw(Batcher* _batcher, string _s, float _x, float _y);
	void load_font(string _path);

	void draw(string _s, Batcher _batch);

	static float get_width(EFont* _font, string _text);

	void set_align_once(Enums::PositionMode _al);

	float x_adding=0;

	static EFont* font_arial;

	Enums::PositionMode align_x = Enums::PositionMode::LEFT;

	bool align_only_once = false;
	Enums::PositionMode align_prev= Enums::PositionMode::LEFT;

	float scale = 1.0f;

};

