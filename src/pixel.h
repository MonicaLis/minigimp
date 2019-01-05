#ifndef PIXEL_H
#define PIXEL_H

#include <stdio.h>
#include <stdlib.h>

typedef struct Pixel{
    unsigned char red, green, blue;
}Pixel;

void display_pixel(Pixel p);
Pixel create_pixel(unsigned char r, unsigned char g, unsigned char b);
int greyscale(Pixel p);

#endif
