#ifndef FIL_H
#define FIL_H
#include "image.h"

typedef struct LUT{
    int greyscale_before;
    int greyscale_after;
   // struct LUT arr[5]; //6 different effects
}LUT;

//cImage* final_LUT(
void identify_arguments();
Image* ADDLUM(int parameter, Image* I);
Image* DIMLUM(int parameter, Image* I);
Image* ADDCON(int parameter, Image* I);
Image* DIMCON(int parameter, Image* I);
Image* INVERT(int parameter, Image* I);
//SEPIA
#endif


/*
 -LUT : look-up table, tableau qui effectue des transformations sur les couleurs
 -NVG défini de départ est associé à un NVG d’arrivée
 -nombre de NVG de départ pas forcément nombre NVG arrivée
 -la combinaison de pl. LUT doit être calculée dans une seule LUT finale
 
 
 goal: send back ONE image with multiple effects
 -create one function that identifies which LUT has been called
 -it needs to have as many arguments as you want
 */
