#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        fprintf(stderr, "Wrong parameters. Expected: ./cat file.txt\n");
        return 1;
    }

    FILE *file = fopen(argv[1], "r");

    if (file == NULL)
    {
        fprintf(stderr, "Error opening file.\n");
        return 1;
    }

    char line[250];

    while (fgets(line, sizeof(line), file))
        printf("%s", line);

    printf("\n");

    fclose(file);
    return 0;
}