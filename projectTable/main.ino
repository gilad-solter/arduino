int joystickPinY = A0;
int joystickPinX = A1;
int joystickValueY = 0;
int joystickValueX = 0;

void setup(){
    // pinMode(joystickPin, INPUT);
    Serial.begin(9600);
}

void loop() {
    joystickValueX = analogRead(joystickPinX);
    joystickValueY = analogRead(joystickPinY);
    Serial.print("Joystick value X: ");
    Serial.print(joystickValueX, DEC);
    Serial.print(", Joystick value Y: ");
    Serial.println(joystickValueY, DEC);
    Serial.println(" ");
}