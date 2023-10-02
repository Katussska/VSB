#include <stdio.h>
#include <stdlib.h> //malloc

char *playground_area(int *rows, int *cols);
void moves(char dir, char *playground, int rows, int cols, int *posR, int *posC);
void display_playground(int *rows, int *cols, char *playground);

int main()
{
    int rows, cols = 0;
    char dir;
    char *playground = playground_area(&rows, &cols);

    int posC = 0;
    int posR = 0;

    while (scanf("%c", &dir) != EOF && dir != 'x')
    {
        moves(dir, playground, rows, cols, &posC, &posR);
    }

    display_playground(&rows, &cols, playground);
    free(playground);
    return 0;
}

char *playground_area(int *rows, int *cols)
{ // rows - řádky; cols - sloupce
    scanf("%d %d", rows, cols);
    int r = *rows;
    int c = *cols;

    char *playground = (char *)malloc(r * c * sizeof(char));

    for (int i = 0; i < r; i++)
    {
        for (int j = 0; j < c; j++)
        {
            playground[i * c + j] = '.';
        }
    }
    return playground;
}

void moves(char dir, char *playground, int rows, int cols, int *posR, int *posC)
{
    int c = cols;
    int pr = *posR;
    int pc = *posC;

    switch (dir)
    {
    case '>':
        ++*posC;
        if (*posC > (cols - 1))
        {

            *posC = 0;
        }

        break;

    case '<':
        --*posC;
        if (*posC < 0)
        {
            *posC = cols - 1;
        }

        break;

    case 'v':
        ++*posR;
        if (*posR > (rows - 1))
        {
            *posR = 0;
        }

        break;

    case '^':
        --*posR;
        if (*posR < 0)
        {
            *posR = rows - 1;
        }

        break;

    case 'o':
        playground[(*posR) * c + (*posC)] = 'o';
        break;

    default:
        break;
    }
}

void display_playground(int *rows, int *cols, char *playground)
{
    int r = *rows;
    int c = *cols;

    for (int i = 0; i < r; i++)
    {
        for (int j = 0; j < c; j++)
        {
            printf("%c", playground[i * c + j]);
        }
        printf("\n");
    }
}