#include "cp_rotate_button.h"

#define CP_GPIO_DT 2
#define CP_GPIO_CLK 4
#define CP_GPIO_SW 35

CPRotateButton::CPRotateButton():clk(HIGH) {

}

void CPRotateButton::init() {
  Serial.println("CPRotateButton::init");
  pinMode(CP_GPIO_CLK, INPUT);
  pinMode(CP_GPIO_DT, INPUT);
  pinMode(CP_GPIO_SW, INPUT);
}

int CPRotateButton::read() {
  int b = digitalRead(CP_GPIO_SW);
  if (b == LOW) {
    Serial.println("button pressed");
    clk = HIGH;
  }
  int new_clk = digitalRead(CP_GPIO_CLK);
  if (new_clk != clk) {
    // changed
    clk = new_clk;
    int value = digitalRead(CP_GPIO_DT);
    Serial.printf("new_clk: %d clk: %d value: %d\n", new_clk, clk, value);
    if (new_clk == LOW && value == HIGH) {
      Serial.println("rotate clockwise");
      return 1;
    } else if (new_clk == LOW && value == LOW) {
      Serial.println("rotate counter-clockwise");
      return -1;
    } else {
      Serial.printf("NO defined -> new_clk: %d clk: %d value: %d\n", new_clk, clk, value);
    }
  }
  return 0;
}