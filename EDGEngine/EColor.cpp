#include "EColor.h"

EColor::EColor(float _r, float _g, float _b, float _a)
{
	color_red = _r;
	color_green = _g;
	color_blue = _b;
	color_alpha = _a;
}

EColor::EColor()
{
}



void EColor::set(float _r, float _g, float _b, float _a)
{
	color_red = _r;
	color_green = _g;
	color_blue = _b;
	color_alpha = _a;
}

void EColor::set(EColor* _c)
{
		color_red = _c->color_red;
		color_green = _c->color_green;
		color_blue = _c->color_blue;
		color_alpha = _c->color_alpha;
}

void EColor::set_alpha(EColor* _c, float _a)
{
	color_red = _c->color_red;
	color_green = _c->color_green;
	color_blue = _c->color_blue;

	color_alpha = _a;
}

EColor::~EColor()
{
}
EColor* EColorCollection::WHITE=new EColor			(1.0f,		1.0f,		1.0f,		1.0f);
EColor* EColorCollection::GRAY=new EColor			(0.5f,		0.5f,		0.5f,		1.0f);
EColor* EColorCollection::BLACK=new EColor			(0,			0,			0,			1.0f);

EColor* EColorCollection::RED=new EColor			(1.0f,		0,			0,			1.0f);
EColor* EColorCollection::GREEN=new EColor			(0,			1.0f,		0,			1.0f);
EColor* EColorCollection::BLUE=new EColor			(0,			0,			1.0f,		1.0f);

EColor* EColorCollection::YELLOW = new EColor		(1.0f,		1.0f,		0,			1.0f);
EColor* EColorCollection::PINK = new EColor			(1.0f,		0,			1.0f,		1.0f);
EColor* EColorCollection::CYAN = new EColor			(0,			1.0f,		1.0f,		1.0f);

EColor* EColorCollection::DAD_NORMAL = new EColor	(0.8f,		0.8f,		0.8f,		1.0f);
EColor* EColorCollection::DAD_MAGIC = new EColor	(0.0f,		1.0f,		1.0f,		1.0f);
EColor* EColorCollection::DAD_RARE = new EColor		(1.0f,		1.0f,		0,			1.0f);
EColor* EColorCollection::DAD_UNIQUE = new EColor	(0.78f,		0.5f,		0.25f,		1.0f);
