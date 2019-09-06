#pragma once
class EColor
{
public:
	float color_red = 1.0f;
	float color_green = 1.0f;
	float color_blue = 1.0f;
	float color_alpha = 1.0f;

	EColor(float _r, float _g, float _b, float _a);
	EColor();
	~EColor();
	void set(float _r, float _g, float _b, float _a);
	void set(EColor* _c);
	void set_alpha(EColor* _c, float _a);
	void set_bright(EColor* _c, float _bright);

};

class EColorCollection
{
public:
	static EColor* RED;
	static EColor* GREEN;
	static EColor* BLUE;

	static EColor* WHITE;
	static EColor* GRAY;
	static EColor* BLACK;

	static EColor* YELLOW;
	static EColor* CYAN;
	static EColor* PINK;

	static EColor* DAD_NORMAL;
	static EColor* DAD_MAGIC;
	static EColor* DAD_RARE;
	static EColor* DAD_UNIQUE;

	static EColor* LIGHT_GRAY;
	static EColor* DARK_GRAY;

	static EColor* MINIMAP_ICON_COLOR[6];


};