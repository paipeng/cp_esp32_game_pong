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
  void drawText(String text, cp_point position);
  void drawTextUTF8(String text, cp_point position);
  void loop();
  void move(rotate_button joystick);
  void updateDraw();
  void drawGameField();
  void drawGameInfo();
  void drawGame(cp_ball ball, cp_player* players);
  cp_size getDisplaySize();
  cp_rectangle getFieldRectangle();

private:
  void prepare(void);
private:
  U8G2_ST7920_128X64_F_SW_SPI u8g2;
  cp_point position;
  String text;
  cp_size screenSize;
  cp_rectangle field;
};
#endif