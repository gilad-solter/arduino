



void setup() {
 Serial.begin(9600);
 Serial.println("Start");
 pinMode(13, OUTPUT);
}

void loop() {
  for (int i = 1; i<10; i++) {
    for (int j = 1; j<=i; j++){
        blink(500);
    }  
    delay(1000);
  }

}


void blink(int l) {
    digitalWrite(13, HIGH);
    delay(l);
    digitalWrite(13, LOW);
    delay(l-300);
}
