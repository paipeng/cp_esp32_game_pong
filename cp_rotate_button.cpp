#include "cp_rotate_button.h"


//按键配置
#define EC11_A_PIN 32
#define EC11_B_PIN 33
#define EC11_K_PIN 34  //按键引脚



int lastEncoderValue = 0;
int now_count = 0;
int mode = 0;  //0,1两种mode,可自行添加
bool activate = true;

//按键单击回调函数
void click() {
  if (mode == 0) {
    Serial.println("Click: MUTE");
  }
  if (mode == 1) {
    Serial.println("Enter");
  }
}


//按键长按回调函数
void longclick() {
  if (activate) {  //如果旋钮转动，则不切换状态
    Serial.println("Longclick: Mode Change");
    Serial.print("current mode: ");
    if (mode == 0) {
      mode = 1;
      Serial.println("Arrow");
      return;
    }
    if (mode == 1) {
      mode = 0;
      Serial.println("Media");
      return;
    }
  }
  activate = true;
}

//按键双击回调函数
void doubleclick() {
  if (mode == 0) {
    Serial.println("Doubleclick: Input test");
  }
  if (mode == 1) {
    Serial.println("Doubleclick: Input test");
  }
}

CPRotateButton::CPRotateButton()
  : clk(HIGH),
    SW(EC11_K_PIN, true) {
}

void CPRotateButton::init() {
  Serial.println("CPRotateButton::init");

  ESP32Encoder::useInternalWeakPullResistors = UP;
  encoder.attachSingleEdge(EC11_A_PIN, EC11_B_PIN);

  pinMode(EC11_K_PIN, INPUT_PULLUP);

  //初始化按键事件检测
  SW.attachClick(click);
  SW.attachDoubleClick(doubleclick);
  SW.attachLongPressStop(longclick);
  SW.setDebounceTicks(20);  //滤波(ms)
  SW.setClickTicks(200);
  SW.setPressTicks(500);
}

int CPRotateButton::read() {
  SW.tick();

  if (lastEncoderValue != encoder.getCount()) {
    now_count = encoder.getCount();
    if (now_count != lastEncoderValue) {
      if (!SW.isIdle()) {  //检测按键是否空闲
        activate = false;
        Serial.print("(Long_pressed)Encoder value: ");
        Serial.println(now_count);
      } else {
        Serial.print("Encoder value: ");
        Serial.println(now_count);
      }
    }

    if (now_count > lastEncoderValue) {
      if (!SW.isIdle()) {  //检测按键是否空闲
        if (mode == 0) {}  //模式0按钮按下顺时针功能
        if (mode == 1) {   //模式1按钮按下顺时针功能
          Serial.println("DOWN_ARROW");
        }
      } else {
        if (mode == 0) {  //模式0顺时针功能
          Serial.println("MEDIA_VOLUME_UP");
        }
        if (mode == 1) {  //模式1顺时针功能
          Serial.println("RIGHT_ARROW");
        }
      }
    }
    if (now_count < lastEncoderValue) {
      if (!SW.isIdle()) {  //检测按键是否空闲
        if (mode == 0) {}  //模式0按钮按下逆时针功能
        if (mode == 1) {   //模式1按钮按下逆时针功能
          Serial.println("UP_ARROW");
        }
      } else {
        if (mode == 0) {  //模式0逆时针功能
          Serial.println("MEDIA_VOLUME_DOWN");
        }
        if (mode == 1) {  //模式1逆时针功能
          Serial.println("LEFT_ARROW");
        }
      }
    }
    lastEncoderValue = now_count;
  }
}
