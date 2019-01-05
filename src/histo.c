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
    printf("histogram initialised\n");
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
    printf("\n max freq: %d and full table:\n",max_freq);

    display_arr(H);
    
    //so that the size of each line is proportional to what the frequency without having to draw out of the window
    float ratio = (float)img_histo->height / max_freq;
    printf("ratio is %f\n",ratio);
    
    //draw a grey line that has the size of value*ratio
    //to do this, the line starts at position [i][height of image - frequency of i]
    for (i=0; i<=255; i++)
    {
        //no need to draw anything if the frequency is 0
        if (H.arr[i] != 0)
        {
            int size_line = H.arr[i]*ratio;
            printf("x: %d size_line:%d\n", i, size_line);
            for(j=0; j<size_line; j++)
            {
                printf("i:%d\n",i);
                set_pixel(img_histo, p_grey, i, img_histo->height - j);
            }
        }
    }
    
    printf("histogram successfully created\n");
    return img_histo;
}


/*take arr[200]=5, you want a 5px line.
 i=5
 j=0 to 5
    setpix(img, grey, 200, 5)

 depends on the frequency, if it's 10 it's easy to control, but what about 6000?
 let's say arr[4]=6000. you can't draw a 6000px line, so you need to divide it by something.
 you gotta make sure it's always smaller than the height of the histo's image. so divide it by its height maybe.
 we want max_freq ~= height of image

 */
