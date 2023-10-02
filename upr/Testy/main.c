#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdbool.h>

typedef struct
{
    char name[101];
    char city[101];
    int naughty;
    int gifts;
} Kiddo;
Kiddo get_kiddo();
char *get_condition();
float average_numOfGifts(int x, int y);

int main(int argc, char **argv)
{
    int num_k = atoi(argv[1]);
    int num_q = atoi(argv[2]);

    Kiddo *kiddosArray = (Kiddo *)malloc(sizeof(Kiddo) * num_k);

    char *condition;
    int num_qifts = 0;
    int num_city = 0;

    for (int k = 0; k < num_k; k++)
    {
        kiddosArray[k] = get_kiddo();
    }

    for (int q = 0; q < num_q; q++)
    {
        condition = get_condition();
        for (int c = 0; c < num_k; c++)
        {
            if (!strcmp(condition, kiddosArray[c].city))
            {
                num_qifts += kiddosArray[c].gifts;
                num_city++;
            }
            c++;
        }

        float averageGifts = average_numOfGifts(num_qifts, num_city);

        for (int l = 0; l < num_k; l++)
        {
            if (!strcmp(condition, kiddosArray[l].city))
            {
                if (kiddosArray[l].gifts <= averageGifts)
                {
                    printf("%s,%d\n", kiddosArray[l].name, kiddosArray[l].gifts);
                }
            }
            l++;
        }
    }

    free(kiddosArray);
    return 0;
}

float average_numOfGifts(int x, int y)
{
    float z = x / y;
    return z;
}

char *get_condition()
{
    char buffer[120];
    fgets(buffer, sizeof(buffer), stdin);
    char *name = strtok(buffer, ",");
    char *city = strtok(NULL, ",");
    for (int r = 0; r < strlen(city); r++)
    {
        if (city[r] == '\n')
        {
            city[r] = '\0';
        }
    }

    return city;
}

Kiddo get_kiddo()
{
    char *buffer = (char *)malloc(sizeof(char) * 250);
    fgets(buffer, sizeof(buffer), stdin);
    char *name = strtok(buffer, ",");
    char *city = strtok(NULL, ",");
    int naughty = atoi(strtok(NULL, ","));
    char *gift = strtok(NULL, ",");
    for (int j = 0; j < strlen(gift); j++)
    {
        if (gift[j] == '\n')
        {
            gift[j] = '\0';
        }
    }
    int gifts = atoi(gift);
    Kiddo k;
    strcpy(k.name, name);
    strcpy(k.city, city);
    k.naughty = naughty;
    k.gifts = gifts;
    free(buffer);
    return k;
}