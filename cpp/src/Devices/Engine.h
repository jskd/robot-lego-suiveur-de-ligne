#ifndef ENGINE_H
#define ENGINE_H

#include "../libs/ev3dev.h"
#include "../commons/Direction.h"
#include "../commons/DutyRatio.h"

class Engine {

public:
  Engine();
  virtual ~Engine();

  void setSpeed(int speed);
  void setDirection(Direction dir);
  void setRatio(DutyRatio ratio);
  void run();
  void stop();
  bool running();

private:
  void _updateDutyCycle();
  int _speed = 30;
  bool _run = false;
  Direction _direction;
  DutyRatio _ratio= DutyCycleRatio::STOP;
  ev3dev::large_motor* _motor_R;
  ev3dev::large_motor* _motor_L;

};

#endif
