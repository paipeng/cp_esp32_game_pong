#include "cp_struct.h"
#include "cp_gfx_display.h"
#include "cp_snake.h"
#include "cp_ps2_joystick.h"
#include "cp_audio.h"
#include "cp_rotate_button.h"

CPSnake snake;
CPGFXDisplay display;
CPPS2Joystick joystick;
CPAudio audio;
CPRotateButton rotateButton;

int game_over = 0;

void setup() {
  Serial.begin(115200);

  // init
  audio.init();
  display.init();
  joystick.init();
  snake.init(display.get_size());
  rotateButton.init();

  game_over = 0;
  delay(5000); // 5 seconds
}


void loop() {
  audio.beep_off();
  int rotate = rotateButton.read();
  if (rotate != 0) {
    Serial.printf("rotate: %d\n", rotate);
  }
#if 1
  int event = joystick.readMove();
  if (event == BUTTON_DOWN) {
    Serial.println("reset");
    game_over = 0;
    display.reset();
    snake.reset();
    display.update_draw(snake.get_points(), snake.get_random_point());
    delay(500);
  } else {
    if (game_over == 0) {
      int state = snake.update_snake(event);
      if (state == 2) {
        game_over = 0;
        audio.beep();
      } else {
        game_over = state;
      }
      if (game_over == 0) {
        display.update_draw(snake.get_points(), snake.get_random_point());
      }
      delay(400);
    } else {
      if (game_over == 1) {
        Serial.println("game_over");
        display.game_over(snake.get_score());
        game_over = 2;
      } else {

      }
      delay(5000);
    }

  }
#endif
}
