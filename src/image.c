#include <stdio.h>
#include <string.h>
#include "image.h"
#include "ppm.h"
#include "histo.h"

void delete_image(Image* I)
{
    if (I)
    {
        free(I->data);
        free(I);
        printf("image deleted\n");
    }
}

Image* create_image(int w, int h)
{
    Image* I = malloc(sizeof(Image));
    if (!I)
    {
        printf("allocation of memory for the image failed\n");
    }
    I->width = w;
    I->height = h;
    //3 times unsigned char because 3 RGB components per pixel
    I->data = (Pixel*)malloc(I->width * I->height * 3 * sizeof(unsigned char));
    if (!I->data)
    {
        printf("allocation of memory for image->data failed\n");
    }
    return I;
}


Pixel get_pixel(int x, int y, Image* I)
{
    return I->data[I->width*y+x]; //because we count pixels from the left to the right, and from the top to bottom
}
/*
 example: I want the 2nd pixel on the 3rd line, which would mean coordinates [0][2], the image is 10x10.
 10x2+3: number 23
 0 1 2 3 4 5 6 7 8 9 10
 11 12 13 14 15 16 17 18 19 20
 21 23 23 24 25 26 27 28 29 30
 ...
 */

void set_pixel(Image* I, Pixel p, int i, int j)
{
    I->data[I->width*j+i].red= p.red;
    I->data[I->width*j+i].green= p.green;
    I->data[I->width*j+i].blue= p.blue;
}


void fill_image(Image* I, unsigned char r, unsigned char g, unsigned char b)
{
    int i,j;
    Pixel p = create_pixel(r,g,b);
    for (j=0; j<I->height; j++)
    {
        for (i=0; i<I->width; i++)
        {
            set_pixel(I,p,i,j);
        }
    }
}


void test_all_functions()
{
    
    printf("\n------------------FUNCTIONS IN IMAGE.C, PIXEL.C, PPM.C------------------\n");
    Image* I;
    printf("First of all we load a ppm image and put it inside our variable I.\n");
    I = load("../images/rgb.ppm");
    printf("Now let's try changing the colour of the first 2 lines of pixels.\n");
    Pixel pink = create_pixel(240, 50, 200);
    Pixel orange = create_pixel(240, 155, 65);

    int i;
    for (i=0; i<I->width; i++)
    {
        set_pixel(I, pink, i, 0);
    }
    for (i=0; i<I->width; i++)
    {
        set_pixel(I, orange, i, 1);
    }
    
    printf("[Testing display_pixel and get_pixel] A pixel on the 1st line should be pink (240, 50, 200), and on the 2nd line orange (240, 155, 65). Let's check:\n");
    printf("first line: ");
    display_pixel( (get_pixel(0,0,I)) ); //1st pixel of 1st line
    printf("second line: ");
    display_pixel( (get_pixel(0,1,I)) ); //1st pixel of 2nd line
    
    printf("Let's calculate the greyscale of the orange pixel.\n");
    printf("greyscale: %d\n", greyscale(orange));
    
    printf("Now we'll try saving this modified image into another one.\n");
    save(I, "../images/modifiedlines.ppm");
    printf("Go into the images folder to see whether the 2 first lines have changed.\n");
    
    printf("Let's try creating an image from scratch.\n");
    Image* J = create_image(100,100);
    printf("We'll try filling it with a dark blue (0,0,150).\n");
    fill_image(J, 0, 0, 150);
    
    printf("Let's save it into a ppm file so we can check if it worked.\n");
    save(J, "../images/created_image.ppm");
    printf("Check the images folder.\n");
    
    printf("Now we can delete all images and liberate allocated memory.\n");
    delete_image(I);
    delete_image(J);
     
    
    printf("\n------------------FUNCTIONS IN HISTO.C------------------\n");
    Image* IMG;
    Image* HIS;
    printf("Let's load an image.\n");
    IMG = load("../images/art.ppm");
    printf("Let's create a Histo variable, initialise it, and display its array.\n");
    Histo H = initialise_histo();
    printf("This is the array of the initialised histogram.\n");
    display_arr(H);
    printf("Now let's try creating its histogram.\n");
    HIS = draw_histo(IMG);
    printf("Let's save the histogram into a file so we can have a look at it.\n");
    save(HIS, "../images/his.ppm");
}


/*
 
 A METTRE DANS LE DOSSIER
Finalement pas des fonctions bien compliquées mais j'ai pris beaucoup de temps à comprendre comment allouer de la mémoire à la structure Image, et comme je l'ai déjà dit, j'étais partie sur l'allocation du nombre de pixels et non pas 3*unsigned char.
 J'ai eu tellement de petits problèmes que je me suis dit que j'allais créer la fonction test_all_functions pour vérifier que tous les petits détails collent. Créer un pixel, lui attribuer des RGB différents, mais aussi tester d'autres fonctions plus complexes comme celle qui crée un histogramme.
 */
