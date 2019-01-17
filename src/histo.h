#ifndef HIS_H
#define HIS_H
#include "image.h"


//all values between 0 and 255 (RGB values)
typedef struct Histo{
    int arr[255];
}Histo;


Histo initialise_histo();
//to display the array of a histogram, mainly to check if there are problems 
void display_arr(Histo H);
Image* draw_histo(Image* I);


#endif
