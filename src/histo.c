#include <stdio.h>
#include <string.h>
#include "histo.h"


Histo initialise_histo()
{
    Histo H;
    int i;
    for (i=0; i<=255; i++)
    {
        H.arr[i] = 0;
    }
    return H;
}

void display_arr(Histo H)
{
    int i;
    for (i=0; i<=255; i++)
    {
        printf("%d:%d ", i, H.arr[i]);
        if (i%10 == 0) //display 10 values per line
        {
            printf("\n");
        }
    }
    printf("\n");
}

/*
 x-axis: goes from 0 to 255
 y-axis: frequency of pixels that have the same greyscale
 */

Image* draw_histo(Image* I)
{
    Histo H = initialise_histo();
    Image* img_histo = create_image(350, 400);
    fill_image(img_histo, 255, 255, 255);
    int i,j,grey;
    int max_freq = 0;
    Pixel p_grey = create_pixel(150, 150, 150);

    //go through the image from left to right, and top to bottom
    for (j=0; j<I->height; j++)
    {
        for (i=0; i<I->width; i++)
        {
            //calculate greyscale of each pixel
            grey = greyscale(get_pixel(i, j, I));
            //the frequency of arr[grey] increases
            H.arr[grey]++;
            //find out what the maximum frequency is (we need this to get the proportions right)
            if(H.arr[grey]>max_freq)
            {
                max_freq = H.arr[grey];
            }
        }
    }
    
    //display_arr(H); only used to check if it looks right, not essential
    
    //so that the size of each line is proportional to what the frequency without having to draw out of the window
    float ratio = (float)img_histo->height / max_freq;
    
    //draw a grey line that has the size of value*ratio
    //to do this, the line starts at position [i][height of image - frequency of i]
    for (i=0; i<=255; i++)
    {
        //no need to draw anything if the frequency is 0
        if (H.arr[i] != 0)
        {
            int size_line = H.arr[i]*ratio;
            for(j=0; j<size_line; j++)
            {
                set_pixel(img_histo, p_grey, i, img_histo->height - j);
            }
        }
    }
    
    printf("histogram successfully created\n");
    return img_histo;
}

/*
 
 A METTRE DANS LE DOSSIER
 Passé beaucoup de temps la dessus aussi. L'idée c'est de créer une barre grise pour chaque niveau de gris, proportionnelle à sa fréquence. J'ai pris du temps à avoir l'idée du "ratio", en général ca dépassait de l'image et du coup j'avais des fuites de mémoire (difficile d'identifier d'ou elles venaient au début).
 
 */
