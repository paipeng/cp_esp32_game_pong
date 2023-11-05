#include "cp_rotate_button.h"


#define CP_GPIO_DT 2
#define CP_GPIO_CLK 4
#define CP_GPIO_SW 35
#define CP_GPIO_VCC -1	 /* 27 put -1 of Rotary encoder Vcc is connected directly to 3,3V; else you can use declared output pin for powering rotary encoder */
#define CP_GPIO_STEPS 1

AiEsp32RotaryEncoder *encoder = NULL;

void IRAM_ATTR readEncoderISR() {
  if (encoder) {
  	encoder->readEncoder_ISR();
  }
}

CPRotateButton::CPRotateButton():clk(HIGH), 
rotaryEncoder(CP_GPIO_CLK, CP_GPIO_DT, CP_GPIO_SW, CP_GPIO_VCC, CP_GPIO_STEPS) {
  encoder = &rotaryEncoder;
}

void CPRotateButton::init() {
  Serial.println("CPRotateButton::init");
#if 0
  pinMode(CP_GPIO_CLK, INPUT);
  pinMode(CP_GPIO_DT, INPUT);
  pinMode(CP_GPIO_SW, INPUT);
#else
  rotaryEncoder.begin();
  rotaryEncoder.setup(readEncoderISR);

  	//set boundaries and if values should cycle or not
	//in this example we will set possible values between 0 and 1000;
	bool circleValues = false;
	rotaryEncoder.setBoundaries(0, 1000, circleValues); //minValue, maxValue, circleValues true|false (when max go to min and vice versa)

	/*Rotary acceleration introduced 25.2.2021.
   * in case range to select is huge, for example - select a value between 0 and 1000 and we want 785
   * without accelerateion you need long time to get to that number
   * Using acceleration, faster you turn, faster will the value raise.
   * For fine tuning slow down.
   */
	//rotaryEncoder.disableAcceleration(); //acceleration is now enabled by default - disable if you dont need it
	rotaryEncoder.setAcceleration(250); //or set the value - larger number = more accelearation; 0 or 1 means disabled acceleration
#endif
}

int CPRotateButton::read() {
#if 0  
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
#else
  if (rotaryEncoder.encoderChanged()) {
    Serial.print(getFrequency(), 1);
    Serial.println(" MHz ");
  }
  if (rotaryEncoder.isEncoderButtonClicked()) {
    Serial.print("Radio station set to ");
    Serial.print(getFrequency());
    Serial.println(" MHz ");
  }
  return 0;
#endif  
}

float CPRotateButton::getFrequency() {
    return (float)rotaryEncoder.readEncoder() / 10.0;
}