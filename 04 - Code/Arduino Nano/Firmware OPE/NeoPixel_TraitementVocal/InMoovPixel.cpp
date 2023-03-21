#include "InMoovPixel.h"
#include <Adafruit_NeoPixel.h>
#include <Arduino.h>
#include "MsgCodec.h"

/*Declaring NeoPixel*/
Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);

void Pixel_init()
{
  strip.begin();
  strip.show();
}

void Pixel_clear()
{
  strip.clear();
}

void Pixel_show()
{
  strip.show();
}

void Pixel_animation_Stop(Neo_Pixel_Info_s *neo_pix_ctx)
{

}

void Pixel_animation_ColorWipe(Neo_Pixel_Info_s *neo_pix_ctx)
{

}

void Pixel_animation_LarsonScanner(Neo_Pixel_Info_s *neo_pix_ctx)
{

}

void Pixel_animation_TheaterChase(Neo_Pixel_Info_s *neo_pix_ctx)
{

}

void Pixel_animation_Wheel(Neo_Pixel_Info_s *neo_pix_ctx)
{

}

void Pixel_animation_TheaterChaseRainbow(Neo_Pixel_Info_s *neo_pix_ctx)
{

}

void Pixel_animation_Rainbow(Neo_Pixel_Info_s *neo_pix_ctx)
{

}

void Pixel_animation_RainbowCycle(Neo_Pixel_Info_s *neo_pix_ctx)
{

}

void Pixel_animation_Flash_Random(Neo_Pixel_Info_s *neo_pix_ctx)
{
  if(!((neo_pix_ctx->count++) % neo_pix_ctx->speed))
  {
    if(neo_pix_ctx->step == 1)
    {
      neo_pix_ctx->position = random(LED_COUNT);
    }
    if(neo_pix_ctx->step<6)
    {
      int r = (neo_pix_ctx->red * neo_pix_ctx->step) / 5;
      int g = (neo_pix_ctx->green * neo_pix_ctx->step) / 5;
      int b = (neo_pix_ctx->blue * neo_pix_ctx->step) / 5;
      strip.setPixelColor(neo_pix_ctx->position,strip.Color(r,g,b));
    }
    else
    {
      int r = (neo_pix_ctx->red * (11 - neo_pix_ctx->step)) / 5;
			int g = (neo_pix_ctx->green * (11 - neo_pix_ctx->step)) / 5;
			int b = (neo_pix_ctx->blue * (11 - neo_pix_ctx->step)) / 5;
      strip.setPixelColor(neo_pix_ctx->position,strip.Color(r,g,b));    
    }
    neo_pix_ctx->step++;
    if(neo_pix_ctx->step > 11)
    {
      neo_pix_ctx->step = 1;
      strip.clear();
    }
  }
  neo_pix_ctx->newData = true;
}

void Pixel_animation_Iron_Man(Neo_Pixel_Info_s *neo_pix_ctx)
{
  int flip;
  if(!((neo_pix_ctx->count++) % neo_pix_ctx->speed))
  {
    flip = random(32);
    if(flip > 22)
    {
      neo_pix_ctx->direction = -neo_pix_ctx->direction;
    }
    neo_pix_ctx->alpha+= 5 * neo_pix_ctx->direction;

    if(neo_pix_ctx->alpha < 5)
    {
      neo_pix_ctx->alpha = 5;
      neo_pix_ctx->direction = 1;
    } 

    if(neo_pix_ctx->alpha > 100)
    {
      neo_pix_ctx->alpha = 100;
      neo_pix_ctx->direction = -1;
    } 

    for (unsigned int i = 0; i <= LED_COUNT; i++)
    {
			strip.setPixelColor(i,strip.Color((neo_pix_ctx->red * neo_pix_ctx->alpha)/100,(neo_pix_ctx->green * neo_pix_ctx->alpha)/100,(neo_pix_ctx->blue * neo_pix_ctx->alpha)/100));
    }
  }
  neo_pix_ctx->newData = true;
}