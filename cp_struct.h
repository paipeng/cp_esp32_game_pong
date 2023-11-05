#ifndef _CP_STRUCT_H_
#define _CP_STRUCT_H_

#include <Arduino.h>
#define DEBUG 0


#define SNAKE_SIZE 20


// 0: unmove; 1: right; 2: bottom; 3: left; 4: top
#define MOVE_NONE 0
#define MOVE_UP 1
#define MOVE_RIGHT 2
#define MOVE_DOWN 3
#define MOVE_LEFT 4
#define BUTTON_DOWN 5


typedef struct _ps2_joystick {
  int x;
  int y;
  int k;
  int left;
  int right;
} ps2_joystick;

typedef struct _cp_size {
  int width;
  int height;
} cp_size;

typedef struct _cp_point {
  int x;
  int y;
} cp_point;



typedef struct _snake_point {
  cp_point position;
  int color;

  struct _snake_point* pre;
  struct _snake_point* next;
} snake_point;

#ifdef __cplusplus
extern "C" {
#endif
snake_point* init_snake_point_array();
void snake_point_array_push(snake_point* spoints, cp_point p);
void snake_point_array_push_at_begin(snake_point* spoints, cp_point p);
void free_snake_point_array(snake_point* spoints);
bool snake_point_array_contain(snake_point* spoints, cp_point p);

#ifdef __cplusplus
}
#endif
#endif
