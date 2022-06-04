#include <Servo.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NB_SERVOS  4

Servo bicep,rotate,epaule,omoplate;
int ports_capteurs[NB_SERVOS] = {20,19,18,17};
char commandChar;
void setup()
{
  Serial.begin(115200);
  bicep.attach(ports_capteurs[0]);
  rotate.attach(ports_capteurs[1]);
  epaule.attach(ports_capteurs[2]);
  omoplate.attach(ports_capteurs[3]);
}

void loop() 
{
  while (Serial.available() > 0) 
  {
     String value=Serial.readString();
     commandChar = value.charAt(0);
     String subvalue2 = value.substring(1);
    switch(commandChar)
    {
      case'a':
      //Serial.println(subvalue2.toInt());
      bicep.write(subvalue2.toInt());
      break;
      case'b':
      //Serial.println(subvalue2.toInt());
      rotate.write(subvalue2.toInt());
      break;
      case'c':
      //Serial.println(subvalue2.toInt());
      epaule.write(subvalue2.toInt());
      break;
      case'd':
      //Serial.println(subvalue2.toInt());
      omoplate.write(subvalue2.toInt());
      break;
  } 
  } 
}
