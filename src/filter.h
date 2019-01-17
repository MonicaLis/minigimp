#ifndef FIL_H
#define FIL_H
#include "image.h"

//CREATE ARRAYS CONTAINING LUTs
//idea: each pixel is given a new greyscale

int* identify_arguments();
/*returns a table of LUTs and their parameters, looks like this:
 
(ADDLUM) [0]: 0 or 1 (0 if not called, 1 if called)  (ADDLUM PARAMETER) [1]
(DIMLUM) [2]: 0 or 1                (ADDLUM PARAMETER) [3]
(ADDCON) [4]: 0 or 1                (ADDCON PARAMETER) [5]
(DIMCON) [6]: 0 or 1                (DIMCON PARAMETER) [7]
(INVERT) [8]: 0 or 1                (INVERT PARAMETER) [9]
(SEPIA) [10]: 0 or 1                (SEPIA PARAMETER) [11]
 
 */

unsigned char RGB_value(unsigned char value);
//to return an unsigned char that's  255 or 0 when calculations in final_LUT give numbers that are too big or too small
void final_LUT(int* LUT);
//applies the filters by using the table created by identify_arguments()

#endif
