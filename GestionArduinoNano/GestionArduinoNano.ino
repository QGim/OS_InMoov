#include <Arduino_FreeRTOS.h>
#include <Servo.h>

#define VoltAmpliGnd 2
#define VoltAmpliVolt 3
#define MouthPin 5
#define HPpin        0    // analog speaker input

void SyncroVocal_Task(void*pvParameters);
void NeoPixelLed_Task(void*pvParameters);
void GlobalInit(void);
void InitVocalTask(void);
void InitNeopixelLedTask(void);

int     MIN = 10; //value when sound is detected
int     MAX = 500;  //max value when sound is detected
int     SecondDetection = 2; 
int     val = 0;    
int     i = 0;
int     posMax = 100;    
int     posMin = 65;
int     pos = posMin;
int     BoucheStatus = 0;
int     ActionBouche = 0;
int     Repos = 0;
int     CompteurRepos = 0;
String  dbg;
Servo mouth;


void setup() 
{
  
  InitVocalTask();
  InitNeopixelLedTask();
}

void loop() {
 //Do nothing

}
void GlobalInit(void)
{
  
  analogReference(INTERNAL);
  Serial.begin(115200);
}

void InitVocalTask(void)
{

  pinMode(VoltAmpliGnd, OUTPUT);
  pinMode(VoltAmpliVolt, OUTPUT);
  digitalWrite(VoltAmpliGnd, LOW);
  digitalWrite(VoltAmpliVolt, HIGH);
  mouth.attach(MouthPin);
 xTaskCreate(SyncroVocal_Task,"Vocal",128,NULL,2,NULL);
}

void InitNeopixelLedTask(void)
{
  
   xTaskCreate(NeoPixelLed_Task,"Noeopixel",128,NULL,2,NULL);
}

void NeoPixelLed_Task(void*pvParameters)
{
  
}

void SyncroVocal_Task(void*pvParameters)
{
  
}
