#ifndef _CP_PS2_JOYSTICK_
#define _CP_PS2_JOYSTICK_
#include <Arduino.h>
#include "cp_struct.h"



class CPPS2Joystick {
public:
  CPPS2Joystick();
  void init();
  ps2_joystick readAnalog();
  int readMove();
};

#endif
