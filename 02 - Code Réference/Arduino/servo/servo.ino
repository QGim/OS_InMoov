#include <Servo.h>

#define SERVO_COUDE_D 7
#define SERVO_EPAULE_D 8

Servo Serv_coude_D,Serv_epaule_D;


int positionCoudeD =0; //min =0° et max=80°


void setup()
{
  InitCoudeD();
  
  
  
  
}

void loop()
{
 
}


void InitCoudeD()
{
  
  Serv_coude_D.attach(SERVO_EPAULE_D);
  Serv_coude_D.write(positionCoudeD);
}
