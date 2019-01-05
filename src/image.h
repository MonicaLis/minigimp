
#ifndef IMG_H
#define IMG_H
#include "pixel.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct Image{
    Pixel* data;
    int height;
    int width;
}Image;

Image* create_image(int w, int h);
void delete_image(Image* I);
Pixel get_pixel(int x, int y, Image* I);
void set_pixel(Image* I, Pixel p, int i, int j);
void fill_image(Image* I, unsigned char r, unsigned char g, unsigned char b);
void test_all_functions();

#endif
