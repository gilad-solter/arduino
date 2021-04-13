#include <Arduino.h>
#include <arduino-timer.h>

auto timer = timer_create_default();

int baseValue = 510;
int joystickValueY = baseValue;
int joystickValueX = baseValue;
int thresholdValueDown = baseValue - 200;
int thresholdValueUp = baseValue + 200;

int clickThreshold = 1000;

unsigned long sec = 1000;
unsigned long longMoveDelayUp = 80 * sec;
unsigned long longMoveDelayDown = 65 * sec;

int joystickPinY = A3;
int joystickPinX = A4;
uint8_t motorChannel1 = 8;
uint8_t motorChannel2 = 7;

enum SpinDirection {
  UP,
  DOWN
};

enum State {
  REST,
  SPINNING
};

State state = REST;
long runningTime;

void setup(){
    pinMode(motorChannel1, OUTPUT);
    pinMode(motorChannel2, OUTPUT);
    Serial.begin(9600);
    stopSpin();
}

void loop() {
    timer.tick();
    joystickValueY = analogRead(joystickPinY);
    joystickValueX = analogRead(joystickPinX);    
    
    if (joystickValueX < thresholdValueDown){
      longSpinNaive(UP);
    } else if (joystickValueX > thresholdValueUp){
      longSpinNaive(DOWN);      
    } else if (joystickValueY > clickThreshold ) {
      printAndStop();
    } else if(joystickValueY < thresholdValueDown) {
      spinDown();      
    } else if(joystickValueY > thresholdValueUp) {
      spinUp();    
    } else if (state == REST) {
        stopSpin();  
    }    
    delay(1);
}

void printAndStop() {
  logs("Timer done after: ");
  logs(millis() - runningTime);  
  stopSpin();
}

void longSpinNaive(SpinDirection spinDirection) {
  if (state != SPINNING) {
    logs("going long!");
    state = SPINNING;    
    runningTime = millis();
    if (spinDirection == UP) {
      spinUp();
      timer.in(longMoveDelayUp, printAndStop);
    } else {
      spinDown();
      timer.in(longMoveDelayDown, printAndStop); 
    }
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
  timer.cancel();
  state = REST;
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
