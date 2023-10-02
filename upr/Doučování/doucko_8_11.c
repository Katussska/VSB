#include <stdio.h>
#include <string.h>

struct Zbran
{
    int poskozeni;
}

// typedef struct Zbran Zbran;

typedef struct
{
    const char *jmeno;
    int pocet_zivotu;
    // Zbran;
    struct Prisera *kamarad;
} Prisera;

int main()
{

    Prisera karel = {"Karel", 100};
    karel.pocet_zivotu += 1;

    printf("Jmeno: %s\nZivoty: %d\n", karel.jmeno, karel.pocet_zivotu);

    /*char str[] = "ab,cd,ef";

    const char *p1 = strtok(str, ",");
    // const char *p2 = strtok(NULL, ",");
    const char *p2 = strtok(p1 + strlen(p1) + 1, ",");
    const char *p3 = strtok(NULL, ",");

    printf("%s\n%s\n%s\n", p1, p2, p3);*/

    return 0;
}