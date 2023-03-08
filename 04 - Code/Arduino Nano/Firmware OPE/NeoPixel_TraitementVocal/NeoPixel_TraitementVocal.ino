#include <Arduino_FreeRTOS.h>
#include <queue.h>
#include <Servo.h> 
#include "status.h"
#include "order.h"
#include "MsgCodec.h"

#define MAXMESSAGE 100
#define servoMouthPin 6
#define HPPin_In A3

/*
 Ajout des prototypes des taches RTOS
*/
void VocalSyncTask(void *pvParameters);
void NeoPixelTask(void *pvParameters);
void ReadMsg(void *pvParameters);



//Sturcture corespondant aux ordres
struct Ctx_order order_data;
byte recvBuffer[MAX_MSG_SIZE];

//Setup des trois taches :
/*
Syncro vocal: 
permet la syncro entre le signal vocal analogique 
en un signal PWM pour le servo qui bouge la bouche

Néo Pixel : 
Tache permetant d'allumer ou d'eteinde cercle de led 
NéoPixel et traitants les ordres en provenance d'une queue.

CtrlNano :
Permet de creer un parser permettant de recuperer les ordres par la raspberry
*/
void setup()
{
  Serial.begin(9600);

while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB, on LEONARDO, MICRO, YUN, and other 32u4 based boards.
  }

  xTaskCreate(VocalSyncTask,"SyncroVocal", 128, NULL, 2, NULL);
  xTaskCreate(NeoPixelTask,"NeoPixel", 128, NULL, 3, NULL);
  xTaskCreate(ReadMsg, "CtrlNano", 128, NULL, 1, NULL);
}



void loop()
{
}




void VocalSyncTask(void *pvParameters __attribute__((unused)))
{
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




void NeoPixelTask(void *pvParameters __attribute__((unused)))
{
  for(;;)
  {
    vTaskDelay(1);
  }
}



 
void ReadMsg(void *pvParameters __attribute__((unused)))
{
  //for process FreeRTOS
  for(;;)
  {
    Serial.println(F("ReadMsg"));
    vTaskDelay(1);
  }
}


void receiveMsg()
{
  int msg_size = 0;
  int byteCounter = 0;
  int bytesAvailable = Serial.available();
    if(bytesAvailable>0)
    {
      for (int i = 0; i < bytesAvailable; i++) 
      {
        // read the incoming values
        unsigned char receiveByte = Serial.read();
        ++byteCounter;
        // Verifier si le premier byte est le MAGIC_NUMBER
        if(byteCounter == 1 && receiveByte != MAGIC_NUMBER)
        {
          byteCounter = 0;
          Serial.print(ETAT_ESERIAL);
        }

        if (byteCounter == 2) 
        {
				// recuperation de la taille du message
				// verification si le message est superieur à 64
          if (receiveByte > MAX_MSG_SIZE) 
          {
            byteCounter = 0;
            Serial.print(ETAT_ESERIAL);
            continue;
          }
				  msg_size = receiveByte;
        }
        if (byteCounter > 2)
        {
          recvBuffer[byteCounter - 3] = receiveByte;
        }

      }
    }
}


void processMsg(String ord,Ctx_order* order_data)
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
    order_data->nb_leds= nb_leds;
    order_data->mode = 0;
  }
  else if(nb_leds > 0) //Tout est prix en compte
  {
    order_data->nb_leds = nb_leds;
    
    int mode = part2.toInt();
    order_data->mode = mode;

    
  }
  else if(nb_leds < 0) // erreurs params (ERANGE)
  {
    
  }
  else //Commande Inconnu
  {
    
  }
}
