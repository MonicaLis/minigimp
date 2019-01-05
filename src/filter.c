#include <stdio.h>
#include <string.h>
#include <stdarg.h>//multiple arguments
#include "filter.h"

char **global_argv;
int global_argc;

/*Image* final_LUT(int number,...)
{
    va_list arguments;
    LUT lut;
    int i;
    //initialise arguments to store all values after "number"
    va_start(arguments, number);
    //each time i increases you get to the next argument
    for (i=0; i<number; i++)
    {
        sum += va_arg ( arguments, double );
    }
    va_end ( arguments );                  // Cleans up the list
    
    return sum / num;
}
*/
//ADDLUM 4 DIMCON 3


/*
Image* ADDLUM(int parameter, Image* I)
{
    Image* result;
    result->red = max(255, I->red*parameter);
    result->green = max(255, I->green*parameter);
    result->blue = max(255, I->blue*parameter);
    return result;
}
*/

void identify_arguments()
{
    int i;
    LUT lut;
    for (i=1; i<global_argc; i++) //when i=0 it's the executable
    {
        string word = *global_argv[i];
        switch(word) {
                
            case "ADDLUM"  :
                printf("read addlum\n");
                break;
                
            case "ADDCONST"  :
                printf("read addconst\n");
                break;
        }
    }
}
