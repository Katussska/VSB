#include <stdio.h>
#include <stdlib.h>

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
} Pixel;

int main()
{
    // Otevření souboru
    FILE *file = fopen("img1.tga", "rb");
    if (file == NULL)
    {
        printf("Soubor se nepodarilo otevrit\n");
        return 1;
    }

    // Načtení hlavičky
    TGAHeader header;
    fread(&header, sizeof(TGAHeader), 1, file);

    // Zjištění rozměrů
    int width = 0;
    memcpy(&width, header.width, 2);

    int height = 0;
    memcpy(&height, header.height, 2);

    // Alokace paměti pro pixely
    Pixel *pixels = malloc(width * height * sizeof(Pixel));

    // Načtení pixelů
    fread(pixels, sizeof(Pixel), width * height, file);

    // Vypsání prvníh pixelu
    Pixel pixel = *pixels; // pixels[0], *(pixels + 0)

    printf("R=%d, G=%d, B=%d\n", pixel.red, pixel.green, pixel.blue);

    // Vykreslení červeného obdélníku
    int rect_w = 40;
    int rect_h = 50;
    int rect_row = 100;
    int rect_col = 60;

    for (int row = rect_row; row < rect_row + rect_h; row++)
    {
        for (int col = rect_col; col < rect_col + rect_w; col++)
        {
            // (row, col)
            int index = row * width + col;
            pixels[index].red = 255;
            pixels[index].green = 0;
            pixels[index].blue = 0;
        }
    }

    // Uložení do souboru
    FILE *file_output = fopen("img2.tga", "wb");
    fwrite(&header, sizeof(TGAHeader), 1, file_output);
    fwrite(pixels, sizeof(Pixel), width * height, file_output);
    fclose(file_output);

    free(pixels);
    fclose(file);

    return 0;
}
