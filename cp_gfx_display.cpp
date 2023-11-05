#include "cp_gfx_display.h"

CPGFXDisplay::CPGFXDisplay():bus(NULL), gfx(NULL) {

}

void CPGFXDisplay::init() {
  bus = new Arduino_ESP32SPI(
    TFT_DC, 
    TFT_CS /* CS */, 
    TFT_SCK /* SCK */, 
    TFT_MOSI /* MOSI */, 
    GFX_NOT_DEFINED /* MISO */, 
    VSPI /* spi_num */
    );
  gfx = new Arduino_ST7789(
    bus, 
    TFT_RST /* RST */, 
    TFT_SCREEN_ROTATE /* rotation */, 
    true /* IPS */,
    TFT_SCREE_WIDTH /* width */, 
    TFT_SCREE_HEIGHT /* height */,
    0 /* col offset 1 */, 
    0 /* row offset 1 */
    );
  gfx->begin();

#ifdef GFX_BL
  pinMode(GFX_BL, OUTPUT);
  digitalWrite(GFX_BL, HIGH);
#endif 
  reset();
}

void CPGFXDisplay::update_draw(snake_point* spoints, cp_point p) {
  gfx->fillScreen(BLACK);
#if DEBUG
    Serial.print("food");
    Serial.printf(" x: %4d y: %4d", p.x, p.y);
    Serial.println("");
#endif
  gfx->fillRect(p.x, p.y, SNAKE_SIZE, SNAKE_SIZE, RED);
#if 1
  snake_point *current_point = spoints;
  while (current_point->next != NULL) {
    current_point = current_point->next;
#if DEBUG
    Serial.print("draw snake");
    Serial.printf(" x: %4d y: %4d", current_point->position.x, current_point->position.y);
    Serial.println("");
#endif
    gfx->fillRect(current_point->position.x, current_point->position.y, SNAKE_SIZE, SNAKE_SIZE, BLUE);
  }
#if DEBUG
  Serial.print("draw snake 1 ");
  Serial.printf(" x: %4d y: %4d", spoints->position.x, spoints->position.y);
  Serial.println("");
#endif
  gfx->fillRect(spoints->position.x, spoints->position.y, SNAKE_SIZE, SNAKE_SIZE, BLUE);
#endif
}

void CPGFXDisplay::reset() {
  gfx->fillScreen(BLACK);
  gfx->setCursor(10, 10);
  gfx->setTextColor(RED);
  gfx->setTextSize(6 /* x scale */, 6 /* y scale */, 2 /* pixel_margin */);
  gfx->println("CP-SNAKE");
}

void CPGFXDisplay::game_over(int score) {
  gfx->fillScreen(BLACK);
  gfx->setCursor(25, 75);
  gfx->setTextColor(RED);
  gfx->setTextSize(5 /* x scale */, 5 /* y scale */, 1 /* pixel_margin */);
  gfx->println("GAME OVER");


  gfx->setCursor(45, 200);
  gfx->setTextSize(2 /* x scale */, 2 /* y scale */, 0 /* pixel_margin */);
  gfx->printf("Score: %4d", score);

}

cp_size CPGFXDisplay::get_size() {
  return (cp_size){TFT_SCREE_HEIGHT, TFT_SCREE_WIDTH};
}