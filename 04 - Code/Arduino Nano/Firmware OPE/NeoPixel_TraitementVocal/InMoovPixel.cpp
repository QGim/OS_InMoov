#include "InMoovPixel.h"
#include <Adafruit_NeoPixel.h>
#include <Arduino.h>
#include "MsgCodec.h"

/*Declaring NeoPixel*/
Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);

  byte animation; 
	byte ColorRed;
	byte ColorGreen; 
	byte ColorBlue;
	int speed = speed;
	int position;
	int count ;
	bool off;
	int direction;
	int step;
	byte alpha;
	bool newData;
  unsigned long lastShow = 0;


void Pixel_Update_struct_animation(Neo_Pixel_Info_s *neo_pix_ctx)
{
  animation = neo_pix_ctx->animation;
	ColorRed = neo_pix_ctx->red;
	ColorGreen = neo_pix_ctx->green;
	ColorBlue = neo_pix_ctx->blue;
	speed = neo_pix_ctx->speed;
	position = 1;
	count = 0;
	off = false;
	direction = 1;
	step = 1;
  alpha = 50;
	newData = true;

  
}

void Pixel_init()
{
  strip.begin();
  strip.show();
}

void Pixel_clear_all()
{
  strip.clear();
}

void Pixel_clear_by_pixel(unsigned char index)
{
  strip.setPixelColor(index,0,0,0);
}

void Pixel_show()
{
  strip.show();
  newData = false;
}



void Pixel_animation_Stop()
{
  for (unsigned int i = 1; i <= LED_COUNT; i++) 
  {
    Pixel_clear_by_pixel(i);
	}
	animation = NEOPIXEL_ANIMATION_NO_ANIMATION;
	newData = true;
}

void Pixel_animation_ColorWipe()
{
  if (!((count++) % speed)) 
  {
      if (off) 
      {
        strip.setPixelColor(position++,0,0,0);
      } 
      else 
      {
        strip.setPixelColor(position++,ColorRed,ColorGreen,ColorBlue);
      }
      if (position > LED_COUNT) 
      {
        position = 1;
        off = !off;
      }
    }
    else
    {
      lastShow = millis();
    }
    newData = true;
}



void Pixel_animation_LarsonScanner()
{
  if (!((count++) % speed))
  {
		for (unsigned int i = 1; i <= LED_COUNT; i++) 
    {
			Pixel_clear_by_pixel(i);
		}
		unsigned int pos = position;
		for (int i = -2; i <= 2; i++)
     {
			pos = position + i;
			if (pos < 1)
				pos += LED_COUNT;
			if (pos > LED_COUNT)
				pos -= LED_COUNT ;
			int j = (abs(i) * 10) + 1;
      strip.setPixelColor(pos,ColorRed/j, ColorGreen / j,ColorGreen/ j);
		}
		position += direction;
		if (position < 1)
    {
			pos = 2;
			direction = -direction;
		} else if (position > LED_COUNT) 
    {
			position = LED_COUNT - 1;
			direction = -direction;
		}
	}
  else
    {
      lastShow = millis();
    }
	newData = true;
}

void Pixel_animation_TheaterChase()
{
  if (!((count++) % speed))
  {
		for (unsigned int i = 0; i <= LED_COUNT; i += 3) 
    {
			if (i + position <= LED_COUNT)
      {
        Pixel_clear_by_pixel(i + position);
			}
		}
		position++;
		if (position >= 4)
    {
      position = 1;
    }
		for (unsigned int i = 0; i <= LED_COUNT; i += 3)
    {
			if (i + position<= LED_COUNT)
      {
        strip.setPixelColor(i+position,ColorRed,ColorGreen,ColorBlue);
			}
		}
	}
  else
    {
      lastShow = millis();
    }
	newData = true;
}

void Pixel_animation_Wheel(unsigned char index_wheel,unsigned int index_pixel)
{
  index_wheel = 255 - index_wheel;
  if(index_wheel< 85)
  {
    strip.setPixelColor(index_pixel,(255-index_wheel*3),0,(index_wheel*3));
  }
  else if (index_wheel<170)
  {
    index_wheel-=85;
    strip.setPixelColor(index_pixel,0,(index_wheel*3),(255-index_wheel*3));
  }
  else
  {
    index_wheel-=170;
    strip.setPixelColor(index_pixel,(index_wheel*3),(255-index_wheel*3),0);
  }
}

