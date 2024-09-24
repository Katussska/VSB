#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        fprintf(stderr, "Wrong parameters. Expected: ./cut [number]\n");
        return 1;
    }

    size_t n = atoi(argv[1]);

    if (n <= 0)
    {
        fprintf(stderr, "Invalid argument. Please enter number greater than 0.\n");
        return 1;
    }

    char line[1000];

    while (fgets(line, sizeof(line), stdin))
    {
        if (strlen(line) < n)
        {
            printf("%s", line);
            continue;
        }

        line[n] = '\0';
        printf("%s\n", line);
    }

    return 0;
}
