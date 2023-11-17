#include "cp_game_pong.h"

#define PLAYER_SIZE 8
#define PLAYER_NUM 2
#define PLAYER_MOVE_STEP 2

CPGamePong::CPGamePong() {
}

void CPGamePong::init(cp_rectangle field) {
  randomSeed(analogRead(0));

  this->field = field;
  players = (cp_player*)malloc(sizeof(cp_player) * 2);

  ball.position = (cp_point){ this->field.start_point.x + (this->field.end_point.x - this->field.start_point.x) / 2,
                              this->field.start_point.y + (this->field.end_point.y - this->field.start_point.y) / 2 };
  ball.speed = 1;
  ball.angle = random(0, 359) / 2.0 / M_PI;
  Serial.printf("random ball angle: %.02f\n", ball.angle);
  players[0].size = PLAYER_SIZE;
  players[0].position = (cp_point){ this->field.start_point.x,
                                    this->field.start_point.y + (this->field.end_point.y - this->field.start_point.y) / 2 - players[0].size / 2 };
  players[1].size = PLAYER_SIZE;
  players[1].position = (cp_point){ this->field.end_point.x - 1,
                                    this->field.start_point.y + (this->field.end_point.y - this->field.start_point.y) / 2 - players[0].size / 2 };
}

cp_player* CPGamePong::getPlayers() {
  return players;
}
cp_ball CPGamePong::getBall() {
  return ball;
}
void CPGamePong::updateBall() {
  cp_point current_position = ball.position;
  float distance = ball.speed;
  ball.position.x += distance * cos(ball.angle);
  ball.position.y += distance * sin(ball.angle);
}

bool CPGamePong::movePlayers(rotate_button* players_joysticks) {
  bool moved = false;
  for (int i = 0; i < PLAYER_NUM; i++) {
    if (players_joysticks[i].update != 0) {
      moved = true;
      if (players_joysticks[i].direction == 0) {  // right
        players[i].position.x += PLAYER_MOVE_STEP;
      } else if (players_joysticks[i].direction == 1) {  // down
        players[i].position.y += PLAYER_MOVE_STEP;
      } else if (players_joysticks[i].direction == 2) {  // left
        players[i].position.x -= PLAYER_MOVE_STEP;
      } else if (players_joysticks[i].direction == 3) {  // up
        players[i].position.y -= PLAYER_MOVE_STEP;
      }

      if (players[i].position.x < field.start_point.x) {
        players[i].position.x = field.start_point.x;
      } else if (players[i].position.x >= field.end_point.x) {
        players[i].position.x = field.end_point.x - 1;
      }

      if ((players[i].position.y - players[i].size / 2) < field.start_point.y) {
        players[i].position.y = field.start_point.y + players[i].size / 2;
      } else if ((players[i].position.y + players[i].size / 2) >= field.end_point.y) {
        players[i].position.y = field.end_point.y - 1 - players[i].size / 2;
      }

      //Serial.printf("player %d move to: %d-%d\n", i, players[i].position.x, players[i].position.y);
    }
  }
  return moved;
}
