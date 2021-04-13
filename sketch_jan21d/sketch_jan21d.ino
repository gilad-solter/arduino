#include <Arduino.h>

uint8_t channel1 = 8;
uint8_t channel2 = 7;

void setup() {
  pinMode(channel1, OUTPUT);
  pinMode(channel2, OUTPUT);
}

void loop() {
  
  
}

void spinUp() {
  digitalWrite(channel1, HIGH);
  digitalWrite(channel2, LOW);
}

void spinDown(){
  digitalWrite(channel1, LOW);
  digitalWrite(channel2, HIGH);
}

void stop(){
  digitalWrite(channel1, LOW);
  digitalWrite(channel2, LOW);
}
