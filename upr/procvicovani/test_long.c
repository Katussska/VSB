#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main()
{

    char buf[50];
    char str[6];
    int j = 0;

    fgets(buf, sizeof(buf), stdin);
    buf[15] = 0;
    if (strcmp(buf, "longest-starts") == 1)
    {
        exit(EXIT_FAILURE);
    }

    for (int i = 15; i < strlen(buf) - 2; i++)
    {
        str[j] = buf[i];
        j++;
    }

    printf("%s\n", buf);
    printf("%s\n", str);

    return 0;
}