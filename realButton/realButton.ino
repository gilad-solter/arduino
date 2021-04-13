const int buttonPin = 2;     // the number of the pushbutton pin



int buttonState = 0;   
int ledPin = 9;

void setup() {
  Serial.begin(9600);
  // initialize the pushbutton pin as an input:
  pinMode(buttonPin, INPUT);
  pinMode(ledPin, OUTPUT);
  Serial.println("start");
}

void loop() {
  
  // read the state of the pushbutton value:
  int newButtonState = digitalRead(buttonPin);

  if (buttonState == HIGH) {
    digitalWrite(ledPin, HIGH);
  } else {
    digitalWrite(ledPin, LOW);
  }
  
  if (buttonState != newButtonState){
    Serial.print("new: ");     
    Serial.print(newButtonState, DEC);
    Serial.print(", old: ");     
    Serial.println(buttonState, DEC);
    buttonState = newButtonState;
  } 
  delay(1);
}
