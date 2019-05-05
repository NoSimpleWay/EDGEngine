#pragma once
class ECamera
{
public:
	float x;
	float y;
	float zoom=1.0f;

	float speed_x = 0;
	float speed_y = 0;

	ECamera();
	~ECamera();
	void update();
};

