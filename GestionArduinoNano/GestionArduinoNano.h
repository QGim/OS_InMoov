#ifndef _GESTION_ARDUINO_N
#define _GESTION_ARDUINO_N

typedef struct
{
  ETAT etat_retour;
   union
   {
     int angleServo;
     //ajouter etat bouche(open,close);
   }TXServoSyncro;
}TXSerial;


#endif
