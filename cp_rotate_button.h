#ifndef _CP_ROTATE_BUTTON_H_
#define _CP_ROTATE_BUTTON_H_

#include <Arduino.h>


#include <OneButton.h>
#include <ESP32Encoder.h>


class CPRotateButton {
public:
  CPRotateButton();
  void init();
  int read();

private:
  int clk;
  ESP32Encoder encoder;
  OneButton SW;
};

#endif