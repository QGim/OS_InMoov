#include <Servo.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NB_SERVOS 6

Servo pouce,index,maj,annu,auri,poignet;
int ports_capteurs[NB_SERVOS] = {2,3,4,5,6,7};
char commandChar;
void setup()
{
  Serial.begin(115200);
  pouce.attach(ports_capteurs[0]);
  index.attach(ports_capteurs[1]);
  maj.attach(ports_capteurs[2]);
  annu.attach(ports_capteurs[3]);
  auri.attach(ports_capteurs[4]);
  poignet.attach(ports_capteurs[5]);
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
      case 'a':
      //Serial.println(subvalue2.toInt());
      pouce.write(subvalue2.toInt());
      break;
      case 'b':
      //Serial.println(subvalue2.toInt());
      index.write(subvalue2.toInt());
      break;
      case 'c':
      //Serial.println(subvalue2.toInt());
      maj.write(subvalue2.toInt());
      break;
      case 'd':
      //Serial.println(subvalue2.toInt());
      annu.write(subvalue2.toInt());
      break;
      case 'e':
      //Serial.println(subvalue2.toInt());
      auri.write(subvalue2.toInt());
      break;
      case 'f':
      //Serial.println(subvalue2.toInt());
      poignet.write(subvalue2.toInt());
      break;
    }
  }  
}
