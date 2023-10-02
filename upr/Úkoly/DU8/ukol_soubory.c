#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>

// Height of each character.
const int FONT_ROW_HEIGHT = 34;

typedef unsigned char byte;

typedef struct
{
    byte id_length;
    byte color_map_type;
    byte image_type;
    byte color_map[5];
    byte x_origin[2];
    byte y_origin[2];
    byte width[2];
    byte height[2];
    byte depth;
    byte descriptor;
} TGAHeader;

typedef struct
{
    byte blue;
    byte green;
    byte red;
} RGBPixel;

typedef struct
{
    TGAHeader header;
    RGBPixel *pixels;
    int width;
    int height;
} Image;

// Loads an image from the given `path`.
// If loading fails, return false.
bool image_load(Image *image, const char *path)
{
    FILE *file = fopen(path, "rb");
    if (file == NULL)
    {
        printf("Could not load image\n");
        return 1;
    }

    memset(image, 0, sizeof(Image));
    fread(&image->header, sizeof(image->header), 1, file);

    // We only support RGB images.
    assert(image->header.depth == 24);
    assert(image->header.image_type == 2);

    memcpy(&image->width, image->header.width, sizeof(image->header.width));
    memcpy(&image->height, image->header.height, sizeof(image->header.height));

    image->pixels = (RGBPixel *)malloc(sizeof(RGBPixel) * image->width * image->height);
    fread(image->pixels, sizeof(RGBPixel) * image->width * image->height, 1, file);

    fclose(file);

    return true;
}

// Free the memory of the given image.
void image_free(Image *image)
{
    free(image->pixels);
}

int podminkyCheck(int argc)
{
    if (argc != 4)
    {
        printf("Wrong parameters");
        exit(EXIT_FAILURE);
    }

    return 0;
}

int main(int argc, char *argv[])
{
    podminkyCheck(argc);

    char *input = argv[1];
    char *output = argv[2];
    char *font = argv[3];
    printf("%d\n%s\n%s\n%s\n", argc, input, output, font);

    Image Meme;
    image_load(Meme, argv[1]);

    /* Image *ABC = (Image *)malloc(sizeof(Image) * 26);
     for (int i = 0; i < 26; i++)
     {

         ABC[i] = image_load(ABC[i], font\X.tga);
     }

     free(ABC);*/
    fclose(image);
    return 0;
}