#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ppm.h"
#include "image.h"


Image* load(const char* filename)
{
    //THIS WORKS
    char buff[16];
    Image *img;
    FILE *fp;
    int c, rgb_comp_color;
    //open PPM file for reading
    fp = fopen(filename, "rb");
    if (!fp) {
        fprintf(stderr, "Unable to open file '%s'\n", filename);
        exit(1);
    }
    
    //read image format
    if (!fgets(buff, sizeof(buff), fp)) {
        perror(filename);
        exit(1);
    }
    
    //check the image format
    if (buff[0] != 'P' || buff[1] != '6') {
        fprintf(stderr, "Invalid image format (must be 'P6')\n");
        exit(1);
    }
    
    //alloc memory form image
    img = (Image *)malloc(sizeof(Image));
    if (!img) {
        fprintf(stderr, "Unable to allocate memory\n");
        exit(1);
    }
    
    //check for comments
    c = getc(fp);
    while (c == '#') {
        while (getc(fp) != '\n') ;
        c = getc(fp);
    }
    
    ungetc(c, fp);
    //read image size information
    if (fscanf(fp, "%d %d", &img->width, &img->height) != 2) {
        fprintf(stderr, "Invalid image size (error loading '%s')\n",       filename);
        exit(1);
    }
    
    //read rgb component
    if (fscanf(fp, "%d", &rgb_comp_color) != 1) {
        fprintf(stderr, "Invalid rgb component (error loading '%s')\n",      filename);
        exit(1);
    }
    
    //check rgb component depth
    if (rgb_comp_color!= 255) {
        fprintf(stderr, "'%s' does not have 8-bits components\n",       filename);
        exit(1);
    }
    
    while (fgetc(fp) != '\n') ;
    //memory allocation for pixel data
    img->data = (Pixel*)malloc(img->width * img->height * 3 * sizeof(unsigned char));
    
    if (!img) {
        fprintf(stderr, "Unable to allocate memory\n");
        exit(1);
    }
    
    //read pixel data from file
    if (fread(img->data, 3 * img->width, img->height, fp) != img->height) {
        fprintf(stderr, "Error loading image '%s'\n", filename);
        exit(1);
    }
    
    fclose(fp);
    return img;
}
    





/*this function opens a file, prints:
    P6
    x y
    max
 and then all the other pixel information from image I into the file.
 */
int save(Image* I, const char* filename)
{
    FILE* fp = fopen(filename, "wb"); //write, binary
    if (!fp)
    {
        printf("failed to save image\n");
        return -1;
    }
    
    //write the header file
    //image format
    fprintf(fp, "P6\n");
    
    //comments
    //fprintf(fp, "# Created by Monica\n");
    
    //image size
    fprintf(fp, "%d %d\n",I->width,I->height);
    
    // rgb component depth
    fprintf(fp, "255\n");
    
    //pixel data
    fwrite(I->data, 3 * I->width, I->height, fp);
    
    fclose(fp);
    printf("image saved\n");
    return 0;
}


