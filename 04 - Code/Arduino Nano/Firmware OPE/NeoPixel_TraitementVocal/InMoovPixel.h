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
extern void Pixel_clear();
extern void Pixel_show();
extern void Pixel_animation_Stop(struct Neo_Pixel_Info_s *neo_pix_ctx);
extern void Pixel_animation_ColorWipe(struct Neo_Pixel_Info_s *neo_pix_ctx);
extern void Pixel_animation_LarsonScanner(struct Neo_Pixel_Info_s *neo_pix_ctx);
extern void Pixel_animation_TheaterChase(struct Neo_Pixel_Info_s *neo_pix_ctx);
extern void Pixel_animation_Wheel(struct Neo_Pixel_Info_s *neo_pix_ctx);
extern void Pixel_animation_TheaterChaseRainbow(struct Neo_Pixel_Info_s *neo_pix_ctx);
extern void Pixel_animation_Rainbow(struct Neo_Pixel_Info_s *neo_pix_ctx);
extern void Pixel_animation_RainbowCycle(struct Neo_Pixel_Info_s *neo_pix_ctx);
extern void Pixel_animation_Flash_Random(struct Neo_Pixel_Info_s *neo_pix_ctx);
extern void Pixel_animation_Iron_Man(struct Neo_Pixel_Info_s *neo_pix_ctx);



#endif
