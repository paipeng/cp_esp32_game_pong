#ifndef _CP_GAME_PONG_H_
#define _CP_GAME_PONG_H_

#include "cp_struct.h"

class CPGamePong {
public:
  CPGamePong();
  void init(cp_rectangle field);
  cp_player* getPlayers();
  cp_ball getBall();
  bool movePlayers(rotate_button* players_joysticks);
  int updateBall();

private:

private:
  cp_ball ball;
  cp_player* players;
  cp_rectangle field;
};
#endif