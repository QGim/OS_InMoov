#include <Servo.h>

Servo myservo;

void setup() {
  Serial.begin(115200);
  myservo.attach(3);
  myservo.write(80);
}

void loop() {
  if(Serial.available())
  {
    int res = Serial.read();
    myservo.write(res);
  }
}