void Pixel_animation_TheaterChaseRainbow()
{
  if (!((count++) % speed)) 
  {
		for (unsigned int i = 0; i <= LED_COUNT; i += 3) 
    {
			if (i + position <= LED_COUNT) 
      {
				Pixel_clear_by_pixel(i+position);
			}
		}
		position++;
		if ( position >= 4)
    {
      position = 1;
    }
		for (unsigned int i = 0; i <= LED_COUNT; i += 3) 
    {
			if (i + position <= LED_COUNT)
      {
				Pixel_animation_Wheel((ColorRed + i), i+position);
			}
		}
		ColorRed++;
	}
  else
    {
      lastShow = millis();
    }
	newData = true;
}

void Pixel_animation_Rainbow()
{
  if(!((count++) % speed))
    {
      for(unsigned int i =0;i<= LED_COUNT;i++)
      {
        Pixel_animation_Wheel(ColorRed+i,i);
      }
      ColorRed++;
    }
    else
    {
      lastShow = millis();
    }
    newData = true;
}

void Pixel_animation_RainbowCycle()
{
  if(!((count++) % speed))
  {
    for(unsigned int i =0;i<= LED_COUNT;i++)
    {
      Pixel_animation_Wheel((i * 256 / LED_COUNT)+ColorRed,i);
    }
    ColorRed++;
  }
  else
    {
      lastShow = millis();
    }
  newData = true;
}

void Pixel_animation_Flash_Random()
{
  if(!((count++) % speed))
  {
    if(step == 1)
    {
      position = random(LED_COUNT);
    }
    if(step<6)
    {
      int r = (ColorRed * step) / 5;
      int g = (ColorGreen * step) / 5;
      int b = (ColorBlue * step) / 5;
      strip.setPixelColor(position,r,g,b);
    }
    else
    {
      int r = (ColorRed * (11 - step)) / 5;
			int g = (ColorGreen * (11 - step)) / 5;
			int b = (ColorBlue * (11 - step)) / 5;
      strip.setPixelColor(position,r,g,b);    
    }
    step++;
    if(step > 11)
    {
      step = 1;
    }
  }
  else
    {
      lastShow = millis();
    }
  newData = true;
}

void Pixel_animation_Iron_Man()
{
  int flip;
  if(!((count++) % speed))
  {
    flip = random(32);
    if(flip > 22)
    {
      direction = -direction;
    }
    alpha+= 5 * direction;

    if(alpha < 5)
    {
      alpha = 5;
      direction = 1;
    } 

    if(alpha > 100)
    {
      alpha = 100;
      direction = -1;
    } 

    for (unsigned int i = 1; i <= LED_COUNT; i++)
    {
			strip.setPixelColor(i,(ColorRed *alpha)/100,(ColorGreen * alpha)/100,(ColorBlue * alpha)/100);
    }
  }
  else
    {
      lastShow = millis();
    }
  newData = true;
}

void Pixel_animation_Update()
{
  if ((lastShow + 33) > millis())
  {
		return; //update 30 times/sec if there is new data to show
	}
  switch (animation)
  {
        case NEOPIXEL_ANIMATION_NO_ANIMATION:
          break;

        case NEOPIXEL_ANIMATION_STOP:
          Pixel_animation_Stop();
          break;

        case NEOPIXEL_ANIMATION_COLOR_WIPE:
          Pixel_animation_ColorWipe();
          break;

        case NEOPIXEL_ANIMATION_LARSON_SCANNER:
          Pixel_animation_LarsonScanner();
          break;

        case NEOPIXEL_ANIMATION_THEATER_CHASE:
          Pixel_animation_TheaterChase();
          break;

        case NEOPIXEL_ANIMATION_THEATER_CHASE_RAINBOW:
          Pixel_animation_TheaterChaseRainbow();
          break;

        case NEOPIXEL_ANIMATION_RAINBOW:
          Pixel_animation_Rainbow(); 
          break;

        case NEOPIXEL_ANIMATION_RAINBOW_CYCLE:
          Pixel_animation_RainbowCycle();
          break;

        case NEOPIXEL_ANIMATION_FLASH_RANDOM:
          Pixel_animation_Flash_Random();
          break;

        case NEOPIXEL_ANIMATION_IRONMAN:
          Pixel_animation_Iron_Man();
          break;

        default:
          Serial.println("Neopixel animation do not exist");
          break;
    }
    if (newData == true)
        {
          Pixel_show();
        }
}

void Pixel_write_on_Matrix(Neo_Pixel_Info_s *neo_pix_ctx)
{
  for (int i = 3; i < neo_pix_ctx->bufferSize + 3; i += 4) 
  {
    strip.setPixelColor(i,neo_pix_ctx->buffer[i+1],neo_pix_ctx->buffer[i+2],neo_pix_ctx->buffer[i+3]);
  }
	newData = true;
}