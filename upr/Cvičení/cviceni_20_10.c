#include <stdio.h>
#include <stdlib.h> //malloc

void vypisMatice(int *mat, int r, int c)
{
    for (int i = 0; i < r; i++)
    {
        for (int j = 0; j < c; j++)
        {
            printf("%d", mat[i * c + j]);
        }
        printf("\n");
    }
}

void vypisVektoru(int *mat, int c)
{
    for (int i = 0; i < r; i++)
    {
        printf("%d", mat[i]);
    }
    printf("\n");
}

int *nasobeniMaticeVektorem(int *mat, int *vek, int r, int c)
{
    int *vysl = calloc(r, sizeOf(int));
    for (int i = 0; i < r; i++)
    {
        for (int j = 0; i < c; j++)
        {
            vysl[i] += mat[i * c + j] * vek[j];
        }
    }
    return vysl;
}

Int main();
{
    int mat[3][4] = {1, 2, 3, 4} {4, 3, 2, 1} { 2, 1, 3, 2 }
    int *vekt = (int *)mat;
    vypisMatice((int *)mat, 3, 4);
    vypisVektoru((int *)mat, 12);

    int *obrazek = malloc(2000 * 3000 * siteOf(int) * 1000);
    if (obrazek == NULL)
    {
        printf("Nepovedlo se alokovat.\n");
    }
    else
    {
        printf("Ok.");
    }
    free(obrazek);

    /*
      int r, c;
      scanf("%d, %d", &r, &c);
      int mat2[r] [c];
    */

    /*
      for(int i = 0; i < 3; i++)
      {
        for(int j = 0; j < 4; j++)
        {
          printf("%d", mat[i] [j]);
        }
        printf("\n");
    */

    /*
        for (int i= 0; i < 12; i++){
          printf("%d ", vekt[i]);
        }
        printf("\n");
      }
    */

    return 0;
}