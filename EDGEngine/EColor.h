#pragma once
class EColor_base
{
public:
	float color_red = 1.0f;
	float color_green = 1.0f;
	float color_blue = 1.0f;
	float color_alpha = 1.0f;

	EColor_base(float _r, float _g, float _b, float _a);
	~EColor_base();


};

class EColor
{
public:
	static EColor_base* RED;
	static EColor_base* GREEN;
	static EColor_base* BLUE;

	static EColor_base* WHITE;
	static EColor_base* BLACK;

	static EColor_base* YELLOW;
	static EColor_base* CYAN;
	static EColor_base* PINK;
};