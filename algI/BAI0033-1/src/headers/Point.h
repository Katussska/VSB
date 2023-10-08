#include <queue>
#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <algorithm>
/**
 * Třída Point
 */
class Point
{
public:
    int value;                      /**< hodnota bodu*/
    std::vector<Point *> neighbors; /**< vektor sousedů bodu*/
    bool checked = false;           /**< kontrola, jestli byl bod projet*/
    int excentricity = 0;           /**< excentricita bodu*/
    // jak daleko je bod, který je od tohoto bodu nejdál tou nejefektivnější trasou

    int distance = 0; /**vzdálenost bodu od počátečního bodu*/

    Point(int value);
    ~Point();
};
