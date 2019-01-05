#ifndef PPM_H
#define PPM_H
#include "image.h"

Image* load(const char* filename);
int save(Image* I,const char* filename);

#endif
