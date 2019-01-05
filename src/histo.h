#ifndef HIS_H
#define HIS_H
#include "image.h"



typedef struct Histo{
    int arr[255];
}Histo;


Histo initialise_histo();
void display_arr(Histo H);
Image* draw_histo(Image* I);


#endif
