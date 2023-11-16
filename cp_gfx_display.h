#ifndef _CP_GFX_DISPLAY_H_
#define _CP_GFX_DISPLAY_H_

#include <Arduino.h>
#include <Arduino_GFX_Library.h>
#include "cp_struct.h"

class CPGFXDisplay {
public:
  CPGFXDisplay();

  void init();
  void reset();
  void update_draw(snake_point *spoints, cp_point p);
  cp_size get_size();
  void game_over(int score);
private:
  Arduino_DataBus *bus;
  Arduino_GFX *gfx;
};

#endif