#ifndef _CP_LCD128X64_DISPLAY_H_
#define _CP_LCD128X64_DISPLAY_H_
#include <Arduino.h>
#include <U8g2lib.h>

#ifdef U8X8_HAVE_HW_SPI
#include <SPI.h>
#endif
#ifdef U8X8_HAVE_HW_I2C
#include <Wire.h>
#endif

#include "cp_struct.h"

class CPLCD128X64Display {
public:
  CPLCD128X64Display();
  void init(int screenWidth = 128, int screenHeight = 64);
  void clear();
  void drawText(String text, int x, int y);
  void drawTextUTF8(String text, int x, int y);
  void loop();
  void move(rotate_button joystick);
  void updateDraw();

private:
  void prepare(void);
private:
  U8G2_ST7920_128X64_F_SW_SPI u8g2;
  cp_point position;
  String text;
  int screenWidth;
  int screenHeight;
};
#endif