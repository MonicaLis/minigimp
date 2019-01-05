#include <stdio.h>
#include <string.h>
#include "pixel.h"

Pixel create_pixel(unsigned char r, unsigned char g, unsigned char b)
{
    Pixel p;
    p.red = r;
    p.green = g;
    p.blue = b;
    return p;
}


void display_pixel(Pixel p)
{
    printf("red: %u green: %u blue: %u\n", p.red, p.green, p.blue);
}

int greyscale(Pixel p)
{
    int r = (int)(p.red); //convert from unisgned char to float
    int g = (int)(p.green);
    int b = (int)(p.blue);
    return 0.299*r + 0.587*g + 0.112*b;
}



