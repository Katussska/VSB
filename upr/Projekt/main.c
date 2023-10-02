#include "library.h"

int main(int argc, char **argv)
{
    parametersCheck(argc);

    char *name = "--infections_per_day";
    char *CHinfections_per_day = getParameter(name, argv, argc);
    float infections_per_day = atof(CHinfections_per_day);
    name = "--infectious_days";
    char *CHinfectious_days = getParameter(name, argv, argc);
    float infectious_days = atof(CHinfectious_days);
    name = "--real_data";
    char *real_data = getParameter(name, argv, argc);
    name = "--output";
    char *output = getParameter(name, argv, argc);
    int days = countDays(real_data);

    FILE *data_csv = fopen(real_data, "r");
    fileCheck(data_csv);

    Day *dayArray = (Day *)malloc(sizeof(Day) * days);
    Simulation *simulationArray = (Simulation *)malloc(sizeof(Simulation) * days);

    float b = infections_per_day;
    float y = 1 / infectious_days;

    loadDays(days, dayArray, data_csv);
    fclose(data_csv);

    simulationArray[0] = getFirst(&dayArray[0]);
    loadSimulations(days, simulationArray, b, y);

    makeChart(output, days, dayArray, simulationArray);

    free(CHinfections_per_day);
    free(CHinfectious_days);
    free(simulationArray);
    free(real_data);
    free(dayArray);
    free(output);
    return 0;
}
