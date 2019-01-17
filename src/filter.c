#include <stdio.h>
#include <string.h>
#include "filter.h"
#include "image.h"
#include "ppm.h"
#include "pixel.h"
#include "histo.h"


char **global_argv;
int global_argc;


int* identify_arguments()
{
    int i, parameter;
    
    //the array in which we'll store our LUTs and their parameters (6 LUTs, 6 parameters)
    static int LUT[15];
     
    //initialise LUT array to 0 everywhere
    for (i=0; i<=15; i++)
    {
        LUT[i]=0;
    }
    
    for (i=2; i<global_argc; i++) //when i=0 it's the executable, when i=1 it's the name of the image
    {
        /*initialise each time in case previous word is longer than current one
         ex: ADDLUM then SEPIA, we'd have word = SEPIAM */
        char word[10] = "";
        strcpy(word, global_argv[i]); //copy what user wrote into variable "word"
        
        if (strcmp(word, "ADDLUM") == 0)
        {
            printf("apply addlum\n");
            LUT[0]=1;
            //convert char to int
            parameter = *global_argv[i+1] - '0';
            LUT[1]=parameter;
        }
        else if (strcmp(word, "DIMLUM") == 0)
        {
            printf("apply dimlum\n");
            LUT[2]=1;
            LUT[3]=parameter;
        }
        else if (strcmp(word, "ADDCON") == 0)
        {
            printf("apply addcon\n");
            LUT[4]=1;
            parameter = *global_argv[i+1] - '0';
            LUT[5]=parameter;
        }
        else if (strcmp(word, "DIMCON") == 0)
        {
            printf("apply dimcon\n");
            LUT[6]=1;
            parameter = *global_argv[i+1] - '0';
            LUT[7]=parameter;
        }
        else if (strcmp(word, "INVERT") == 0)
        {
            printf("apply invert\n");
            LUT[8]=1;
            parameter = *global_argv[i+1] - '0';
            LUT[9]=parameter;
        }
        else if (strcmp(word, "SEPIA") == 0)
        {
            printf("apply sepia\n");
            LUT[10]=1;
            parameter = *global_argv[i+1] - '0';
            LUT[11]=parameter;
        }
        
    }
    
    return LUT;
}



unsigned char RGB_value(unsigned char value)
{
    unsigned char result = value;
    if (value>255) result = 255;
    if (value<0) result = 0;
    return result;
}


void final_LUT(int* LUT)
{
    unsigned char current_red, current_green, current_blue;
    int i,j;
    Pixel current_pixel;
    
    //we load the image we want to apply effects on
    char* IMG = global_argv[1];
    char path[30] = "../images/"; //30 to make sure there's enough space for the image's name
    strcat(path, IMG);
    Image* loaded_IMG = load(path);
    
    
    //we need to do apply effects to all pixels so we go through the entire image
    for (i=0; i<loaded_IMG->height; i++)
    {
        for (j=0; j<loaded_IMG->width; j++)
        {
            //we create a pixel, change its RGB values depending on what effects have been called
            current_pixel = get_pixel(i,j,loaded_IMG);
            current_red = current_pixel.red;
            current_green = current_pixel.green;
            current_blue = current_pixel.blue;
            
            /*-----------------------ADDLUM and DIMLUM---------------------*/
            if (LUT[0] == 1)
            {
                current_red = RGB_value( current_red + 10*LUT[1]);
                current_green = RGB_value( current_green + 10*LUT[1]);
                current_blue = RGB_value( current_blue + 10*LUT[1]);
            }
            if (LUT[2] == 1)
            {
                current_red = RGB_value( current_red - 10*LUT[3]);
                current_green = RGB_value( current_green - 10*LUT[3]);
                current_blue = RGB_value( current_blue - 10*LUT[3]);
            }
            
            /*-----------------------ADDCON and DIMCON---------------------*/
            if (LUT[4] == 1)
            {
                current_red = RGB_value( 10*LUT[5]*(current_red - 128) + 128 );
                current_green = RGB_value( 10*LUT[5]*(current_green - 128) + 128 );
                current_blue = RGB_value( 10*LUT[5]*(current_blue - 128) + 128 );
            }
            if (LUT[6] == 1)
            {
                current_red = RGB_value( 0.2*LUT[5]*(current_red - 128) + 128 );
                current_green = RGB_value( 0.2*LUT[5]*(current_green - 128) + 128 );
                current_blue = RGB_value( 0.2*LUT[5]*(current_blue - 128) + 128 );
            }
            /*-----------------------INVERT and SEPIA---------------------*/
            if (LUT[8] == 1)
            {
                current_red = 255 - current_red;
                current_green = 255 - current_green;
                current_blue = 255 - current_blue;
            }
            if (LUT[10] == 1)
            {
                current_red = RGB_value( (current_red * .393) + (current_green *.769) + (current_blue * .189) );
                current_green = RGB_value( (current_red * .349) + (current_green *.686) + (current_blue * .168) );
                current_blue = RGB_value( (current_red * .272) + (current_green *.534) + (current_blue * .131) );
            }
            
            //we put the new RGB values into the pixel
            current_pixel.red = current_red;
            current_pixel.green = current_green;
            current_pixel.blue = current_blue;
            set_pixel(loaded_IMG, current_pixel, i, j);
        }
    }
    
    //save into new image and create its histogram
    Image* new_histo = draw_histo(loaded_IMG);
    save(loaded_IMG, "../images/new_image.ppm");
    save(new_histo, "../images/new_histo.ppm");
    printf("Your new image has been saved as new_image.ppm in the images folder, you can also find its histogram new_histo.ppm.\n");
    delete_image(loaded_IMG);
}


/*
 
 A METTRE DANS LE DOSSIER
 
 L'idée générale est la suivante: on utilise les variables argc et argv pour créer le tableau de LUTs en fonction de ce qui a été créé en ligne de commande (cf tableau dans filter.h). Ensuite, dans la fonction final_LUT on applique les effets demandés. La nouvelle image est sauvegardée, et son histogramme aussi.
 Pour les formules des effets j'ai essentiellement bidouillé des formules que j'ai trouvées en ligne. Il n'y a que ADDLUM DIMLUM et INVERT qui marchent parfaitement bien.
 
 Problèmes:
 -seul le 1er chiffre du paramètre est lu, par ex. ADDLUM 15 donne ADDLUM 1
 -ADDCON donne un résultat très étrange
 -INVERT ne marche que si on met un paramètre alors qu'on ne l'utilise pas de même avec SEPIA (mais dans l'ex. du projet il y'a écrit SEPIA 5 alors j'ai décidé de faire pareil)
 -j'ai pas compris comment je pouvais aller chercher le dernier élément de la liste argv (donc le nouveau nom de l'image) alors elle est toujours sauvegardée sous le nom "new_image.ppm"
 
 J'ai passé beaucoup de temps à comprendre s'il fallait que je fasse un tableau de unsigned char comme les valeurs RGB, j'ai ensuite essayé char mais le plus facile c'était de tout convertir en int pour simplifier les calculs.
 Je ne pense pas que ces fonctions soient très optimales, il y a beaucoup de if() mais je ne sais pas comment faire autrement. Ce n'est pas très facile de rajouter une LUT mais c'est quand même faisable.
 J'ai aussi passé du temps à comprendre comment récupérer les arguments, c'est quand j'ai décidé de faire un tableau de nombres que tout est allé plus rapidement. Au départ j'ai imaginé faire un tableau avec les noms des effets mais c'est devenu trop compliqué.
 
 */

 
