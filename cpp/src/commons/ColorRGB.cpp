#include <math.h>
#include "ColorRGB.h"

ColorRGB::ColorRGB()
{

}

ColorRGB::ColorRGB(int r, int g, int b)
	: _red(r), _green(g), _blue(b)
{
	
}

ColorRGB::~ColorRGB()
{
	
}

int ColorRGB::red()
{
	return _red;
}

int ColorRGB::green()
{
	return _green;
}

int ColorRGB::blue()
{
	return _blue;
}

void ColorRGB::set_red(int r)
{
	_red = r;
}

void ColorRGB::set_green(int g)
{
	_green = g;
}

void ColorRGB::set_blue(int b)
{
	_blue = b;
}

int ColorRGB::distanceOf(ColorRGB& color)
{
	int distance = sqrt(pow(_red - color.red(), 2) + pow(_green - color.green(), 2) + pow(_blue - color.blue(), 2));
	return distance;
}

std::ostream& operator<<(std::ostream& out, ColorRGB& color){
	out << color._red << " " << color._green << " " << color._blue << " ";
	return out;
}

bool operator>=(ColorRGB& color1, ColorRGB& color2){
	if( (color1._red >= color2._red) && (color1._green >= color2._green) && (color1._blue >= color2._blue))
		return true;
	return false;
}

bool operator<=(ColorRGB& color1, ColorRGB& color2){
	if( (color1._red <= color2._red) && (color1._green <= color2._green) && (color1._blue <= color2._blue))
		return true;
	return false;
}