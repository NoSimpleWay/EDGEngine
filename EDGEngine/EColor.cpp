#include "EColor.h"

EColor::EColor(float _r, float _g, float _b, float _a)
{
	color_red = _r;
	color_green = _g;
	color_blue = _b;
	color_alpha = _a;
}

void EColor::set(float _r, float _g, float _b, float _a)
{
	color_red = _r;
	color_green = _g;
	color_blue = _b;
	color_alpha = _a;
}

EColor::~EColor()
{
}
EColor* EColorCollection::WHITE=new EColor		(1.0f,		1.0f,		1.0f,		1.0f);
EColor* EColorCollection::BLACK=new EColor		(0,			0,			0,			1.0f);

EColor* EColorCollection::RED=new EColor		(1.0f,		0,			0,			1.0f);
EColor* EColorCollection::GREEN=new EColor		(0,			1.0f,		0,			1.0f);
EColor* EColorCollection::BLUE=new EColor		(0,			0,			1.0f,		1.0f);

EColor* EColorCollection::YELLOW = new EColor	(1.0f,		1.0f,		0,			 1.0f);
EColor* EColorCollection::PINK = new EColor		(1.0f,		0,			1.0f,		 1.0f);
EColor* EColorCollection::CYAN = new EColor		(0,			1.0f,		1.0f,		 1.0f);
