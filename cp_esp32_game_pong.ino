#include "cp_struct.h"
#include "cp_gfx_display.h"
#include "cp_snake.h"
#include "cp_ps2_joystick.h"
#include "cp_audio.h"
#include "cp_rotate_button.h"
#include "cp_lcd128x64_display.h"

CPSnake snake;
CPLCD128X64Display display;
//CPGFXDisplay display;
CPPS2Joystick joystick;
CPAudio audio;
CPRotateButton rotateButton;

int game_over = 0;

void setup() {
  Serial.begin(115200);

  // init
  audio.init();
  display.init();
  //joystick.init();
  //snake.init(display.get_size());
  rotateButton.init();

  game_over = 0;
  delay(5000);  // 5 seconds

  display.drawText("TEST", 10, 10);
}


void loop() {
  //audio.beep_off();
  delay(1000);
  display.loop();
#if 0
  int rotate = rotateButton.read();
  if (rotate != 0) {
    Serial.printf("rotate: %d\n", rotate);
  }
#endif
}
