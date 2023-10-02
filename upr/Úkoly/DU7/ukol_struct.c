#include <stdio.h>
#include <string.h>
#include <stdlib.h>
int podminkyCheckN(int argc, char **argv)
{
    if (argc != 3)
    {
        printf("Wrong parameters");
        exit(EXIT_FAILURE);
    }
    int n = atoi(argv[2]);
    if (n <= 0)
    {
        printf("Wrong parameters");
        exit(EXIT_FAILURE);
    }
    return n;
}
typedef struct
{
    int day;
    char name[101];
    float startPrice;
    float endPrice;
    int sales;
    float diff;
} Akcie;
Akcie akcie_nacti()
{
    char *buffer = (char *)malloc(101 * sizeof(char));
    fgets(buffer, 101, stdin);
    int day = atoi(strtok(buffer, ","));
    char *name = strtok(NULL, ",");
    float startPrice = atof(strtok(NULL, ","));
    float endPrice = atof(strtok(NULL, ","));
    char *sale = strtok(NULL, ",");
    for (int j = 0; j < strlen(sale); j++)
    {
        if (sale[j] == '\n')
        {
            sale[j] = '\0';
        }
    }
    int sales = atoi(sale);
    Akcie i;
    strcpy(i.name, name);
    i.day = day;
    i.startPrice = startPrice;
    i.endPrice = endPrice;
    i.sales = sales;
    i.diff = endPrice - startPrice;
    free(buffer);
    return i;
}
void akcie_vypis(Akcie i)
{
    printf("Day: %d, ticker: %s, start: %.2f, end: %.2f, diff: %.2f, volume: %d",
           i.day, i.name, i.startPrice, i.endPrice, i.diff, i.sales);
}
void html_vypis(Akcie *array, int n, char *t)
{
    printf("<ul>\n");
    for (int j = n - 1; j >= 0; j--)
    {
        if (strcmp(array[j].name, t))
        {
            printf("<li>");
            akcie_vypis(array[j]);
            printf("</li>\n");
        }
        else
        {
            printf("<li><b>");
            akcie_vypis(array[j]);
            printf("</b></li>\n");
        }
    }
    printf("</ul>\n</body>\n</html>\n");
}
void vypis_hlavu(char *t)
{
    printf("<html>\n<body>\n<div>\nTicker %s was not found\n</div>\n", t);
}
void vypis_hlavicku(Akcie i)
{
    printf("<html>\n<body>\n<div>\n<h1>%s: highest volume</h1>\n<div>Day: %d</div>\n<div>Start price: %.2f</div>\n<div>End price: %.2f</div>\n<div>Volume: %d</div>\n</div>\n", i.name, i.day, i.startPrice, i.endPrice, i.sales);
}
void html_hlavicka(Akcie *array, int n, char *t)
{
    Akcie best = {};
    for (int j = 0; j < n; j++)
    {
        if (!(strcmp(array[j].name, t)))
        {
            if (array[j].sales > best.sales)
            {
                best = array[j];
            }
        }
    }
    if (strcmp(best.name, t))
    {
        vypis_hlavu(t);
    }
    else
    {
        vypis_hlavicku(best);
    }
}
int main(int argc, char **argv)
{
    int n = podminkyCheckN(argc, argv);
    char *t = argv[1];
    Akcie *array = (Akcie *)malloc(sizeof(Akcie) * n);
    for (int i = 0; i < n; i++)
    {
        array[i] = akcie_nacti();
    }
    html_hlavicka(array, n, t);
    html_vypis(array, n, t);
    free(array);
    return 0;
}
