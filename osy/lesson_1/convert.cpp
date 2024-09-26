#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        fprintf(stderr, "Wrong parameters. Expected: ./convert [-l/-u/-x]\n");
        return 1;
    }

    if (strcmp(argv[1], "-l") != 0 && strcmp(argv[1], "-u") != 0 && strcmp(argv[1], "-x") != 0)
    {
        fprintf(stderr, "Invalid argument. Please choose -l, -u, or -x.\n");
        return 1;
    }

    char line[1000];

    while (fgets(line, sizeof(line), stdin))
    {
        for (int i = 0; line[i] != '\0'; i++)
        {
            char converted_char = line[i];
            switch (argv[1][1])
            {
            case 'l':
                converted_char = tolower(line[i]);
                break;
            case 'u':
                converted_char = toupper(line[i]);
                break;
            case 'x':
                if (islower(line[i]))
                    converted_char = toupper(line[i]);
                else if (isupper(line[i]))
                    converted_char = tolower(line[i]);
                break;
            }
            putchar(converted_char);
        }
    }
    return 0;
}