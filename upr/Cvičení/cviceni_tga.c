#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    uint8_t idlength;
    uint8_t colourmaptype;
    uint8_t datatypecode;
    uint16_t colourmaporigin;
    uint16_t colourmaplength;
    uint8_t colourmapdepth;
    uint16_t x_origin;
    uint16_t y_origin;
    uint16_t width;
    uint16_t height;
    uint8_t bitsperpixel;
    uint8_t imagedescriptor;
} TGA_HEADER;

int main(int argc, char *argv[])
{
    TGA_HEADER header = {0, 0, 2, 0, 0, 0, 0, 0, 1920, 1080, 24, 0};
    FILE *tga_file = fopen("image.tga", wb);

    fwrite(&header, sizeof(header), 1, tga_file);

    fclose(tga_file);
    return 0;
}