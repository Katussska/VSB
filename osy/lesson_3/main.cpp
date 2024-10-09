#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>
#include <stdbool.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/types.h>
#include <bits/struct_stat.h>
#include <bits/struct_stat_time64_helper.h>
#include <time.h>

void print_string_array(char **array, int size)
{
    for (int i = 0; i < size; i++)
    {
        printf("%s\n", array[i]);
    }
}

int main(int argc, char **argv)
{
    if (argc < 2)
    {
        printf("Usage: %s <string>\n", argv[0]);
        return 1;
    }

    int opt;
    bool read = false;
    bool write = false;
    bool execute = false;

    while ((opt = getopt(argc, argv, "rwx")) != -1)
    {
        switch (opt)
        {
        case 'r':
            read = true;
            break;
        case 'w':
            write = true;
            break;
        case 'x':
            execute = true;
            break;
        default:
            fprintf(stderr, "Usage: %s [-r] [-w] [-x]\n", argv[0]);
            return 1;
        }
    }

    for (int i = optind; i < argc; i++)
    {
        struct stat fileStat;
        if (stat(argv[i], &fileStat) < 0)
        {
            perror("Non-existing file.");
            exit(EXIT_FAILURE);
        }

        mode_t mode = fileStat.st_mode;

        if (
            (!read || (access(argv[i], R_OK) == 0)) &&
            (!write || (access(argv[i], W_OK) == 0)) &&
            (!execute || (access(argv[i], X_OK) == 0)))
        {
            // User permissions
            printf((mode & S_IRUSR) ? "r" : "-");
            printf((mode & S_IWUSR) ? "w" : "-");
            printf((mode & S_IXUSR) ? "x" : "-");

            // Group permissions
            printf((mode & S_IRGRP) ? "r" : "-");
            printf((mode & S_IWGRP) ? "w" : "-");
            printf((mode & S_IXGRP) ? "x" : "-");

            // Other permissions
            printf((mode & S_IROTH) ? "r" : "-");
            printf((mode & S_IWOTH) ? "w" : "-");
            printf((mode & S_IXOTH) ? "x" : "-");

            printf(" %.2f kB ", (float)fileStat.st_size / 1000.f);

            char timebuf[80];
            struct tm *timeinfo = localtime(&fileStat.st_mtime);
            strftime(timebuf, sizeof(timebuf), "%Y-%m-%d %H:%M:%S", timeinfo);
            printf("%s", timebuf);

            printf(" %s\n", argv[i]);
        }
    }

    return 0;
}