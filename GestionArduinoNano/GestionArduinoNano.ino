#include <Adafruit_NeoPixel.h>
#include <Arduino_FreeRTOS.h>
#include "return_state.h"
#include "GestionArduinoNano.h"
#include <queue.h>
#include <Servo.h>


#define MouthServoPin 6 // pin du servo bouche
#define LineInPin A3 // pin LineIn
#define NeoPixelPin 9 //
#define NB_LEDS 16
#define QUEUE_SIZE 10

void SyncroVocal_Task(void*pvParameters);
void NeoPixelLed_Task(void*pvParameters);
void SerialTask(void*pvParameters);

ETAT InitGlobal(void);
ETAT InitVocalTask(void);
ETAT InitNeopixelLedTask(void);
ETAT InitSerialTask(void);

Servo obj_servoMouth;
Adafruit_NeoPixel strip = Adafruit_NeoPixel(NB_LEDS, NeoPixelPin, NEO_GRB + NEO_KHZ800); //déclaration objet neopixel
QueueHandle_t queue_neopixel, queue_vocal, queue_init = NULL;




void setup()
{
  ETAT state;
  state = ETAT_OK;
  struct SerialData SerData;

  queue_neopixel = xQueueCreate( QUEUE_SIZE, sizeof( struct SerialData));
  if (queue_neopixel != NULL)
  {
    state = ETAT_OK;
  }
  queue_vocal = xQueueCreate( QUEUE_SIZE, sizeof( struct SerialData));
  if (queue_vocal != NULL)
  {
    state = ETAT_OK;
  }

  queue_init = xQueueCreate( QUEUE_SIZE, sizeof( struct SerialData));
  if (queue_init != NULL)
  {
    state = ETAT_OK;
  }


  state = InitGlobal();
  if (state != ETAT_OK)
  {
    SerData.etat = state;
  }

  state = InitSerialTask();
  if (state != ETAT_OK)
  {

    SerData.etat = state;
  }

  state = InitVocalTask();
  if (state != ETAT_OK)
  {
    SerData.etat = state;
  }

  state = InitNeopixelLedTask();
  if (state != ETAT_OK)
  {
    SerData.etat = state;
  }


  if (state == ETAT_OK)
  {
    SerData.etat = state;
  }

  xQueueSend(queue_init, &SerData, portMAX_DELAY);

}

void loop() {
  //Do nothing

}

//Initialisation arduino global
ETAT InitGlobal(void)
{
  ETAT state;
  state = ETAT_OK;
  analogReference(INTERNAL);
  return state;
}

//Initialisation tache serial pour les transfert d'info à RPI
ETAT InitSerialTask(void)
{
  ETAT state;
  state = ETAT_ERROR;
  Serial.begin(115200); //init serial

  //init serial task
  if (xTaskCreate(SerialTask, "Serial", 128, NULL, 2, NULL) == pdPASS)
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

  if (xTaskCreate(NeoPixelLed_Task, "Noeopixel", 128, NULL, 2, NULL) == pdPASS)
  {
    state = ETAT_OK;
  }

  return state;
}








void SerialTask(void*pvParameters)
{
  (void)pvParameters;
  struct SerialData DataSerialSend;

  //changer la couleur et mode du neopixel //RX
  //renvoyer l'angle du servo
  //renvoyer etat init des differentes taches pour informer RPI pour séquence d'init.
  for (;;)
  {
    xQueueReceive(queue_init, &DataSerialSend, portMAX_DELAY);
    if (DataSerialSend.etat == ETAT_OK)
    {
      Serial.write ("Init OK");
    }
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


    //colorWipe(strip.Color(alpha, 0, alpha / 2)); // Pink
    colorWipe(strip.Color(0, 0, alpha)); // Blue
  }
}

void SyncroVocal_Task(void*pvParameters)
{

  (void)pvParameters;

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

  for (;;)
  {
    val = analogRead(LineInPin);
    pos = map(val, MIN, MAX, posMin, posMax);

    if (val > MIN ) // if values detected : speaker voltage

    {
      i++;
    }
    else
    {
      BoucheStatus = 1; // closed mouth
    }

    if (i >= SecondDetection)
    {
      i = 0;
      BoucheStatus = 0;
    }

    if (BoucheStatus == 0 && ActionBouche == 0)

    {
      if (Repos == 0)
      {
        obj_servoMouth.attach(MouthServoPin);
        delay(1);
      }
      ActionBouche = 1;
      obj_servoMouth.write(pos);
      CompteurRepos = 0;
      delay(1);

    }
    if (BoucheStatus == 1 && ActionBouche == 1)
    {

      Repos = 0;
      CompteurRepos = 0;
      ActionBouche = 0;

    }

    if (CompteurRepos == 100 && Repos == 0)
    {
      obj_servoMouth.write(posMin);
      delay(10);
      obj_servoMouth.detach();
      Repos = 1;
    }

    CompteurRepos += 1;
    delay(1);
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
