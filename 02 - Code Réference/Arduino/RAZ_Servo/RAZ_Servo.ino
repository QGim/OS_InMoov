#include <Servo.h>
 
    // variable to store the servo posit

Servo myservo;

// twelve servo objects can be created oion

void setup() 
{
   myservo.attach(17);
   myservo.write(0); 
}
void loop()
{

}
