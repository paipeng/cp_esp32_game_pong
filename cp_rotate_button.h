#ifndef _CP_ROTATE_BUTTON_H_
#define _CP_ROTATE_BUTTON_H_

#include <Arduino.h>
#include "AiEsp32RotaryEncoder.h"

class CPRotateButton {
public:
  CPRotateButton();
  void init();
  int read();
private:
  float getFrequency();

private:
  int clk;
  AiEsp32RotaryEncoder rotaryEncoder;
};

#endif