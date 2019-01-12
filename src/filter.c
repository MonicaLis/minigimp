#include <stdio.h>
#include <stdarg.h>//multiple arguments
#include <string.h>
#include "filter.h"

char **global_argv;
int global_argc;

unsigned char* identify_arguments()
{
    int i;
    //the array in which we'll store our LUTs and their parameters (6 LUTs, 6 parameters)
    //we use unsigned char so that parameters can be multiplied with RGB components easily
    unsigned char* LUT = NULL;
    LUT = malloc(sizeof(11* (*LUT) ));
    
    //initialise LUT array to 0 everywhere
    for (i=0; i<=15; i++)
    {
        LUT[i]=0;
    }
    
    for (i=2; i<global_argc; i++) //when i=0 it's the executable, when i=1 it's the name of the image
    {
        /*initialise each time in case previous word is longer than current one
         ex: ADDLUM then SEPIA, we'd have word = SEPIAM*/
        char word[10] = "";
        strcpy(word, global_argv[i]); //copy what user wrote into variable "word"
       
        //this doesn't seem to be an optimal solution but I have no idea how to do better since switch(string) cannot be done in C
        if (strcmp(word, "ADDLUM") == 0)
        {
            printf("apply addlum\n");
            LUT[0]=1;
            LUT[1]=global_argv[i+1][0];
        }
        else if (strcmp(word, "DIMLUM") == 0)
        {
            printf("apply dimlum\n");
            LUT[2]=1;
            LUT[3]=(unsigned char)global_argv[i+1];
        }
        else if (strcmp(word, "ADDCON") == 0)
        {
            printf("apply addcon\n");
            LUT[4]=1;
            LUT[5]=(unsigned char)global_argv[i+1];
        }
        else if (strcmp(word, "DIMCON") == 0)
        {
            printf("apply dimcon\n");
            LUT[6]=1;
            LUT[7]=(unsigned char)global_argv[i+1];
        }
        else if (strcmp(word, "INVERT") == 0)
        {
            printf("apply invert\n");
            LUT[8]=1;
            LUT[9]=(unsigned char)global_argv[i+1];
        }
        else if (strcmp(word, "SEPIA") == 0)
        {
            printf("apply sepia\n");
            LUT[10]=1;
            LUT[11]=(unsigned char)global_argv[i+1];
        }
            
    }
    
    return LUT;
}

/*
void ADDLUM(int parameter, Image* I)
{
    Image* result;
    //make sure we never go higher than 255, the max RGB component
    result->red = min(255, I->red*parameter);
    result->green = min(255, I->green*parameter);
    result->blue = min(255, I->blue*parameter);
}

void DIMLUM(int parameter, Image* I)
{
    Image* result;
    //make sure we never go lower than 0, the min RGB component
    result->red = max(0, I->red*parameter);
    result->green = max(0, I->green*parameter);
    result->blue = max(0, I->blue*parameter);
}

void ADDCON(int parameter, Image* I);
CONTRAST
 float factor = (259*(parameter + 255))/(255*(259 - parameter); //contrast correction factor
 red = factor*(original_red - 128) + 128;
 blue = factor*(original_blue - 128) + 128;
 green = factor*(original_green - 128) + 128;

 

//value of contrast will be in the range of -255 to +255. Negative values will decrease the amount of contrast and, conversely, positive values will increase the amount of contrast.
*/

void final_LUT(unsigned char* LUT)
{
    int i;
    for (i=0; i<12; i++)
    {
        printf("%u ",LUT[i]);
    }
    printf("\n");

    
    /*
    unsigned char current_red, addlum_red, dimlum_red, addcon_red, dimcon_red, invert_red, sepia_red;
    unsigned char* LUT;
    
    //we need to do this for each pixel
    
    if (LUT[0] == 1) //if we need to apply ADDLUM
    {
        current_red = current_red * LUT[1];
    }
    if (LUT[2] == 1)
    {
        current_red = current_red * (-LUT[1]);
    }
     */
}

