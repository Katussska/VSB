#include "Point.h"

/**
 * Třída komponenta
 */
class Component
{
public:
    std::vector<Point *> points; /**< vektor bodů, které komponenta obsahuje*/

    Component();
    ~Component();

    void getExcentricities();
    int getDiameter();
    int getRadius();
};
