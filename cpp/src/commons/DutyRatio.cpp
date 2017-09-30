#include "DutyRatio.h"

//                                    left   right
DutyRatio DutyCycleRatio::FORWARD = { 1    , 1     };
DutyRatio DutyCycleRatio::BACKWARD= { -1   , -1    };
DutyRatio DutyCycleRatio::LEFT    = { -0.5 , 1     };
DutyRatio DutyCycleRatio::RIGHT   = { 1    , -0.5  };
DutyRatio DutyCycleRatio::STOP    = { 0    , 0     };