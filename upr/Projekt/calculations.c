#include "library.h"

void parametersCheck(int argc)
{
    if (argc != 9)
    {
        printf("Wrong parameters");
        exit(EXIT_FAILURE);
    }
}
char *getParameter(char *name, char **argv, int argc)
{
    char *parameter = (char *)calloc(50, sizeof(char));
    for (int i = 1; i < argc; i++)
    {
        if (strcmp(argv[i], name) == 0)
        {
            strcpy(parameter, argv[i + 1]);
        }
    }

    if (parameter[0] == '\0')
    {
        printf("Parameter %s not found\n", name);
        exit(EXIT_FAILURE);
    }

    for (int j = 0; j < 50; j++)
    {
        if (parameter[j] == '\n')
        {
            parameter[j] = '\0';
        }
    }

    return parameter;
}
void fileCheck(FILE *fileName)
{
    if (fileName == NULL)
    {
        printf("Could not load a file\n");
        exit(EXIT_FAILURE);
    }
}
int countDays(char *fileName)
{
    int count = 0;

    FILE *data = fopen(fileName, "r");
    fileCheck(data);

    char tmp[256];
    while (fgets(tmp, sizeof tmp, data))
    {
        count++;
    }

    fclose(data);
    return count;
}
Day getDay(FILE *filename)
{
    char *buffer = (char *)malloc(51 * sizeof(char));
    fgets(buffer, 51, filename);

    Day x;
    x.susceptible = atof(strtok(buffer, ","));
    x.infected = atof(strtok(NULL, ","));
    char *CHrecovered = strtok(NULL, ",");
    CHrecovered[strcspn(CHrecovered, "\n")] = 0;
    x.recovered = atof(CHrecovered);
    x.people = x.susceptible + x.infected + x.recovered;
    x.S = x.susceptible / x.people;
    x.I = x.infected / x.people;
    x.R = x.recovered / x.people;

    free(buffer);
    return x;
}
Simulation getFirst(Day *array)
{
    Simulation x;
    x.S = array->S;
    x.I = array->I;
    x.R = array->R;
    return x;
}
Simulation getSimulation(float b, float y, Simulation *array)
{
    Simulation x;
    x.S = array->S - b * array->S * array->I;
    x.I = array->I + b * array->S * array->I - y * array->I;
    x.R = array->R + y * array->I;
    return x;
}
void loadDays(int count, Day *array, FILE *filename)
{
    for (int i = 0; i < count; i++)
    {
        array[i] = getDay(filename);
    }
}
void loadSimulations(int count, Simulation *array, float b, float y)
{
    for (int i = 0; i < count - 1; i++)
    {
        array[i + 1] = getSimulation(b, y, &array[i]);
    }
}