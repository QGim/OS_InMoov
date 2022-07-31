/*
  AnalogReadSerial

  Reads an analog input on pin 0, prints the result to the Serial Monitor.
  Graphical representation is available using Serial Plotter (Tools > Serial Plotter menu).
  Attach the center pin of a potentiometer to pin A0, and the outside pins to +5V and ground.

  This example code is in the public domain.

  http://www.arduino.cc/en/Tutorial/AnalogReadSerial
*/
#include <Servo.h>

#define D_CAPT_POUCE  A3    //A1
#define D_CAPT_INDEX  A4    //A2
#define D_CAPT_MAJEUR   A5   //A3
#define D_CAPT_ANNU     A6   //A4
#define D_CAPT_AURI     A7   //A5

#define D_POUCE   2
#define D_POUCE_ANGL      80
#define D_POUCE_ANGL_MIN    10
#define D_POUCE_ANGL_MAX    120

struct Capteur_Main_D
{
  int pou;
  int ind;
  int maj;
  int annu;
  int auri;
};


Capteur_Main_D capt_main_d;

Servo myservo; 
short angle = 0;
void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
  myservo.attach(D_POUCE);
  myservo.write(D_POUCE_ANGL); 
}

// the loop routine runs over and over again forever:
void loop() {
  // read the input on analog pin 0:
   capt_main_d.pou = analogRead(D_CAPT_POUCE);
   capt_main_d.ind = analogRead(D_CAPT_INDEX);
   capt_main_d.maj =  analogRead(D_CAPT_MAJEUR);
   capt_main_d.annu = analogRead(D_CAPT_ANNU);
   capt_main_d.auri = analogRead(D_CAPT_AURI);
  // print out the value you read:
  Serial.print(capt_main_d.pou);Serial.print(":");Serial.print(capt_main_d.ind);Serial.print(":");Serial.print(capt_main_d.maj);Serial.print(":");Serial.print(capt_main_d.annu);Serial.print(":");Serial.println(capt_main_d.auri);
  delay(1);        // delay in between reads for stability

  for (angle = D_POUCE_ANGL_MIN; angle <= D_POUCE_ANGL_MAX; angle += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    myservo.write(angle);              // tell servo to go to position in variable 'pos'
    if(capt_main_d.pou >= 15)
     {
       for (angle = D_POUCE_ANGL_MAX; angle >= D_POUCE_ANGL_MIN; angle -= 1) { // goes from 180 degrees to 0 degrees
       myservo.write(angle);              // tell servo to go to position in variable 'pos'
        delay(3);
     }
  }
    delay(3);                       // waits 15ms for the servo to reach the position
  }
  for (angle = D_POUCE_ANGL_MAX; angle >= D_POUCE_ANGL_MIN; angle -= 1) { // goes from 180 degrees to 0 degrees
    myservo.write(angle);              // tell servo to go to position in variable 'pos'
    delay(3);                       // waits 15ms for the servo to reach the position
  }
}
