#include <Arduino.h>
#include <Ultrasonic.h>

Ultrasonic ultrasonic(3);
int buttonPinBlue = A1;
int buttonPinGreen = A2;
uint8_t motorChannel1 = 8;
uint8_t motorChannel2 = 7;

enum SpinDirection {
  UP,
  DOWN
};

enum State {
  REST,
  SPINNING_UP,
  SPINNING_DOWN
};

enum BUTTON_STATES {
  OFF,
  ON  
};

State state = REST;
int buttonValueThreshold = 1000;
long BOTTOM_HEIGHT = 69;
long TOP_HEIGHT = 106;

long heightFromFloor;



void setup(){
    pinMode(motorChannel1, OUTPUT);
    pinMode(motorChannel2, OUTPUT);
    Serial.begin(9600);
    stopSpin();
    heightFromFloor = ultrasonic.MeasureInCentimeters();
}

void loop() {
    int greenButtonValue = analogRead(buttonPinGreen);
    int blueButtonValue = analogRead(buttonPinBlue);

    int greenButtonState = getButtonState(greenButtonValue);
    int blueButtonState = getButtonState(blueButtonValue);

    long newHeight = ultrasonic.MeasureInCentimeters();
    delay(50);
 
    if (isClean(newHeight)) {
        heightFromFloor = newHeight;
    }    
    Serial.println(heightFromFloor);
    
    switch (state) {
      
      case REST:
        if (blueButtonState == ON) {
          state = SPINNING_UP;
          spinUp();
          delay(500);
        } else if (greenButtonState == ON) {
          state = SPINNING_DOWN;
          spinDown();
          delay(200);
        }
        break;

      case SPINNING_UP:
        if (blueButtonState == ON || 
            greenButtonState == ON ||
            heightFromFloor >= TOP_HEIGHT) {
          state = REST;
          stopSpin();
          delay(200);
        }
        break;
      
      case SPINNING_DOWN:
        if (blueButtonState == ON || 
            greenButtonState == ON ||
            heightFromFloor <= BOTTOM_HEIGHT) {
          state = REST;
          stopSpin();
          delay(200);
        }
        break;
    }

    delay(1);
}

bool isClean(long newValue) {
  if ((newValue + 3) < heightFromFloor || (newValue - 3) > heightFromFloor) {
    Serial.print("Rejected: ");
    Serial.println(newValue);
    return false;  
  }
  return true;
}

BUTTON_STATES getButtonState(int value){
   if(value > buttonValueThreshold) {
      return OFF;
   } else {
      return ON;
   }
}

void spinUp() {
  logs("UP");
  digitalWrite(motorChannel1, LOW);
  digitalWrite(motorChannel2, HIGH);
}

void spinDown(){
  logs("DOWN");
  digitalWrite(motorChannel1, HIGH);
  digitalWrite(motorChannel2, LOW);
}

void stopSpin(){
  state = REST;
  logs("stop");
  digitalWrite(motorChannel1, LOW);
  digitalWrite(motorChannel2, LOW);
}

void logs(String l){
  Serial.println(l);
}
void logs(int n){
  Serial.println(n);
}
void logs(unsigned long n){
  Serial.println(n);
}
