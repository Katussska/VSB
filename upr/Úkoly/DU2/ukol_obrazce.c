#include <stdio.h>

int main()
{

    int obrazec = 9, n = 3, h = 10, i = 1, j = 1, k = 0, radek = 1, sloupec = 1;
    switch (obrazec)
    {
    case 1:
        while (i <= n) //Řádek o délce n
        {
            printf("x");
            i++;
        }
        break;
    case 2:
        while (i <= n) // Sloupec o výšce n
        {
            printf("x\n");
            i++;
        }
        break;
    case 3:
        while (radek <= n) //Čtverec o straně n
        {
            for (int i = 0; i < n; i++)
            {
                printf("x ");
            }
            radek++;
            printf("\n");
        }
        break;
    case 4:
        while (sloupec <= h) // Obdélník o šířce n a výšce h
        {
            for (int i = 0; i < n; i++)
            {
                printf("x ");
            }
            sloupec++;
            printf("\n");
        }
        break;
    case 5:
        while (radek <= h) //“Žebřík” s šířkou n a h stupínky
        {
            for (int i = 1; i < n; i++)
            {
                printf("x");
            }
            printf("\n");
            radek++;
            printf("\n");
        }
        break;
    case 6:
        while (radek <= n) // Dutý čtverec o straně n
        {
            if (radek == 1 || radek == n)
            {
                for (int i = 1; i <= n; i++)
                {
                    printf("x ");
                }
            }
            else
            {
                printf("x ");
                for (int i = 3; i <= n; i++)
                {
                    printf("  ");
                }
                printf("x");
            }
            printf("\n");
            radek++;
        }
        break;
    case 7:
        while (i <= n) // Pravotočivá diagonála s výškou n
        {
            for (int j = 0; j < i; j++)
            {
                printf(" ");
            }
            printf("x\n");
            i++;
        }
        break;
    case 8:
        while (i <= n) // Levotočivá diagonála s výškou n
        {
            for (int j = n; j > i; j--)
            {
                printf(" ");
            }
            printf("x\n");
            i++;
        }
        break;
    case 9:
        for (int i = 0; i < n; i++) // Trojúhelník s výškou n
        {
            if ((i + 1) == n)
            {
                for (int j = 0; j < n; j++)
                {
                    printf("x ");
                }
            }
            else
            {
                for (int j = 1; j < (n - i); j++)
                {
                    printf(" ");
                }
                if (i == 0)
                {
                    printf("x\n");
                }
                else
                {
                    printf("x");
                }
                if (i != 0)
                {
                    for (int j = 1; j < (2 * i); j++)
                    {
                        printf(" ");
                    }
                    printf("x\n");
                }
            }
        }
        break;
    case 10:
        while (sloupec <= h) // Obdélník vyplněný čísly o šířce n a výšce h
        {
            if (sloupec == 1 || sloupec == h)
            {
                for (int i = 1; i <= n; i++)
                {
                    printf("x ");
                }
            }
            else
            {
                printf("x ");
                for (int i = 3; i <= n; i++)
                {
                    printf("%d ", k);
                    k++;
                    if (k >= 10)
                    {
                        k = 0;
                    }
                }
                printf("x");
            }
            printf("\n");
            radek++;
            sloupec++;
        }
        break;
    default:
        printf("Spatna volba\n");
    }
    printf("\n\n");
    return 0;
}