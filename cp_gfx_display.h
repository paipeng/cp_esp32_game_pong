#ifndef _CP_GFX_DISPLAY_H_
#define _CP_GFX_DISPLAY_H_

#include <Arduino.h>
#include <Arduino_GFX_Library.h>
#include "cp_struct.h"

#define TFT_DC 13 /* DC */
#define TFT_CS 5 /* CS */
#define TFT_SCK 18 /* SCK */
#define TFT_MOSI 23 /* MOSI */
#define TFT_RST 14 /* MOSI */


#define TFT_SCREEN_ROTATE 1
#define TFT_SCREE_WIDTH 240
#define TFT_SCREE_HEIGHT 320

class CPGFXDisplay {
public:
  CPGFXDisplay();

  void init();
  void reset();
  void update_draw(snake_point* spoints, cp_point p);
  cp_size get_size();
  void game_over(int score);
private:
  Arduino_DataBus *bus;
  Arduino_GFX *gfx;
};

#endif