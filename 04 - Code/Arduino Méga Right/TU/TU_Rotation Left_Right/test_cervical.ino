#include <Servo.h>

#define OFFSET_INIT_LEFT 10
#define OFFSET_INIT_RIGHT 3

Servo  servo_rolling_neck_left;
Servo  servo_rolling_neck_right;

int angle_init = 90;
int angle_courant = angle_init;

void setup()
{
    servo_rolling_neck_left .attach(13);
    servo_rolling_neck_right .attach(12);
    servo_rolling_neck_left.write(modify_angle_left(angle_init)); //angle init left = 85
    servo_rolling_neck_right.write(modify_angle_right(angle_init));  //angle init right = 70
    
    rotate_clavicule(90);
}

void loop()
{
    
}


void rotate_clavicule (int angle)
{
    if (angle>= 180)
    {
        angle = 180;
    }
    if (angle<= 0)
    {
        angle = 0;
    }
    servo_rolling_neck_left.write(modify_angle_left(angle));
    servo_rolling_neck_right.write(180 - modify_angle_right(angle));
    angle_courant = angle;
    delay(15);
}


int modify_angle_left(int angle_left_order)
{
   return angle_left_order + OFFSET_INIT_LEFT;
}

int modify_angle_right(int angle_right_order)
{
   return angle_right_order + OFFSET_INIT_RIGHT;
}