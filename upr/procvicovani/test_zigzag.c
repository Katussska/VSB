#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int getN();
int getR(char *buf);

int main()
{
    char buf[51] = {0};
    int n = getN();
    int r = getR(buf);

    for (int i = 0; i < r; i++)
    {
        fgets(buf, sizeof(buf), stdin);
        for (int j = 0; j < sizeof(buf); j++)
        {
            if (buf[j] == '\n')
            {
                buf[j] = '\0';
            }

            if (buf[j] == '\0')
            {
                buf[j] = ' ';
                buf[j + 1] = '\0';
                break;
            }
        }
        for (char *s = strtok(buf, " "); s != NULL; s = strtok(NULL, " "))
        {
            int z = 0;
            int k = strlen(s) - 1;

            int delka = strlen(s);

            for (int m = 0; m < delka; m++)
            {
                if (m % 2 == 1)
                {
                    if (m >= n)
                    {
                        printf("%c", s[k]);
                    }
                    k--;
                }
                else if (m % 2 == 0 || m == 0)
                {
                    if (m >= n)
                    {
                        printf("%c", s[z]);
                    }
                    z++;
                }
            }
            printf("\n");
        }
    }
    return 0;
}

int getN()
{
    char bufN[20] = {0};
    fgets(bufN, sizeof(bufN), stdin);

    bufN[7] = 0;
    if (strcmp(bufN, "zig-zag"))
    {
        exit(EXIT_FAILURE); // return 1;
    }

    int n = atoi((bufN + 8));
    return n;
}

int getR(char *buf)
{
    fgets(buf, sizeof(buf), stdin);
    int r = atoi(buf);
    return r;
}