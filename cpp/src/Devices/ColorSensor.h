#ifndef COLORSENSOR_H
#define COLORSENSOR_H

#include <unistd.h>
#include <vector>

#include "../libs/ev3dev.h"
#include "../commons/Color.h"
#include "../commons/ColorRGB.h"
#include "../commons/ColorEntry.h"


class ColorSensor {

public:
	ColorSensor();
	virtual ~ColorSensor();

	void calibration();
	void sampling(int samples, ColorRGB& average);
	void sampling(int samples, ColorRGB& min, ColorRGB& max);
	void save_calibration(std::string file);
	void open_calibration(std::string file);

	int getColor();
	std::string getColorName(int ref);
	ColorRGB getColorRGB();

private:
	ev3dev::color_sensor* _sensor;
	std::vector<ColorEntry*> _dico_colors;

};

#endif