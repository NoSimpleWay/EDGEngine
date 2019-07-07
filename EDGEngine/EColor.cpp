#include "EColor.h"

EColor_base::EColor_base(float _r, float _g, float _b, float _a)
{
	color_red = _r;
	color_green = _g;
	color_blue = _b;
	color_alpha = _a;
}

EColor_base::~EColor_base()
{
}
EColor_base* EColor::WHITE=new EColor_base		(1.0f,		1.0f,		1.0f,		1.0f);
EColor_base* EColor::BLACK=new EColor_base		(0,			0,			0,			1.0f);

EColor_base* EColor::RED=new EColor_base		(1.0f,		0,			0,			1.0f);
EColor_base* EColor::GREEN=new EColor_base		(0,			1.0f,		0,			1.0f);
EColor_base* EColor::BLUE=new EColor_base		(0,			0,			1.0f,		1.0f);

EColor_base* EColor::YELLOW = new EColor_base	(1.0f,		1.0f,		0,			 1.0f);
EColor_base* EColor::PINK = new EColor_base		(1.0f,		0,			1.0f,		 1.0f);
EColor_base* EColor::CYAN = new EColor_base		(0,			1.0f,		1.0f,		 1.0f);
