
#include <Arduino_FreeRTOS.h>
#include "status.h"
#include "NeoPixel.h"
#include "request.h"
#define MAXMESSAGE 100


void VocalSyncTask(void *pvParameters);
void NeoPixelTask(void *pvParameters);
void ControllerTask(void *pvParameters);


void setup()
{
  xTaskCreate(VocalSyncTask, (const char *const)"SyncroVocal", 128, NULL, 2, NULL);
  xTaskCreate(NeoPixelTask, (const char *const)"NeoPixel", 128, NULL, 2, NULL);
  xTaskCreate(ControllerTask, (const char *const)"CtrlNano", 128, NULL, 2, NULL);

}

void loop()
{
}

void VocalSyncTask(void *pvParameters)
{
  (void)pvParameters;
  while (1)
  {

  }
}

void NeoPixelTask(void *pvParameters)
{
  (void)pvParameters;
  while (1)
  {

  }
}

void ControllerTask(void *pvParameters)
{

  Serial.begin(115200);

  //Création de la requète

  char request[MAXMESSAGE];
  char separateur[] = "-";
  char *tokenPtr;
  int charsRead;
  struct Requete req;

  (void)pvParameters;

  while (1)
  {
    if (Serial.available() > ETAT_OK)
    {
      charsRead = Serial.readBytesUntil('\n', request, MAXMESSAGE - 1);
      request[charsRead] = '\0';   // Now it's a string

      Serial.print("Target string:  ");
      Serial.println(request);

      tokenPtr = strtok(request, separateur);

      while (tokenPtr != '\0')
      {
        Serial.println(tokenPtr);
        tokenPtr = strtok('\0', separateur);
      }
    }
  }
}
