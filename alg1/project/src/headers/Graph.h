#include "Component.h"
/**
 * Třída graf
 */
class Graph
{
public:
    std::vector<Point *> points;         /**< vektor bodů nacházejících se v grafu*/
    std::vector<Component *> components; /**< vektor komponent nacházejících se v grafu*/

    Graph(std::string fileName);
    ~Graph();

    void findComponents();
    int where(int a);
    Component *biggestComponent();
};
