
#include <Arduino_FreeRTOS.h>
#include <Servo.h> 
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
  Serial.begin(115200);
}

void loop()
{
}

void VocalSyncTask(void *pvParameters)
{
  (void)pvParameters;
  Servo myservo;
  #define servoPin 6 
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
  //Création de la requète
  const size_t request_size = 256;
  const char separateur[2] = " ";
  static char input_buffer[request_size];
  static uint8_t i, j;
  struct Requete req;
  char *token;
  char *temp[10] = {};

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
        j = 0;
        Serial.print("Requete global recue:");
        Serial.println(input_buffer);
        //Add  security request
        if (input_buffer[0] == '\0' || input_buffer[0] ==' ')
        {
          req.port = "";
          req.nb_leds = "";
          req.mode = "";
          req.func = "";
          req.nb_params = "";
          Serial.println(ETAT_EAGAIN);
        }
        else
        {
          /*obtention du premier token */
          token = strtok(input_buffer, separateur);
          req.port = token;
          /* obtention des autres tokens */
          while ( token != NULL )
          {
            token = strtok(NULL, separateur);
            temp[j] = token;
            j++;
          }
          req.nb_leds = temp[0];
          req.mode = temp[1];
          req.func = temp[2];
          req.nb_params = temp[3];

          if (req.nb_params == "0")
          {
            
          }
          Serial.println(req.port);
          Serial.println(req.nb_leds);
          Serial.println(req.mode);
          Serial.println(req.nb_params);
        }
      }
    }
  }
}
