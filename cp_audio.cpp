#include "cp_audio.h"
#include <Arduino.h>

#define CP_BEEP_GPIO 25
CPAudio::CPAudio()
  : t(1) {
}

void CPAudio::init() {
  pinMode(CP_BEEP_GPIO, OUTPUT);  // set ESP32 pin to output mode
}

void CPAudio::beep() {
  //Serial.println("beep on");
  digitalWrite(CP_BEEP_GPIO, HIGH);  // turn on
  delay(50);                         //延时200ms
  digitalWrite(CP_BEEP_GPIO, LOW);   // turn off
  delay(50);                         //延时200ms
  /*
  t.setTimeout([]() {
    Serial.println("beep off");
    digitalWrite(CP_BEEP_GPIO, LOW); // turn on
    //t.cancelAll();
    //Serial.println("cancel all timer");
  }, 200);
  */
}

void CPAudio::beep_off() {
  //Serial.println("beep off");
  //digitalWrite(CP_BEEP_GPIO, LOW); // turn off
}