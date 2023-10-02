#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int getR();

int main()
{
    char buf[51];
    char buf1[51];
    fgets(buf, sizeof(buf), stdin);
    buf[14] = 0;
    int r = getR();
    int max = 0;

    for (int k = 15; k < count; i++)
    {
        /* code */
    }

    for (int i = 0; i < r; i++)
    {
        fgets(buf1, sizeof(buf1), stdin);
        for (int j = 0; j < 101; j++)
        {
            if (buf1[j] == '\n')
            {
                buf1[j] = '\0';
            }

            if (buf1[j] == '\0')
            {
                buf1[j] = ' ';
                buf1[j + 1] = '\0';
                break;
            }
        }
        if (strcmp(buf1, (buf + 15)))
        {
        }
    }

    return 0;
}

int getR()
{
    char buf2[10];
    fgets(buf2, sizeof(buf2), stdin);
    int r = atoi(buf2);
    return r;
}