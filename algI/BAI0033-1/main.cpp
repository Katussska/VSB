/*
 * @author BAI033
 * @date 1.5.2023
 */

#include "src/headers/Graph.h"

int main(int argc, char **argv)
{
    time_t loadingBegin;
    time_t loadingFinish;
    time_t findingBegin;
    time_t findingFinish;

    time(&loadingBegin);

    if (argc != 2)
    {
        std::cout << "Missing file.\n";
        return 1;
    }

    Graph graph(argv[1]); // načtení grafu v konstruktoru
    graph.findComponents();

    time(&loadingFinish);

    std::cout << "Loading time: " << ((double)loadingFinish - loadingBegin) / 60 << " minutes" << std::endl;

    time(&findingBegin);

    Component *biggestComponent = graph.biggestComponent();
    biggestComponent->getExcentricities();

    time(&findingFinish);

    std::cout << "Searching time: " << ((double)findingFinish - findingBegin) / 60 << " minutes" << std::endl;

    std::cout << "Radius: " << biggestComponent->getRadius() << std::endl;
    std::cout << "Diameter: " << biggestComponent->getDiameter() << std::endl;

    return 0;
}