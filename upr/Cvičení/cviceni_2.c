#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{

    /*   int x = 120;
       if (x<100){
           printf("Male\n");
       }
       else {
           if(x>1000){
               printf("Velke\n");
           }
           else {
               printf("Stredni\n");
           }
       }
   */

    int typ = 4, max = 23, i = 1, j = 1, soucet = 0, radek = 5, sloupec = 8;
    switch (typ)
    {
    case 1:
        while (i <= max)
        {
            printf("%d", i);
            i++;
        }
        break;
    case 2:
        while (i <= max)
        {
            /*                    if(i%2==0){
                                    printf("%d", i);
                                }
                                i++;
            */
            printf("%d ", i);
            i += 2;
        }
        break;
    case 3:
        while (i <= max)
        {
            printf("%d ", soucet);
            i++;
            soucet += i;
        }
        break;
    case 4:
        while (i <= radek)
        {
            j = 1;
            soucet = 1;
            while (j <= sloupec)
            {
                printf("%d ", soucet);
                soucet += i;
                j++;
            }
            printf("\n");
            i++;
        }
        break;
    default:
        printf("Spatna volba\n");
    }
    printf("\nKonec\n");
    return 0;
}