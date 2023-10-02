#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <assert.h>
#include <errno.h>
#include <string.h>

int main(int argc, char *argv[])
{
    FILE *fout;
    fout = fopen("intput.bin", "wb"); // misto input.txt muzeme zadat rovnou adresu: C:\\Users...

    char str[] = "Severocesky dealer drog = crackonos";

    int cislo1 = 10;
    int cislo2 = 20;

    // fputs("Retezec, ktery chci zapsat", fin);
    // fprintf(fout, "%d %d\n", 420, 13);
    fwrite(&cislo1, sizeof(cislo1), 1 /*kolik prvku = mame jedno cislo*/, fout);
    fwrite(&cislo2, sizeof(cislo2), 1 /*kolik prvku = mame jedno cislo*/, fout);
    fwrite(str, sizeof(char), 1 /*kolik prvku = mame jedno cislo*/, fout);

    fclose(fout);

    char str1[100];

    FILE *fin = fopen("intput.txt", "r");
    int cislo3;
    int cislo4;
    // fgets(str1, 100, fin);
    // fscanf(fin, "%d %d\n", &cislo1, &cislo2);
    // printf("%d %d\n", cislo1, cislo2);
    fread(&cislo3, sizeof(int /*cislo1*/), 1, fin);
    fread(&cislo4, sizeof(int /*cislo2*/), 1, fin);

    // fprintf("%d %d\n", cislo3, cislo4);

    fclose(fin);
    return 0;
}

// lolololol, v kunde