#include <Arduino_FreeRTOS.h>
#include <queue.h>
#include <Servo.h>
#include "status.h"
#include "MsgCodec.h"
#include "InMoovPixel.h"

#define MAXMESSAGE 100
#define servoMouthPin 6
#define HPPin_In A3

/*
 Ajout des prototypes des taches RTOS
*/
void VocalSyncTask(void *pvParameters);
void NeoPixelTask(void *pvParameters);
void ReadMsg(void *pvParameters);

/*Handle des taches*/
TaskHandle_t Handle_Vocal_sync;
TaskHandle_t Handle_Neo_Pixel;
TaskHandle_t Handle_Read_Msg;

/*Déclaring buffer*/
byte recv_cmd_Buffer[MAX_MSG_SIZE];
/*Declaring Queue*/
QueueHandle_t NeoPixel_Queue;

// Setup des trois taches :
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
  Serial.begin(115200);
  // crete queue for task
  NeoPixel_Queue = xQueueCreate(15, sizeof(Neo_Pixel_Info_s));

  if (NeoPixel_Queue != NULL)
  {
    xTaskCreate(NeoPixelTask, "NeoPixel", 128, NULL, 2, &Handle_Neo_Pixel);
    xTaskCreate(ReadMsg, "CtrlNano", 128, NULL, 3, &Handle_Read_Msg);
  }
  xTaskCreate(VocalSyncTask, "SyncroVocal", 128, NULL, 1, &Handle_Vocal_sync);

  vTaskStartScheduler();
}

void loop()
{
  delay(1000);
}

void VocalSyncTask(void *pvParameters)
{
  (void)pvParameters;

  Servo myservo;
  int MIN = 400;  // value when sound is detected
  int MAX = 1000; // max value when sound is detected
  int SecondDetection = 2;
  int val = 0;
  int i = 0;
  int posMax = 145;
  int posMin = 60;
  int pos = posMin;
  int BoucheStatus = 0;
  int ActionBouche = 0;
  int Repos = 0;
  int CompteurRepos = 0;
  String dbg;
  analogReference(INTERNAL);
  myservo.attach(servoMouthPin);
  myservo.write(posMin);
  for (;;)
  {
    val = analogRead(HPPin_In);
    pos = map(val, MIN, MAX, posMin, posMax);
    if (val > MIN) // if values detected : speaker voltage
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
        delay(0.5);
      }
      ActionBouche = 1;
      myservo.write(pos);
      CompteurRepos = 0;
      delay(0.1);
    }
    if (BoucheStatus == 1 && ActionBouche == 1)
    {
      Repos = 0;
      CompteurRepos = 0;
      ActionBouche = 0;
    }
    if (CompteurRepos == 100 && Repos == 0)
    {
      myservo.write(posMin);
      Repos = 1;
    }
    CompteurRepos += 1;
    delay(1);
  }
}

void NeoPixelTask(void *pvParameters)
{
  (void)pvParameters;
  Neo_Pixel_Info_s neoStruct_receive;
  Pixel_init();

  for (;;)
  {
    if (xQueueReceive(NeoPixel_Queue, &neoStruct_receive, portMAX_DELAY) == pdPASS)
    {
      switch (neoStruct_receive.func)
      {
      case NEO_PIXEL_SET_ANIMATION:
        Pixel_Update_struct_animation(&neoStruct_receive);
        break;
        
      case NEO_PIXEL_WRITE_MATRIX:
        Pixel_write_on_Matrix(&neoStruct_receive);
        break;
      }
      Pixel_animation_Update();
    }
  }
}

void ReadMsg(void *pvParameters)
{
  (void)pvParameters;
  ETAT etat;
  // for process FreeRTOS
  for (;;)
  {
    etat = receiveMsg();
    Serial.println(etat);
    if (etat == ETAT_OK)
    {
      processMsg();
    }
    vTaskDelay(500 / portTICK_PERIOD_MS);
  }
}

ETAT receiveMsg()
{
  ETAT etat;
  etat = ETAT_ERROR;
  int msg_size = 0;
  int byteCounter = 0;
  int bytesAvailable = Serial.available();
  if (bytesAvailable > 0)
  {
    for (int i = 0; i < bytesAvailable; i++)
    {
      // read the incoming values
      unsigned char receiveByte = Serial.read();
      ++byteCounter;
      // Verifier si le premier octet est le MAGIC_NUMBER
      if ((byteCounter == 1) && (receiveByte != MAGIC_NUMBER))
      {
        byteCounter = 0;
        etat = ETAT_ESERIAL;
      }
      if (byteCounter == 2)
      {
        // recuperation de la taille du message
        // verification si le message est superieur à 64
        if (receiveByte > MAX_MSG_SIZE)
        {
          byteCounter = 0;
          etat = ETAT_ESERIAL;
          continue;
        }
        msg_size = receiveByte;
      }
      if (byteCounter > 2)
      {
        recv_cmd_Buffer[byteCounter - 3] = receiveByte;
      }
      if (byteCounter == 2 + msg_size)
      {
        byteCounter = 0;
        etat = ETAT_OK;
      }
    }
  }
  return etat;
}

void processMsg()
{
  // decode process for arduino nano
  ETAT etat;
  etat = ETAT_OK;
  int start_index = 0;
  int fonction = recv_cmd_Buffer[0];
  Neo_Pixel_Info_s neoStruct_send;
  switch (fonction)
  {
  case NEO_PIXEL_SET_ANIMATION:
    neoStruct_send.func = NEO_PIXEL_SET_ANIMATION;
    neoStruct_send.animation = recv_cmd_Buffer[start_index + 1];
    start_index += 1; // u8
    neoStruct_send.red = recv_cmd_Buffer[start_index + 1];
    start_index += 1; // u8
    neoStruct_send.green = recv_cmd_Buffer[start_index + 1];
    start_index += 1; // u8
    neoStruct_send.blue = recv_cmd_Buffer[start_index + 1];
    start_index += 1; // u8
    neoStruct_send.speed = to_b16(recv_cmd_Buffer, start_index + 1);
    start_index += 2; // u16
    xQueueSend(NeoPixel_Queue, &neoStruct_send, portMAX_DELAY);
    break;

  case NEO_PIXEL_WRITE_MATRIX:
    neoStruct_send.func = NEO_PIXEL_WRITE_MATRIX;
    neoStruct_send.buffer = recv_cmd_Buffer+start_index+2;
    neoStruct_send.bufferSize=recv_cmd_Buffer[start_index+1];
    start_index +=1 + recv_cmd_Buffer[start_index+1];
    xQueueSend(NeoPixel_Queue,&neoStruct_send,portMAX_DELAY);
    break;

  default:
    etat = ETAT_EPARAM;
    Serial.println("Fonction NeoPixel innconnu");
    break;
  }
}

int to_b16(byte *buff, int index)
{
  return (buff[index] << 8) + buff[index + 1];
}


