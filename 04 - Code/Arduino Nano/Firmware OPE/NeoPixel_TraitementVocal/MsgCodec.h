#ifndef MsgCodec_h
#define MsgCodec_h
/*******************************************************************
 * serial protocol functions
 */

 
#define MAGIC_NUMBER            85  // 01010101=55 = U
#define MAX_MSG_SIZE			128
#define SEPARATEUR              124 // = | => Séparateur



/*FONCTION NEO_PIXEL*/
// > neoPixelSetAnimation/deviceId/animation/red/green/blue/b16 speed
#define NEO_PIXEL_SET_ANIMATION 1
// > neoPixelWriteMatrix/deviceId/[] buffer
#define NEO_PIXEL_WRITE_MATRIX 2

struct Neo_Pixel_Info_s
{
    byte func = 0;
    byte animation = 0;
    byte red = 0;
    byte green = 0;
    byte blue = 0;
    int speed = 0;
};
 
#endif
