
#include <Arduino_FreeRTOS.h>
#include "status.h"
#include "NeoPixel.h"


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
  int input_buffer = 0;
  (void)pvParameters;
  while (1) 
  {
    if(Serial.available()>ETAT_OK)
    {
      input_buffer = Serial.read();
    }
    Serial.println(input_buffer,DEC);
    
  }
}