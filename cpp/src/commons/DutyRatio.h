#ifndef DutyRatio_H
#define DutyRatio_H

struct DutyRatio
{
  float l;
  float r;
};

namespace DutyCycleRatio {
  extern DutyRatio FORWARD;
  extern DutyRatio BACKWARD;
  extern DutyRatio LEFT;
  extern DutyRatio RIGHT;
  extern DutyRatio STOP;
}

#endif