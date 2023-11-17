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
  OneButton button;

public:
  int lastEncoderValue;
  int now_count;
  int mode;  //0,1两种mode,可自行添加
  bool activate;
};

#endif