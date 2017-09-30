#ifndef COLORRGB_H
#define COLORRGB_H

#include <iostream>

class ColorRGB {

public:
	ColorRGB();
	ColorRGB(int r, int g, int b);
	virtual ~ColorRGB();

	int red();
	int green();
	int blue();

	void set_red(int r);
	void set_green(int g);
	void set_blue(int b);

	int distanceOf(ColorRGB& color);

private:
	int _red = 0;
	int _green = 0;
	int _blue = 0;


friend std::ostream& operator<<(std::ostream& out, ColorRGB& color);
friend bool operator>=(ColorRGB& color1, ColorRGB& color2);
friend bool operator<=(ColorRGB& color1, ColorRGB& color2);
};

#endif