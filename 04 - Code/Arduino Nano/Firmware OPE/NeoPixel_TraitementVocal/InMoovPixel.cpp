#include "InMoovPixel.h"
#include <Adafruit_NeoPixel.h>
#include <Arduino.h>

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