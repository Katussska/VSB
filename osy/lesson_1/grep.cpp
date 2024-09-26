#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        fprintf(stderr, "Wrong parameters. Expected: ./grep [word]\n");
        return 1;
    }

    const char *word = argv[1];
    char line[1000];

    while (fgets(line, sizeof(line), stdin))
        if (strstr(line, word) != NULL)
            printf("%s", line);

    return 0;
}