#include "cp_lcd128x64_display.h"

#define CPIOT_LCD_128X64_E 18   /* clock=*/
#define CPIOT_LCD_128X64_RW 23  /* data=*/
#define CPIOT_LCD_128X64_RS 5   /* CS=*/
#define CPIOT_LCD_128X64_RES 22 /* reset=*/

CPLCD128X64Display::CPLCD128X64Display()
  : u8g2(U8G2_R0, CPIOT_LCD_128X64_E, CPIOT_LCD_128X64_RW, CPIOT_LCD_128X64_RS, CPIOT_LCD_128X64_RES), text(""), screenWidth(0), screenHeight(0) {
}
void CPLCD128X64Display::init(int screenWidth, int screenHeight) {
  this->screenWidth = screenWidth;
  this->screenHeight = screenHeight;
  u8g2.begin();
}
void CPLCD128X64Display::clear() {
  u8g2.clearBuffer();
}


void CPLCD128X64Display::prepare(void) {
  u8g2.setFont(u8g2_font_6x10_tf);
  u8g2.setFontRefHeightExtendedText();
  u8g2.setDrawColor(1);
  u8g2.setFontPosTop();
  u8g2.setFontDirection(0);
}

void CPLCD128X64Display::loop() {
  u8g2.clearBuffer();
  char s[2] = " ";
  uint8_t x, y;
  u8g2.drawStr(0, 0, "ASCII page 1");
  for (y = 0; y < 6; y++) {
    for (x = 0; x < 16; x++) {
      s[0] = y * 16 + x + 32;
      u8g2.drawStr(x * 7, y * 10 + 10, s);
    }
  }
  u8g2.sendBuffer();
}

void CPLCD128X64Display::drawText(String text, cp_point position) {
  this->text = text;
  this->position = position;
  updateDraw();
}

void CPLCD128X64Display::drawTextUTF8(String text, cp_point position) {
  this->text = text;
  this->position = position;
  prepare();
  u8g2.setFont(u8g2_font_wqy12_t_gb2312);
  u8g2.setFontPosTop();
  u8g2.drawUTF8(position.x, position.y, text.c_str());
  u8g2.sendBuffer();
}

void CPLCD128X64Display::updateDraw() {
  prepare();
  u8g2.drawStr(this->position.x, this->position.y, this->text.c_str());
  u8g2.sendBuffer();
}
void CPLCD128X64Display::move(rotate_button joystick) {
  if (joystick.direction == 0) {  // right
    //
    position.x++;
  } else if (joystick.direction == 1) {  // down
    position.y++;
  } else if (joystick.direction == 2) {  // left
    //
    position.x--;
  } else if (joystick.direction == 3) {  // up
    position.y--;
  }

  if (position.x < 0) {
    position.x = 0;
  } else if (position.x >= screenWidth) {
    position.x = screenWidth - 1;
  }

  if (position.y < 0) {
    position.y = 0;
  } else if (position.y >= screenHeight) {
    position.y = screenHeight - 1;
  }
  

  updateDraw();
}