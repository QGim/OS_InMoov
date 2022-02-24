#include <Arduino_FreeRTOS.h>
#include <Servo.h>

#define MouthServo 6 // pin du servo bouche
#define LineIn 3 // pin LineIn

void SyncroVocal_Task(void*pvParameters);
void NeoPixelLed_Task(void*pvParameters);

void InitGlobal(void);
void InitVocalTask(void);
void InitNeopixelLedTask(void);

Servo obj_servoMouth;


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

  obj_servoMouth.write(55);

  xTaskCreate(SyncroVocal_Task, "Vocal", 128, NULL, 2, NULL);
}

void InitNeopixelLedTask(void)
{
  xTaskCreate(NeoPixelLed_Task, "Noeopixel", 128, NULL, 2, NULL);
}

void NeoPixelLed_Task(void*pvParameters)
{

}

void SyncroVocal_Task(void*pvParameters)
{
  int secondDetection = 1; //
  int read_val = 0; // variable to store the read value
  int i = 0;
  int pos = 55; // variable to store the servo position
  int boucheStatus = 0;
  int actionBouche = 0;

  unsigned long timeofdetect;
  char delayFlag = 0;
  unsigned long v_delay = 1;
  unsigned long v_time;

  if (delayFlag == 0)
  {
    read_val = analogRead(LineIn);

    if (read_val < 630 || read_val > 680 ) // recherche valeur entre 665 et 680 ( a ajuster si besoin )

    {
      boucheStatus = 1; // bouche fermée

    }
    else // tant que

    {
      i++; // la valeur entre 630 et 680 est pas trouvée
    }

    if (i >= secondDetection)
    {
      i = 0;
      boucheStatus = 0;
    }
  }
  if (boucheStatus == 0 && actionBouche == 0)
  {
    if (delayFlag == 0)
    {
      obj_servoMouth.write(95);
      v_time = millis();
      delayFlag = 1;
    }
    delay(40); //1

    if (v_time + v_delay < millis() and delayFlag == 1)
    {
      obj_servoMouth.write(55);
      v_time = millis();
      delayFlag = 2;
    }
    delay(40); //2

    if (v_time + v_delay < millis() and delayFlag == 2)
    {
      actionBouche = 1;
      v_time = millis();
      delayFlag = 0;
    }
  }

  if ((boucheStatus == 1 && actionBouche == 1) or delayFlag == 3)
  {
    if (delayFlag == 0)
    {
      delayFlag = 3;
      obj_servoMouth.write(55);
      v_time = millis();
      delay(40); // 3
    }
    if (v_time + v_delay < millis())
    {
      actionBouche = 0;
      v_time = millis();
      delayFlag = 0;
    }
  }
}
