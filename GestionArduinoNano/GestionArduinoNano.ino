#include <Arduino_FreeRTOS.h>
#include <Servo.h>

#define MouthServo 6 // pin du servo bouche
#define LineIn 3 // pin LineIn

void SyncroVocal_Task(void*pvParameters);
void NeoPixelLed_Task(void*pvParameters);

void InitGlobal(void);
void InitVocalTask(void);
void InitNeopixelLedTask(void);

int VOICESecondDetection = 1; //
int VOICEval = 0; // variable to store the read value
int VOICEi = 0;
int VOICEpos = 55; // variable to store the servo position
int VOICEBoucheStatus = 0;
int VOICEActionBouche = 0;

unsigned long timeofdetect;
char VOICEdelayFlag = 0;
unsigned long VOICEdelay = 1;
unsigned long VOICEtime;

void setup() 
{
  InitGlobal();
  InitVocalTask();
  InitNeopixelLedTask();
}

void loop() {
 //Do nothing

}
void InitGlobal(void)
{
  analogReference(EXTERNAL);
  Serial.begin(115200);
}

void InitVocalTask(void)
{
 Servo obj_servoMouth;
 pinMode(MouthServo, OUTPUT);
 obj_servoMouth.attach(MouthServo);
 
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
