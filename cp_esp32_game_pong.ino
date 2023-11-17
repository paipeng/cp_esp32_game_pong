#include "cp_struct.h"
#include "cp_snake.h"
#include "cp_ps2_joystick.h"
#include "cp_audio.h"
#include "cp_rotate_button.h"
#include "cp_lcd128x64_display.h"
#include "cp_game_pong.h"

//CPSnake snake;
CPLCD128X64Display display;
//CPPS2Joystick joystick;
//CPAudio audio;
CPGamePong pong;
CPRotateButton player1;

int game_over = 0;
rotate_button joysticks[2];
void setup() {
  Serial.begin(115200);



  //audio.init();
  display.init();
  // init
  pong.init(display.getFieldRectangle());

  //joystick.init();
  //snake.init(display.get_size());
  player1.init();

  game_over = 0;
  delay(5000);  // 5 seconds

  //display.drawText("TEST", (cp_point){10, 10});

  display.drawGame(pong.getBall(), pong.getPlayers());
}


void loop() {
  //audio.beep_off();
  delay(100);
  //display.loop();

#if 1
  joysticks[0] = player1.read();
  if (joysticks[0].update != 0) {
    Serial.printf("rotate dir: %d vol: %d button: %d rotate: %d\n", joysticks[0].direction, joysticks[0].volumn, joysticks[0].button, joysticks[0].rotate);
    //display.move(joystick);
  }
  joysticks[1] = joysticks[0];
  if (pong.movePlayers(joysticks)) {
    display.drawGame(pong.getBall(), pong.getPlayers());
  }
#endif
}
