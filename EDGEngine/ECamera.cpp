#include "ECamera.h"

float x=0.0f;
float y=0.0f;

float speed_x = 0;
float speed_y = 0;

float zoom=1.0f;

ECamera::ECamera()
{
}


ECamera::~ECamera()
{
}

void ECamera::update()
{
	x += speed_x;
	y += speed_y;

	speed_x *= 0.9f;
	speed_y *= 0.9f;
}
