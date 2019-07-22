#pragma once
class EMath
{
public:
	static float clamp_value_float(float _v, float _min, float _max);

	static struct rgb {
		double r;       // a fraction between 0 and 1
		double g;       // a fraction between 0 and 1
		double b;       // a fraction between 0 and 1
	};

	static struct hsv {
		double h;       // angle in degrees
		double s;       // a fraction between 0 and 1
		double v;       // a fraction between 0 and 1
	};

	static hsv rgb2hsv(rgb in);
	static rgb hsv2rgb(hsv in);
};