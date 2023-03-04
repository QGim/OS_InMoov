#include <Servo.h>

Servo  servo_articulatng_neck;

void setup()
{
  servo_articulatng_neck.attach(10);
  servo_articulatng_neck.write(90);
}

void loop()
{
    
}
