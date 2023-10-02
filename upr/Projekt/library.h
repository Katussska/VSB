#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdbool.h>

typedef struct
{
    float susceptible;
    float infected;
    float recovered;
    float people;
    float S;
    float I;
    float R;
} Day;
typedef struct
{
    float S;
    float I;
    float R;
} Simulation;

void parametersCheck(int argc);
char *getParameter(char *name, char **argv, int argc);
void fileCheck(FILE *fileName);
int countDays(char *fileName);
Day getDay(FILE *filename);
Simulation getFirst(Day *array);
Simulation getSimulation(float b, float y, Simulation *array);
void loadDays(int count, Day *array, FILE *filename);
void loadSimulations(int count, Simulation *array, float b, float y);

void makeChart(char *path, int count, Day *array, Simulation *array2);
void printHead(FILE *fileName);
int printDays(int x, int count, FILE *fileName);
void printGrit(int x, FILE *fileName);
void printDaySLine(Day *array, FILE *fileName, int count);
void printDayILine(Day *array, FILE *fileName, int count);
void printDayRLine(Day *array, FILE *fileName, int count);
void printSimulationSLine(Simulation *array, FILE *fileName, int count);
void printSimulationILine(Simulation *array, FILE *fileName, int count);
void printSimulationRLine(Simulation *array, FILE *fileName, int count);
void printInfo(FILE *fileName);