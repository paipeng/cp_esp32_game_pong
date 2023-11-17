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
  delay(2000);  // 5 seconds
  //audio.init();
  display.init();
  // init
  pong.init(display.getFieldRectangle());

  //joystick.init();
  //snake.init(display.get_size());
  player1.init();

  game_over = 0;
  delay(1000);  // 5 seconds
  Serial.println("Start game...");

  //display.drawText("Coleco Telstar TV Game", (cp_point){70, 10});

  display.drawGame(pong.getBall(), pong.getPlayers());
}


void loop() {
  //audio.beep_off();
  delay(100);
  if (game_over == 0) {
    joysticks[0] = player1.read();
    joysticks[1] = joysticks[0];

    if (pong.movePlayers(joysticks)) {
      if (pong.updateBall() == -1) {
        game_over = 1;
      }
      display.drawGame(pong.getBall(), pong.getPlayers());
    }
  } else {
    Serial.println("Game Over!");
  }
}
