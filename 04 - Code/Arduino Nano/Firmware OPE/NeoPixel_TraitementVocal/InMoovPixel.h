#ifndef InMoovPixel_h
#define InMoovPixel_h


#define LED_PIN   9
#define LED_COUNT 15


#define NEOPIXEL_ANIMATION_NO_ANIMATION 0
#define NEOPIXEL_ANIMATION_STOP 1
#define NEOPIXEL_ANIMATION_COLOR_WIPE 2
#define NEOPIXEL_ANIMATION_LARSON_SCANNER 3
#define NEOPIXEL_ANIMATION_THEATER_CHASE 4
#define NEOPIXEL_ANIMATION_THEATER_CHASE_RAINBOW 5
#define NEOPIXEL_ANIMATION_RAINBOW 6
#define NEOPIXEL_ANIMATION_RAINBOW_CYCLE 7
#define NEOPIXEL_ANIMATION_FLASH_RANDOM 8
#define NEOPIXEL_ANIMATION_IRONMAN 9


extern void Pixel_init();
extern void Pixel_clear_all();
extern void Pixel_clear_by_pixel(unsigned char index);
extern void Pixel_show();
extern void Pixel_animation_Stop();
extern void Pixel_animation_ColorWipe();
extern void Pixel_animation_LarsonScanner();
extern void Pixel_animation_TheaterChase();
extern void Pixel_animation_TheaterChaseRainbow();
extern void Pixel_animation_Rainbow();
extern void Pixel_animation_RainbowCycle();
extern void Pixel_animation_Flash_Random();
extern void Pixel_animation_Iron_Man();
extern void Pixel_Update_struct_animation(struct Neo_Pixel_Info_s *neo_pix_ctx);
extern void Pixel_animation_Update();
extern void Pixel_write_on_Matrix(struct Neo_Pixel_Info_s *neo_pix_ctx);


#endif
