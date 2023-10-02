#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <assert.h>
#include <errno.h>
#include <string.h>

int main(int argc, char **argv)
{
    FILE *output1 = fopen("x", "w");
    FILE *output2 = fopen("y", "wb");
    int pole[] = {1, 2, 3, 4, 5};
    for (int i = 0; i < 5; i++)
    {
        fprintf(output1, "%d ", pole[i]); // pokud nedáme za %d mezeru, na výstupu místo 1 2 3 4 5 bude 12345 0 0 0 0
    }
    fwrite(pole, sizeof(int), 5, output2);
    fclose(output1);
    fclose(output2);

    FILE *input1 = fopen("x", "r");
    if (input1 == NULL)
    {
        printf("Nepovedlo se otevrit soubor z duvodu %d - %s\n",
               errno, strerror(errno));
        // return 1;
    }
    FILE *input2 = fopen("y", "rb");
    assert(input2);             // pokud bude NULL, assert to ukonci. nahrazuje if podminku, vypisuje standartni chybovy vystup
    fseek(input2, 0, SEEK_END); // SEEK_SET????
    int pole1[5] = {};
    int pole2[5] = {};
    for (int i = 0; i < 5; i++)
    {
        int nacteno = fscanf(input1, "%d ", &pole1[i]);
        if (nacteno == 0)
        {
            printf("Spatny obsah souboru");
            // return 1;
        }
        if (nacteno == EOF)
        {
            printf("Dosazen konec souboru");
            // return 1;
        }
    }
    int nacteno = fread(pole2, sizeof(int), 6, input2);
    if (nacteno < 6)
    {
        printf("Nepovedlo se nacist binarne\n");
        if (feof(input2))
        {
            printf("Dosazen konec souboru\n");
        }
    }

    fclose(input1);
    fclose(input2);
    for (int i = 0; i < 5; i++)
    {
        printf("%d ", pole1[i]);
    }
    printf("\n");
    for (int i = 0; i < 5; i++)
    {
        printf("%d ", pole2[i]);
    }
    printf("\n");
    return 0;
}