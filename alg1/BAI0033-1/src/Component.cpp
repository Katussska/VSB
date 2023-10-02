#include "headers/Component.h"

/**
 * Konstruktor
 */
Component::Component()
{
}
/**
 * Destruktor
 */
Component::~Component()
{
}
/**
 * Získání excentricit
 */
void Component::getExcentricities()
{
    std::queue<Point *> pointies; // procházení do šířky pro nejkratší vzdálenost (vektor je do hloubky)
    Point *temp;                  // uložení bodu, kterého popneme z queue, ale potřebujeme používat jeho sousedy

    for (int i = 0; i < this->points.size(); i++)
    {
        for (int j = 0; j < this->points.size(); j++) // musíme vynulovat vše při procházení každého bodu
        {
            this->points[j]->checked = false;
            this->points[j]->distance = 0; // abychom zjistili vzdálenost od aktuálního bodu (jinak by tam zůstala ta z minula)
        }

        pointies.push(this->points[i]); // pushneme do queue současný bod, ok terého počítáme dostance

        while (!pointies.empty())
        {
            temp = pointies.front();
            temp->checked = true;
            pointies.pop(); // smazání frontu, proto ukládáme do temp

            for (int k = 0; k < temp->neighbors.size(); k++) // projíždíme sousedy
            {
                if (!(temp->neighbors[k]->checked)) // pokud nebyl navšíven
                {
                    temp->neighbors[k]->checked = true;
                    temp->neighbors[k]->distance = temp->distance + 1; // zvětšíme vzdálenost
                    pointies.push(temp->neighbors[k]);                 // pushneme do queue
                }
            }
        }

        int maximal = 0; // index bodu s maximální distance pro nalezení excentricity
        for (int j = 0; j < this->points.size(); j++)
        {
            if (this->points[j]->distance >= this->points[maximal]->distance)
            {
                maximal = j;
            }
        }

        this->points[i]->excentricity = this->points[maximal]->distance;
    }
}
/**
 * Získání průměru
 * Vybere největší excentricitu
 */
int Component::getDiameter()
{
    int maximal = 0;
    for (int j = 0; j < this->points.size(); j++)
    {
        if (this->points[j]->excentricity >= this->points[maximal]->excentricity)
        {
            maximal = j;
        }
    }
    return this->points[maximal]->excentricity;
}
/**
 * Získání poloměru
 * Vybere nejmenší excentricitu
 */
int Component::getRadius()
{
    int maximal = 0;
    for (int j = 0; j < this->points.size(); j++)
    {
        if (this->points[j]->excentricity <= this->points[maximal]->excentricity)
        {
            maximal = j;
        }
    }
    return this->points[maximal]->excentricity;
}