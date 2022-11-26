#ifndef order_h
#define order_h

typedef struct request
{
  int nb_leds;
  int mode;
  int nb_params;
}request_t;

typedef struct answer
{
  
}answer_t;


struct ctx_order
{
  struct request;
  struct answer ;
};

#endif
