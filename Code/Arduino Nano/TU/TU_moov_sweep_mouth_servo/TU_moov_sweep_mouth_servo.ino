
#include <Servo.h>

#define SERVO_BOUCHE 6
#define INIT_ANGLE 58 //angle de la bouche en init (bouche fermé)
#define ANGLE_MIN 58 //angle de la bouche minimal (bouche fermé)
#define ANGLE_MAX 145 //angle de la bouche maximal (bouche ouverte)

Servo mouth; 


int angle_mouth; // variable to store the servo position

void setup()
{
  mouth.attach(SERVO_BOUCHE);  // attaches the servo on pin 9 to the servo object
  mouth.write(INIT_ANGLE);
  
}

void loop() 
{
  for (angle_mouth = ANGLE_MIN; angle_mouth <= ANGLE_MAX; angle_mouth += 1) 
  { 
    // in steps of 1 degree
    mouth.write(angle_mouth);              // tell servo to go to position in variable 'pos'
    delay(10);                       // waits 15 ms for the servo to reach the position
  }
  for (angle_mouth = ANGLE_MAX; angle_mouth >= ANGLE_MIN; angle_mouth -= 1)
  { 
    mouth.write(angle_mouth);              // tell servo to go to position in variable 'pos'
    delay(10);                       // waits 15 ms for the servo to reach the position
  }
}
