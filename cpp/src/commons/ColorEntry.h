#ifndef COLORENTRY_H
#define COLORENTRY_H

#include <iostream>
#include "Color.h"
#include "ColorRGB.h"

class ColorEntry {
public:
	ColorEntry();
	virtual ~ColorEntry();

	void setMin(ColorRGB min);
	void setMax(ColorRGB max);
	void setName(std::string name);

	ColorRGB getMin();
	ColorRGB getMax();
	std::string getName();

private:
	std::string _name = "UNKNOW";
	ColorRGB _min;
	ColorRGB _max;

friend std::ostream& operator<<(std::ostream& out, ColorEntry& c);
};

#endif