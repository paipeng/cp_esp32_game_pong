#ifndef _CP_SNAKE_
#define _CP_SNAKE_
#include <Arduino.h>
#include "cp_struct.h"





class CPSnake {
public:
  CPSnake();
  
public:  
  bool is_eat();
  snake_point* get_points();
  cp_point get_random_point();

  void init(cp_size screen_size);
  void reset();
  void random_point();
  int update_snake(int move_dir);
  int get_score();
private:
  bool check_eat(cp_point point);
  bool check_point_invalid(cp_point point);

private:
  snake_point *spoints;
  cp_point r_point;
  int move_direction;
  bool eat;
  cp_size screen_size;
  int score;
};
#endif