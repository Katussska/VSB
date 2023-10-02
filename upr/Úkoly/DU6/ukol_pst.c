#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int getRows(char *buf);
void change(char *buf2, int *V, int *m);
void lower(char *buf2);
void upper(char *buf2);
int palindrom(char *buf);

int main()
{
    char buf[101];
    char buf2[101];
    int n = getRows(buf);
    int c = 0;

    for (int i = 0; i < n; i++)
    {
        fgets(buf, sizeof(buf), stdin);
        for (int j = 0; j < 101; j++)
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
            int V = 0;
            int m = 0;
            for (int i = 0; i <= strlen(s); i++)
            {
                buf2[i] = s[i];
            }
            printf("Slovo %d: %s ", c, s);
            c++;
            change(buf2, &V, &m);
            printf("%s ", buf2);
            printf("%d %d ", m, V);
            lower(buf2);
            printf("%s ", buf2);
            upper(buf2);
            printf("%s ", buf2);
            printf("%d", palindrom(s));
            printf("\n");
        }
    }
    return 0;
}

int getRows(char *buf)
{
    fgets(buf, sizeof(buf), stdin);
    int n = atoi(buf);
    return n;
}

void change(char *buf2, int *V, int *m)
{
    for (int i = 0; buf2[i] != '\0'; i++)
    {
        if (buf2[i] >= 'a' && buf2[i] <= 'z')
        {
            ++*m;
            buf2[i] = buf2[i] - 'a' + 'A';
        }
        else if (buf2[i] >= 'A' && buf2[i] <= 'Z')
        {
            ++*V;
            buf2[i] = buf2[i] + 'a' - 'A';
        }
    }
}

void lower(char *buf2)
{
    for (int i = 0; buf2[i] != '\0'; i++)
    {
        if (buf2[i] >= 'A' && buf2[i] <= 'Z')
        {
            buf2[i] = buf2[i] + 'a' - 'A';
        }
    }
}

void upper(char *buf2)
{
    for (int i = 0; buf2[i] != '\0'; i++)
    {
        if (buf2[i] >= 'a' && buf2[i] <= 'z')
        {
            buf2[i] = buf2[i] - 'a' + 'A';
        }
    }
}

int palindrom(char *buf)
{
    int k = strlen(buf) - 1;
    for (int i = 0; i < strlen(buf); i++)
    {
        if (buf[i] == buf[k])
        {
            if (i == k)
            {
                return 1;
            }
            k--;
        }
        else
        {
            return 0;
        }
    }
    return 1;
}
