#include <stdio.h>
#include <unistd.h>

void animate()
{
    fflush(stdout); //(bonus animace)
    usleep(1000 * 30);
}

int maxim(int n, int *hist)
{
    int max = 0;
    for (int i = 0; i < 9; i++)
    {
        if (hist[i] > max)
        {
            max = hist[i];
        }
    }
    return max;
}

void histogramV(int *hist, int n)
{
    for (int i = 1; i <= 9; i++)
    {
        printf("%d ", i);
        for (int j = 0; j < hist[i - 1]; j++)
        {
            printf("#");
            // animate();
        }
        printf("\n");
    }
}

void histogramH(int *hist, int n)
{
    int max = maxim(n, hist);
    int i = 0;
    while (i < max)
    {
        for (int j = 0; j < 9; j++)
        {
            if (hist[j] < max)
            {
                printf(" ");
                // animate();
            }
            else
            {
                printf("#");
                // animate();
            }
        }
        printf("\n");
        max -= 1;
    }
    printf("123456789");
    printf("\n\n");
}

int main()
{
    setvbuf(stdout, NULL, _IONBF, 0);
    char graf;
    scanf("%c", &graf);
    if (graf != 'v' && graf != 'h')
    {
        printf("Neplatny mod vykresleni\n");
        return 1;
    }

    int n = 0;
    scanf("%d", &n);
    if (n < 0)
    {
        printf("Zadejte NEZÁPORNÉ číslo.\n");
        return 1;
    }

    int hist[9];

    int values = 0;
    int vstupy[10000];
    for (int i = 0; i < n; ++i)
    {
        scanf("%d", &values);
        vstupy[i] = values;
    }

    for (int j = 0; j < n; j++)
    {
        for (int i = 1; i <= 9; i++)
        {
            if (i == vstupy[j])
            {
                hist[i - 1]++;
            }
        }
        if (vstupy[j] < 1 || vstupy[j] > 9)
        {
            hist[0]++;
        }
    }

    if (graf == 'v')
    {
        histogramV(hist, n);
    }
    else
    {
        histogramH(hist, n);
    }

    return 0;
}
