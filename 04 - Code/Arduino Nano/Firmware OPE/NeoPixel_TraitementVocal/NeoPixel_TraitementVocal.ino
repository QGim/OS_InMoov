
#include <Arduino_FreeRTOS.h>
#include "status.h"
#include "NeoPixel.h"
#include "request.h"



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
  const size_t request_size = 256;
  String index;
  char separateur = " ";
  static char input_buffer[request_size];
  static uint8_t i;
  struct Requete req;

  (void)pvParameters;

  while (1)
  {
    if (Serial.available() > ETAT_OK)
    {
      char c = Serial.read();
      if ( c != '\n' && i < request_size - 1 )
      {
        input_buffer[i++] = c;
      }
      else
      {
        input_buffer[ i ] = '\0';
        i = 0;
        Serial.print("Requete global recue:");
        Serial.println(input_buffer);
        
        index = strtok(input_buffer," ");
        //req.port = atoi(index);
        Serial.println(index.toInt()); 


        //Serial.print("Port:");
        //Serial.println(req.port,DEC);           

        Serial.println("\n\n\n");

        Serial.println("\n\n\n");
      }
    }
  }
}
