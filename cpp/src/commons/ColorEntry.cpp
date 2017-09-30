#include "ColorEntry.h"

ColorEntry::ColorEntry()
{

}

ColorEntry::~ColorEntry()
{

}

void ColorEntry::setMin(ColorRGB min)
{
	_min = min;
}

void ColorEntry::setMax(ColorRGB max)
{
	_max = max;
}

void ColorEntry::setName(std::string name)
{
	_name = name;
}

ColorRGB ColorEntry::getMin()
{
	return _min;
}

ColorRGB ColorEntry::getMax()
{
	return _max;
}

std::string ColorEntry::getName()
{
	return _name;
}

std::ostream& operator<<(std::ostream& out, ColorEntry& c)
{	
	ColorRGB min = c.getMin();
	ColorRGB max = c.getMax();
	out << min;
	out << " ";
	out << max;
	return out;
}