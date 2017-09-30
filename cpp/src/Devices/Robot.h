#ifndef ROBOT_H
#define ROBOT_H

#include "Engine.h"
#include "ColorSensor.h"
#include "../commons/Direction.h"

class Robot {

public:
	Robot();
	virtual ~Robot();

	Engine& getEngine();
	ColorSensor& getColorSensor();

	void scan_color();
	void line_follow();

	bool search_line(Direction dir, int bg_color, double seconds);
	Direction getOpposedDir(Direction dir);

private:
	Engine* _engine;
	ColorSensor* _sn_color;
};


#endif