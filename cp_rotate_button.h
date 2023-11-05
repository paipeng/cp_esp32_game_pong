#ifndef _CP_ROTATE_BUTTON_H_
#define _CP_ROTATE_BUTTON_H_

#include <Arduino.h>

class CPRotateButton {
public:
  CPRotateButton();
  void init();
  int read();
private:
  int clk;
};

#endif