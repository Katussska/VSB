#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <string>
#include <unistd.h>
#include <vector>
#include <time.h>

struct File
{
    std::string path;
    long long size;
    long modified;

    File(std::string p, size_t s, time_t t) : path(p), size(s), modified(t)
    {
    }
};

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        printf("Usage: %s <file>\n", argv[0]);
        return 1;
    }

    File file(argv[1], 0, 0);

    struct stat fileStat;
    if (stat(file.path.c_str(), &fileStat) < 0)
    {
        perror("stat");
        exit(EXIT_FAILURE);
    }

    file = File(
        file.path,
        fileStat.st_size,
        fileStat.st_mtime);

    while (true)
    {
        if (access(file.path.c_str(), F_OK) != 0)
        {
            printf("INFO: file not found: %s\n", file.path.c_str());
            exit(EXIT_FAILURE);
        }

        struct stat fileStat;
        if (stat(file.path.c_str(), &fileStat) < 0)
        {
            perror("stat");
            exit(EXIT_FAILURE);
        }

        if (fileStat.st_mtime == file.modified)
            continue;

        struct tm *timeinfo;
        timeinfo = localtime(&fileStat.st_mtime);

        printf("-----------------------------------\n");
        printf("%s %dB ----------------------------\n", file.path.c_str(), (fileStat.st_size - file.size));

        if (fileStat.st_size > file.size)
        {
            FILE *fp = fopen(file.path.c_str(), "r");
            fseek(fp, file.size, SEEK_SET);

            char *line = NULL;
            size_t len = 0;
            ssize_t read;

            while ((read = getline(&line, &len, fp)) != -1)
            {
                printf("%s", line);
            }

            free(line);
            fclose(fp);
        }

        file = File(
            file.path,
            fileStat.st_size,
            fileStat.st_mtime);

        fflush(stdout);
        usleep(60000000 / 30);
    }
}
