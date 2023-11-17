#include "cp_rotate_button.h"


//按键配置
#define EC11_A_PIN 32
#define EC11_B_PIN 33
#define EC11_K_PIN 34  //按键引脚

static CPRotateButton* pButton = NULL;
static rotate_button rb;

//按键单击回调函数
void click() {
  Serial.println("Click");
  if (pButton->mode == 0) {
    Serial.println("Click: MUTE");
    rb.button |= 0b001;
  }
  if (pButton->mode == 1) {
    Serial.println("Enter");
    rb.button &= 0b110;
  }
}


//按键长按回调函数
void longclick() {
  Serial.println("longclick");
  if (pButton->activate) {  //如果旋钮转动，则不切换状态
    Serial.println("Longclick: Mode Change");
    Serial.print("current mode: ");
    if (pButton->mode == 0) {
      pButton->mode = 1;
      Serial.println("Arrow");
      rb.button |= 0b010;
      return;
    }
    if (pButton->mode == 1) {
      pButton->mode = 0;
      Serial.println("Media");
      rb.button &= 0b101;
      return;
    }
  }
  pButton->activate = true;
}

//按键双击回调函数
void doubleclick() {
  Serial.println("doubleclick");
  if (pButton->mode == 0) {
    Serial.println("Doubleclick: Input test");
    rb.button |= 0b100;
  }
  if (pButton->mode == 1) {
    Serial.println("Doubleclick: Input test");
    rb.button &= 0b011;
  }
}

CPRotateButton::CPRotateButton()
  : clk(HIGH),
    button(EC11_K_PIN, true), lastEncoderValue(0), now_count(0), mode(0), activate(true) {
  pButton = this;
  ESP32Encoder::useInternalWeakPullResistors = UP;
}

void CPRotateButton::init() {
  Serial.println("CPRotateButton::init");

  encoder.attachSingleEdge(EC11_A_PIN, EC11_B_PIN);

  pinMode(EC11_K_PIN, INPUT_PULLUP);

  //初始化按键事件检测
  button.attachClick(click);
  button.attachDoubleClick(doubleclick);
  button.attachLongPressStop(longclick);
  button.setDebounceTicks(20);  //滤波(ms)
  button.setClickTicks(200);
  button.setPressTicks(500);
}

rotate_button CPRotateButton::read() {
  button.tick();
  rb.update = 0;
  rb.volumn = 0;
  rb.direction = -1;
  rb.rotate = lastEncoderValue;
  if (lastEncoderValue != encoder.getCount()) {
    now_count = encoder.getCount();
    if (now_count != lastEncoderValue) {
      if (!button.isIdle()) {  //检测按键是否空闲
        activate = false;
        //Serial.printf("(Long_pressed)Encoder value: %d\n", now_count);
      } else {
        //Serial.printf("Encoder value: %d\n", now_count);
      }
    }

    if (now_count > lastEncoderValue) {
      if (!button.isIdle()) {  //检测按键是否空闲
        if (mode == 0) {}      //模式0按钮按下顺时针功能
        if (mode == 1) {       //模式1按钮按下顺时针功能
          Serial.println("DOWN_ARROW");
          rb.direction = 1;
        }
      } else {
        if (mode == 0) {  //模式0顺时针功能
          //Serial.println("MEDIA_VOLUME_UP");
          rb.volumn = 1;
          rb.direction = 3;
        }
        if (mode == 1) {  //模式1顺时针功能
          Serial.println("RIGHT_ARROW");
          rb.direction = 0;
        }
      }
    } else if (now_count < lastEncoderValue) {
      if (!button.isIdle()) {  //检测按键是否空闲
        if (mode == 0) {}      //模式0按钮按下逆时针功能
        if (mode == 1) {       //模式1按钮按下逆时针功能
          Serial.println("UP_ARROW");
          rb.direction = 3;
        }
      } else {
        if (mode == 0) {  //模式0逆时针功能
          //Serial.println("MEDIA_VOLUME_DOWN");
          rb.volumn = -1;
          rb.direction = 1;
        }
        if (mode == 1) {  //模式1逆时针功能
          Serial.println("LEFT_ARROW");
          rb.direction = 2;
        }
      }
    }
    lastEncoderValue = now_count;
    rb.update = 1;
  }
  return rb;
}
