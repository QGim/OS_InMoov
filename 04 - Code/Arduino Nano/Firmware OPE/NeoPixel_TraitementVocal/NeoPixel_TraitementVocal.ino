
#include <Arduino_FreeRTOS.h>
#include <queue.h>
#include <Servo.h> 
#include "status.h"
#include "NeoPixel.h"
#include "order.h"

#define MAXMESSAGE 100
#define servoMouthPin 6
#define HPPin_In A3

/*
 * Ajout des prototypes des taches RTOS
 */
void VocalSyncTask(void *pvParameters);
void NeoPixelTask(void *pvParameters);
void ControllerTask(void *pvParameters);

void setup()
{
  Serial.begin(115200);
  
  xTaskCreate(VocalSyncTask, (const char *const)"SyncroVocal", 128, NULL, 3, NULL);
  xTaskCreate(NeoPixelTask, (const char *const)"NeoPixel", 128, NULL, 1, NULL);
  xTaskCreate(ControllerTask, (const char *const)"CtrlNano", 128, NULL, 3, NULL);

  vTaskStartScheduler();
}

void loop()
{
}

void VocalSyncTask(void *pvParameters)
{
  (void)pvParameters;
  u16 test;
  Servo myservo;                 
  int     MIN = 400; //value when sound is detected
  int     MAX = 1000;  //max value when sound is detected
  int     SecondDetection = 2; 
  int     val = 0;    
  int     i = 0;
  int     posMax = 145;    
  int     posMin = 60;
  int     pos = posMin; 
  int     BoucheStatus = 0;
  int     ActionBouche = 0;
  int     Repos = 0;
  int     CompteurRepos = 0;
  String  dbg;
  analogReference(INTERNAL);
  myservo.attach(servoMouthPin);
  myservo.write(posMin);
  for(;;)
  {
    val = analogRead(HPPin_In);
    pos=map(val, MIN, MAX, posMin, posMax); 
    if (val > MIN ) // if values detected : speaker voltage
    {
      i++;
    }
    else  
    {
     BoucheStatus = 1; // closed mouth
    }
    if (i>=SecondDetection)
    {
      i=0;
      BoucheStatus = 0;
    }
    if (BoucheStatus == 0 && ActionBouche == 0)
    {
      if (Repos==0)
      {
        delay(0.5);
      }
      ActionBouche = 1;
      myservo.write(pos);
      CompteurRepos=0;
      delay(0.1);
    }
    if (BoucheStatus == 1 && ActionBouche == 1)
    {
      Repos = 0;
      CompteurRepos = 0;
      ActionBouche =0;
    }
    if (CompteurRepos == 100 && Repos == 0)
    {
     myservo.write(posMin); 
     Repos=1;
    }
    CompteurRepos+=1;    
    delay(1);
  }
}




void NeoPixelTask(void *pvParameters)
{
  (void)pvParameters;
  for(;;)
  {
    
  }
}



 
void ControllerTask(void *pvParameters)
{
 (void)pvParameters;
  String order;
  ctx_order order_data;
 
  for(;;)
  {
    if(Serial.available())
    {
       char c = Serial.read();
       if( c == '\n')
       {
          parseOrder(order,&order_data);
          order = "";
       }
       else
       {
          order += c;
       }
    }
  }
}


void parseOrder(String ord,ctx_order *order_data)
{
  String part1; // nb leds
  String part2; // mode d'allumage
  String part3; // Nb params

  part1 = ord.substring(0,ord.indexOf(" "));
  int nb_leds = part1.toInt();
 
  part2 = ord.substring(ord.indexOf(" ") + 1);
  part3 = ord.substring(ord.indexOf(" ") + 1);

  if(nb_leds == 0) // Attention si aucune led selectionné ->mode eteint par default et mode forcé à 0
  {
    order_data.nb_leds = nb_leds;
    order_data.mode = 0;
    order_data.params = 0;
  }
  else if(nb_leds > 0) //Tout est prix en compte
  {
    order_data.nb_leds = nb_leds;
    
    int mode = part2.toInt();
    order_data.mode = mode;
  
    
  }
  else if(nb_leds < 0) // erreurs params (ERANGE)
  {
    
  }
  else //Commande Inconnu
  {
    
  }
}
