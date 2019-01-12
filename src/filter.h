#ifndef FIL_H
#define FIL_H
#include "image.h"

//CREATE ARRAYS CONTAINING LUTs
//idea: each pixel is given a new greyscale

unsigned char* identify_arguments();
/*returns a table of LUTs and their parameters, looks like this:
 
(ADDLUM) [0]: 0 or 1 (0 if not called, 1 if called)  (ADDLUM PARAMETER) [1]
(DIMLUM) [2]: 0 or 1                (ADDLUM PARAMETER) [3]
(ADDCON) [4]: 0 or 1                (ADDCON PARAMETER) [5]
(DIMCON) [6]: 0 or 1                (DIMCON PARAMETER) [7]
(INVERT) [8]: 0 or 1                (INVERT PARAMETER) [9]
(SEPIA) [10]: 0 or 1                (SEPIA PARAMETER) [11]
 
 */

void ADDLUM(int parameter, Image* I);
void DIMLUM(int parameter, Image* I);
void ADDCON(int parameter, Image* I);
void DIMCON(int parameter, Image* I);
void INVERT(int parameter, Image* I);
//SEPIA
void final_LUT(unsigned char* LUT);
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
