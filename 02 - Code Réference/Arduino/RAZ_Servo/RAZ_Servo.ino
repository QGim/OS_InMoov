#include <Servo.h>

    // variable to store the servo posit

Servo myservo;
Servo myservo2;// create servo object to control a servo
// twelve servo objects can be created oion

void setup() 
{
   myservo2.attach(17);
   myservo2.write(5); 

}
void loop()
{
}
