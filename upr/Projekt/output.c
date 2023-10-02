#include "library.h"

void makeChart(char *path, int count, Day *array, Simulation *array2)
{
    FILE *SVGchart = fopen(path, "wt");
    fileCheck(SVGchart);
    printHead(SVGchart);
    int x = 100;
    x = printDays(x, count, SVGchart);
    printGrit(x, SVGchart);

    printDaySLine(array, SVGchart, count);
    printDayILine(array, SVGchart, count);
    printDayRLine(array, SVGchart, count);

    printSimulationSLine(array2, SVGchart, count);
    printSimulationILine(array2, SVGchart, count);
    printSimulationRLine(array2, SVGchart, count);

    printInfo(SVGchart);

    fprintf(SVGchart, "</svg>\n");
    fclose(SVGchart);
}
void printHead(FILE *fileName)
{
    fprintf(fileName, "<svg version=\"1.2\" xmlns=\"http://www.w3.org/2000/svg\" xmlns:xlink=\"http://www.w3.org/1999/xlink\" class=\"graph\" aria-labelledby=\"title\" role=\"img\">\n<title id =\"title\">Graf vývoje epidemie</title>\n");
}
int printDays(int x, int count, FILE *fileName)
{
    fprintf(fileName, "<g>\n");
    // fprintf(fileName, "%d", x);
    for (int i = 0; i < count; i++)
    {
        fprintf(fileName, "<text x=\"");
        fprintf(fileName, "%d", x);
        fprintf(fileName, "\" y=\"445\">");
        fprintf(fileName, "%d", i + 1);
        fprintf(fileName, "</text>\n");
        x = x + 50;
    }
    fprintf(fileName, "<text x=\"");
    fprintf(fileName, "%d", x / 2 + 25);
    fprintf(fileName, "\" y=\"470\" class=\"label-title\">Days</text>\n");
    fprintf(fileName, "<line x1=\"99\" y1=\"430\" x2=\"");
    fprintf(fileName, "%d", x - 50);
    fprintf(fileName, "\" y2=\"430\" stroke=\"black\" />\n");
    fprintf(fileName, "</g>\n");
    return x;
}
void printGrit(int x, FILE *fileName)
{
    fprintf(fileName, "<g class=\"labels y-labels\">\n");
    int y = 130;
    float p = 1;
    for (int i = 0; i < 10; i++)
    {
        fprintf(fileName, "<text x=\"70\" y=\"");
        fprintf(fileName, "%d", y);
        fprintf(fileName, "\">");
        fprintf(fileName, "%.1f", p);
        fprintf(fileName, "</text>\n");
        fprintf(fileName, "<line x1=\"100\" y1=\"");
        fprintf(fileName, "%d", y);
        fprintf(fileName, "\" x2=\"");
        fprintf(fileName, "%d", x - 50);
        fprintf(fileName, "\" y2=\"");
        fprintf(fileName, "%d", y);
        fprintf(fileName, "\" stroke=\"#ECEFEF\" />\n");

        p = p - 0.1;
        y = y + 30;
    }
    fprintf(fileName, "<text x=\"70\" y=\"");
    fprintf(fileName, "%d", y);
    fprintf(fileName, "\">0</text>\n");
    fprintf(fileName, "<line x1=\"100\" y1=\"");
    fprintf(fileName, "%d", y);
    fprintf(fileName, "\" x2=\"100\" y2=\"110\" stroke=\"black\" />\n");

    fprintf(fileName, "</g>\n");
}
void printDaySLine(Day *array, FILE *fileName, int count)
{
    fprintf(fileName, "<polyline points=\"");
    int x = 100;
    for (int i = 0; i < count; i++)
    {
        int y = 430 - (300 * array[i].S);
        fprintf(fileName, "%d,%d ", x, y);
        x = x + 50;
    }
    fprintf(fileName, "\" fill=\"none\" stroke=\"green\" />\n");
}
void printDayILine(Day *array, FILE *fileName, int count)
{
    fprintf(fileName, "<polyline points=\"");
    int x = 100;
    for (int i = 0; i < count; i++)
    {
        int y = 430 - (300 * array[i].I);
        fprintf(fileName, "%d,%d ", x, y);
        x = x + 50;
    }
    fprintf(fileName, "\" fill=\"none\" stroke=\"red\" />\n");
}
void printDayRLine(Day *array, FILE *fileName, int count)
{
    fprintf(fileName, "<polyline points=\"");
    int x = 100;
    for (int i = 0; i < count; i++)
    {
        int y = 430 - (300 * array[i].R);
        fprintf(fileName, "%d,%d ", x, y);
        x = x + 50;
    }
    fprintf(fileName, "\" fill=\"none\" stroke=\"blue\" />\n");
}
void printSimulationSLine(Simulation *array, FILE *fileName, int count)
{
    fprintf(fileName, "<polyline points=\"");
    int x = 100;
    for (int i = 0; i < count; i++)
    {
        int y = 430 - (300 * array[i].S);
        fprintf(fileName, "%d,%d ", x, y);
        x = x + 50;
    }
    fprintf(fileName, "\" fill=\"none\" stroke=\"#72DD72\" />\n");
}
void printSimulationILine(Simulation *array, FILE *fileName, int count)
{
    fprintf(fileName, "<polyline points=\"");
    int x = 100;
    for (int i = 0; i < count; i++)
    {
        int y = 430 - (300 * array[i].I);
        fprintf(fileName, "%d,%d ", x, y);
        x = x + 50;
    }
    fprintf(fileName, "\" fill=\"none\" stroke=\"#DD7272\" />\n");
}
void printSimulationRLine(Simulation *array, FILE *fileName, int count)
{
    fprintf(fileName, "<polyline points=\"");
    int x = 100;
    for (int i = 0; i < count; i++)
    {
        int y = 430 - (300 * array[i].R);
        fprintf(fileName, "%d,%d ", x, y);
        x = x + 50;
    }
    fprintf(fileName, "\" fill=\"none\" stroke=\"#728FDD\" />\n");
}
void printInfo(FILE *fileName)
{
    fprintf(fileName, "<g>\n");
    fprintf(fileName, "<circle cx=\"100\" cy=\"480\" r=\"5\" fill=\"green\" />\n");
    fprintf(fileName, "<circle cx=\"100\" cy=\"495\" r=\"5\" fill=\"red\" />\n");
    fprintf(fileName, "<circle cx=\"100\" cy=\"510\" r=\"5\" fill=\"blue\" />\n");
    fprintf(fileName, "<circle cx=\"100\" cy=\"525\" r=\"5\" fill=\"#72DD72\" />\n");
    fprintf(fileName, "<circle cx=\"100\" cy=\"540\" r=\"5\" fill=\"#DD7272\" />\n");
    fprintf(fileName, "<circle cx=\"100\" cy=\"555\" r=\"5\" fill=\"#728FDD\" />\n");
    fprintf(fileName, "<text x=\"110\" y=\"485\">Zdraví</text>\n");
    fprintf(fileName, "<text x=\"110\" y=\"500\">Nakažení</text>\n");
    fprintf(fileName, "<text x=\"110\" y=\"515\">Uzdravení</text>\n");
    fprintf(fileName, "<text x=\"110\" y=\"530\">Zdraví (Simulace)</text>\n");
    fprintf(fileName, "<text x=\"110\" y=\"545\">Nakažení (Simulace)</text>\n");
    fprintf(fileName, "<text x=\"110\" y=\"560\">Uzdravení (Simulace)</text>\n");
    fprintf(fileName, "</g>\n");
}