#ifndef _GESTION_ARDUINO_N
#define _GESTION_ARDUINO_N

#include "return_state.h"


typedef struct
{
  int angleServo;
  //ajouter etat bouche(open,close)
} TXData;

typedef struct
{
  int mode_neopixel;
  int color_neopixel;
} RXData;

struct SerialData
{
  ETAT etat;
  RXData RXSerialData;
  TXData TXSerialData;
};


#endif
