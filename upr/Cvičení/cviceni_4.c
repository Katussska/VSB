#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>

void vratSouradnice(int *x, int *y)
{
    int a = 0, b = 0;
    scanf("%d %d", &a, &b);
    printf("Souradnice (%d, %d)\n", a, b);
    *x = a;
    *y = b; //%c-načítání znaku
}

vypisPole(int p[10])
{
    for (int i = 0; i < 10; i++)
    {
        printf("%d\n", p[i]);
    }
}

int main()
{
    /*    int x=10,y=20;
        vratSouradnice(&x,&y);
        printf("Souradnice v main (%d, %d)\n",x,y); */

    int pole[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    vypisPole(pole);
    return 0;
}