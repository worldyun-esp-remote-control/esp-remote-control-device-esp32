#include <Arduino.h>
#include <start.h>
#include <Config.h>
#include <Mqtt.h>

#define LOOP_DELAY_MS 100   //循环睡眠时间(ms) 为0则关闭睡眠


void setup() {
  start();
}


void loop() {
  if( LOOP_DELAY_MS >0 ){
    delay(LOOP_DELAY_MS);
  }
  WIFI::loop();
  Mqtt::loop();
}

