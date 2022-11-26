#ifndef status_h
#define status_h

typedef enum
{
	ETAT_OK = 0,        //-> OK no errors
	ETAT_ERROR = -1,    //-> Return classical error
  ETAT_ERANGE = -2,   //-> Return out of range value error 
  ETAT_EBUSY = -3,    //-> Return error when the process is busy
  ETAT_ETIMEOUT = -4, //-> Return 
  ETAT_EPARAM = -5,   //-> Return
  ETAT_ENOENT = -6,   //-> Return
  ETAT_ENOSPC = -7,   //-> Return
  ETAT_EABORTED = -8, //-> Return
} ETAT;

#endif
