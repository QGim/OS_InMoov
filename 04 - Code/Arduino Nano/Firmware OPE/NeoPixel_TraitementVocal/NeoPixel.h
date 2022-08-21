#ifndef NeoPixel_h
#define NeoPixel_h

#define NB_LEDS 15
#define PINOUT_NEOPIXEL 9

/*Mode d'animation*/
 


typedef enum
{
 NEOPIXEL_NO_ANIMATION = 0,
 NEOPIXEL_ANIMATION_STOP = 1,
 NEOPIXEL_ANIMATION_COLOR_WIPE = 2,
 NEOPIXEL_ANIMATION_LARSON_SCANNER = 3,
 NEOPIXEL_ANIMATION_THEATER_CHASE = 4,
 NEOPIXEL_ANIMATION_THEATER_CHASE_RAINBOW = 5,
 NEOPIXEL_ANIMATION_RAINBOW = 6,
 NEOPIXEL_ANIMATION_RAINBOW_CYCLE = 7,
 NEOPIXEL_ANIMATION_FLASH_RANDOM = 8,
 NEOPIXEL_ANIMATION_IRONMAN = 9
}Animation;




typedef struct 
{
    short rouge;
    short vert;
    short bleu;
}couleur;


typedef struct
{
    
    couleur color;
    Animation anim;
} __attribute__((packed))pixel_ctx;




#endif
