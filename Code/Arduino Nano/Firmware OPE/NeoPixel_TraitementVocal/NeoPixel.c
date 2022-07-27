#include "status.h"
#include "NeoPixel.h"

Pixel pixel;

void clearPixel(void)
{
    pixel.rouge = 0;
    pixel.vert = 0;
    pixel.bleu = 0;
}