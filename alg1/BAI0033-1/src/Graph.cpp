#include "headers/Graph.h"

/**
 * Konstruktor s načítáním grafu
 * @param fileName soubor s grafem
 */
Graph::Graph(std::string fileName)
{
    std::ifstream file(fileName);
    if (!file.is_open()) // ověření
    {
        std::cout << "Couldn't open file.\n";
        return;
    }

    int x, y, wx, wy;

    while (!file.eof())
    {
        file >> x >> y; // vezme z filu hodnoty a zapise do x prvni a do y druhou
        wx = where(x);  // nalezení a uložení indexu x
        wy = where(y);  // nalezení a uložení indexu y

        if (wx < 0) // pokud nejsou vytvorene, tak se pushnou
        {
            this->points.push_back(new Point(x)); // vytvoří se nový point x
            wx = points.size() - 1;               // potrebujeme si udrzet, kde je a zapsat mu sousedy
                                                  // better algoritmus, bcs nemusime volat where() 150x
        }

        if (wy < 0) // pokud nejsou vytvorene, tak se pushnou
        {
            this->points.push_back(new Point(y));                       // vytvoří se nový point y
            this->points[wx]->neighbors.push_back(this->points.back()); // pushnem y do sousedu x
            this->points.back()->neighbors.push_back(this->points[wx]); // pushnem x do sousedu y
        }
        else
        {
            this->points[wx]->neighbors.push_back(this->points[wy]); // pushnem y do sousedu x
            this->points[wy]->neighbors.push_back(this->points[wx]); // pushnem x do sousedu y
        }
    }

    file.close();
}
/**
 * Destruktor
 * Smaže všechny pointy
 */
Graph::~Graph()
{
    for (int i = 0; i < this->points.size(); i++)
    {
        delete points[i];
    }

    for (int i = 0; i < this->components.size(); i++)
    {
        delete components[i];
    }
}
/**
 * Nalezení indexu
 * @param a vrchol, kterému chceme nalézt index
 */
int Graph::where(int a)
{
    for (int i = 0; i < this->points.size(); i++)
    {
        if (this->points[i]->value == a)
        {
            return i;
        }
    }
    return -666; // obviously cislo, na ktere se to nedostane
}
/**
 *Nalezení komponenty
 */
void Graph::findComponents() // procházení do hloubky
{
    Point *live;                    // bod, se kterým se momentálně pracuje
    Component *newComponent;        // pointer pro novou komponentu
    std::vector<Point *> tempoints; // vektor pointů pro zpracování

    for (int i = 0; i < this->points.size(); i++) // procházíme pointy grafu
    {
        if (!this->points[i]->checked) // pokud nebyly navštívené
        {
            newComponent = new Component;         // naalokuju novou komponentu
            tempoints.push_back(this->points[i]); // zapíšu bod do vektoru

            while (!tempoints.empty())
            {
                live = tempoints.back(); // uložení pointu, abychom o něj u popu nepřišli

                if (!live->checked)
                {
                    live->checked = true;
                    newComponent->points.push_back(live); // zapsání do vektoru komponenty, pokud nebyl navštíven
                }

                tempoints.pop_back(); // smazani bodu

                for (int i = 0; i < live->neighbors.size(); i++) // projetí sousedů aktuálního bodu
                {
                    if (!live->neighbors[i]->checked)
                    {
                        tempoints.push_back(live->neighbors[i]); // pokud nebyl bod navštíven, zapíšeme
                    }
                }
            }
            this->components.push_back(newComponent); // uložíme hotovou komponentu do komponent grafu
            newComponent = nullptr;
        }
    }
}
/**
 * Nalezení největší komponenty
 */
Component *Graph::biggestComponent()
{
    int maximal = 0; // index komponenty s maximální velikostí
    for (int i = 0; i < this->components.size(); i++)
    {
        if (this->components[i]->points.size() >= this->components[maximal]->points.size())
        {
            maximal = i;
        }
    }
    return this->components[maximal];
}