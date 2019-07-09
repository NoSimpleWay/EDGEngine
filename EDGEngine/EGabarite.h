#pragma once
#include <string>
class EGabarite
{
public:
	float x;
	float y;

	float x2;
	float y2;

	float size_x;
	float size_y;



	std::string name;

	EGabarite(std::string _name, float _x, float _y, float _size_x, float _size_y);
	~EGabarite();
};

class DefaultGabarite
{
public:
	static EGabarite* gabarite_white;
	static EGabarite* gabarite_undefined;
};
