#pragma once
class EColor
{
public:
	float color_red = 1.0f;
	float color_green = 1.0f;
	float color_blue = 1.0f;
	float color_alpha = 1.0f;

	EColor(float _r, float _g, float _b, float _a);
	~EColor();
	void set(float _r, float _g, float _b, float _a);

};

class EColorCollection
{
public:
	static EColor* RED;
	static EColor* GREEN;
	static EColor* BLUE;

	static EColor* WHITE;
	static EColor* BLACK;

	static EColor* YELLOW;
	static EColor* CYAN;
	static EColor* PINK;
};