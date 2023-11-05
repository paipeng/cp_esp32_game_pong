#include "cp_struct.h"



snake_point* init_snake_point_array() {
  snake_point *spoints = (snake_point *)malloc(sizeof(snake_point));
  spoints->pre = NULL;
  spoints->next = NULL;
  return spoints;
}

void snake_point_array_push(snake_point* spoints, cp_point p) {
  snake_point *current_point = spoints, *new_point = NULL;
  while (current_point->next != NULL) {
      current_point = current_point->next;
  }
  
  new_point = init_snake_point_array();
  new_point->pre = current_point;
  new_point->position = p;
  new_point->next = NULL;
  current_point->next = new_point;
}

void snake_point_array_push_at_begin(snake_point* spoints, cp_point p) {
  snake_point *new_point = init_snake_point_array();
  new_point->pre = NULL;
  new_point->position = p;
  new_point->next = spoints;
  spoints->pre = new_point;
  spoints = new_point;
}

void free_snake_point_array(snake_point* spoints) {
  snake_point* current_point = spoints, *next_point = NULL;
  if (current_point != NULL) {
      do {
          next_point = current_point->next;
          free(current_point);
          current_point = next_point;
      } while (next_point != NULL);
      spoints = NULL;
  }
}

bool snake_point_array_contain(snake_point* spoints, cp_point p) {
  if (spoints) {
    snake_point* current_point = spoints;
    do {
      if (current_point->position.x == p.x && current_point->position.y == p.y) {
        return true;
      }
      current_point = current_point->next;
    } while (current_point != NULL);
  }
  return false;
}