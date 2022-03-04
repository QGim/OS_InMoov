#include <Adafruit_NeoPixel.h>
#include <Arduino_FreeRTOS.h>
#include "return_state.h"
#include "GestionArduinoNano.h"
#include <queue.h>
#include <Servo.h>


#define MouthServoPin 6 // pin du servo bouche
#define LineInPin A0 // pin LineIn
#define NeoPixelPin 9 //
#define NB_LEDS 3

void SyncroVocal_Task(void*pvParameters);
void NeoPixelLed_Task(void*pvParameters);
void SerialTask(void*pvParameters);

ETAT InitGlobal(void);
ETAT InitVocalTask(void);
ETAT InitNeopixelLedTask(void);
ETAT InitSerialTask(void);

Servo obj_servoMouth;
Adafruit_NeoPixel strip = Adafruit_NeoPixel(NB_LEDS, NeoPixelPin, NEO_GRB + NEO_KHZ800); //déclaration objet neopixel



void setup()
{
  ETAT state;
  state = ETAT_OK;

  TXSerial sendState;

  state = InitGlobal();
  if (state != ETAT_OK)
  {
    
    return -1;
  }

  state = InitSerialTask();
  if (state != ETAT_OK)
  {
    //mettre etat dans struct
    return -1;
  }

  state = InitVocalTask();
  if (state != ETAT_OK)
  {
    //mettre etat dans struct
    return -1;
  }

  state = InitNeopixelLedTask();
  if (state != ETAT_OK)
  {
    //mettre etat dans struct
    return -1;
  }

  Serial.println("Init OK");
  //TODO: Ajouter queue pour renvoyer state au serial(utiliser structure)

}

void loop() {
  //Do nothing

}

//Initialisation arduino global
ETAT InitGlobal(void)
{
  ETAT state;
  analogReference(EXTERNAL);
  state = ETAT_OK;

  return state;
}

//Initialisation tache serial pour les transfert d'info à RPI
ETAT InitSerialTask(void)
{
  ETAT state;
  state = ETAT_ERROR;
  Serial.begin(115200); //init serial
  QueueHandle_t queue_neopixel, queue_vocal;
  int queueSize = 10;

  queue_neopixel = xQueueCreate( queueSize, sizeof( int ));
  if (queue_neopixel != NULL)
  {
    state = ETAT_OK;
  }
  queue_vocal = xQueueCreate( queueSize, sizeof( int ));
  if (queue_vocal != NULL)
  {
    state = ETAT_OK;
  }
  
  //init serial task
  if(xTaskCreate(SerialTask, "Serial", 128, NULL, 2, NULL)==pdPASS)
  {
    state = ETAT_OK;
  }
  
  return state;
}


ETAT InitVocalTask(void)
{
  ETAT state;
  state = ETAT_ERROR;

  pinMode(MouthServoPin, OUTPUT);
  obj_servoMouth.attach(MouthServoPin);
  obj_servoMouth.write(55);
  if (xTaskCreate(SyncroVocal_Task, "Vocal", 128, NULL, 2, NULL) == pdPASS)
  {
    state = ETAT_OK;
  }
  return state;
}

ETAT InitNeopixelLedTask(void)
{
  ETAT state;
  state = ETAT_ERROR;
  
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'

  if(xTaskCreate(NeoPixelLed_Task, "Noeopixel", 128, NULL, 2, NULL)==pdPASS)
  {
    state = ETAT_OK;
  }
  
  return state;
}








void SerialTask(void*pvParameters)
{
  (void)pvParameters;

  //changer la couleur et mode du neopixel //RX
  //renvoyer l'angle du servo
  //renvoyer etat init des differentes taches pour informer RPI pour séquence d'init.
  for (;;)
  {

  }

}

void NeoPixelLed_Task(void*pvParameters)
{

  (void)pvParameters;

  int alpha = 0; // Current value of the pixels
  int dir = 1; // Direction of the pixels... 1 = getting brighter, 0 = getting dimmer
  int flip; // Randomly flip the direction every once in a while
  int minAlpha = 10; // Min value of brightness
  int maxAlpha = 100; // Max value of brightness
  int alphaDelta = 2; // Delta of brightness between times through the loop

  for (;;)
  {


    flip = random(32);
    if (flip > 20) {
      dir = 1 - dir;
    }
    // Some example procedures showing how to display to the pixels:
    if (dir == 1) {
      alpha += alphaDelta;
    }
    if (dir == 0) {
      alpha -= alphaDelta;
    }
    if (alpha < minAlpha) {
      alpha = minAlpha;
      dir = 1;
    }
    if (alpha > maxAlpha) {
      alpha = maxAlpha;
      dir = 0;
    }
    vTaskDelay(3);
    // Change the line below to alter the color of the lights
    // The numbers represent the Red, Green, and Blue values
    // of the lights, as a value between 0(off) and 1(max brightness)
    //
    // EX:
    //


    colorWipe(strip.Color(alpha, 0, alpha / 2)); // Pink
    //colorWipe(strip.Color(0, 0, alpha)); // Blue
  }
}

void SyncroVocal_Task(void*pvParameters)
{

  (void)pvParameters;

  int secondDetection = 1; //
  int read_val; // variable to store the read value
  int i = 0;
  int pos = 55; // variable to store the servo position
  int boucheStatus = 0;
  int actionBouche = 0;

  unsigned long timeofdetect;
  char delayFlag = 0;
  unsigned long v_delay = 1;
  unsigned long v_time;

  for (;;)
  {
    if (delayFlag == 0)
    {
      read_val = analogRead(LineInPin);

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
      vTaskDelay(40); //1

      if (v_time + v_delay < millis() and delayFlag == 1)
      {
        obj_servoMouth.write(55);
        v_time = millis();
        delayFlag = 2;
      }
      vTaskDelay(40); //2

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
        vTaskDelay(40); // 3
      }
      if (v_time + v_delay < millis())
      {
        actionBouche = 0;
        v_time = millis();
        delayFlag = 0;
      }
    }
  }
}

void colorWipe(uint32_t c)
{
  for (uint16_t i = 0; i < strip.numPixels(); i++)
  {
    strip.setPixelColor(i, c);
    strip.show();
  }
}
