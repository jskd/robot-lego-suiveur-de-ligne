#include "Engine.h"

using namespace ev3dev;

Engine::Engine()
{
	_motor_R = new large_motor(OUTPUT_A);
	_motor_L = new large_motor(OUTPUT_D);

	_direction = Direction::FORWARD;
	_run = false;
}

Engine::~Engine()
{
	_motor_R->reset();
	_motor_L->reset();

	delete _motor_R;
	delete _motor_L;
}

void Engine::_updateDutyCycle()
{
  _motor_L->set_duty_cycle_sp(_speed * _ratio.l);
  _motor_R->set_duty_cycle_sp(_speed * _ratio.r);
}

void Engine::setSpeed(int speed)
{
	_speed = speed;
	//_updateDutyCycle();
}

void Engine::setDirection(Direction dir)
{
	_direction = dir;

 	switch(_direction){
    case Direction::FORWARD:
      setRatio(DutyCycleRatio::FORWARD);
    break;
    case Direction::BACKWARD:
      setRatio(DutyCycleRatio::BACKWARD);
    break;
    case Direction::LEFT:
      setRatio(DutyCycleRatio::LEFT);
    break;
    case Direction::RIGHT:
      setRatio(DutyCycleRatio::RIGHT);
    break;
    default:
      setRatio(DutyCycleRatio::STOP);
    break;
  }
}

void Engine::setRatio(DutyRatio ratio)
{
  _ratio = ratio;
  _updateDutyCycle();
}

void Engine::run()
{
	_motor_L->run_direct();
	_motor_R->run_direct();
	_run = true;
}

void Engine::stop()
{
	_motor_L->set_duty_cycle_sp(0);
	_motor_R->set_duty_cycle_sp(0);

	_motor_L->set_stop_action("brake");
	_motor_R->set_stop_action("brake");

	_motor_L->stop();
	_motor_R->stop();

	_run = false;
}

bool Engine::running()
{
	return _run;
}
