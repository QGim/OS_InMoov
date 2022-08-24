#ifndef request_h
#define request_h

typedef struct Requete
{
  int port;
  int nb_leds;
  int mode;
  int func;
  int nb_params;
  int param[];
};

#endif
