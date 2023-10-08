#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

/**
 * Reprezentace jedné polozky urcene k preprave
 */
struct item
{
    int weight; ///< Vaha polozky
    int price;  ///< Cena za prepravu teto polozky
};

/**
 * Nacteni vstupniho souboru do vektoru obsahujiciho pro kazdou polozku
 * (coz odpovida radku ve vstupnim souboru) dvojici celociselnych hodnot
 * vaha a cena
 *
 * @param name Jmeno souboru, ze ktereho se polozky budou nacitat
 * @return Vektor vsech polozek nactenych ze souboru
 */
vector<item> read_file(string name)
{

    ifstream infile;
    infile.open(name);
    vector<item> items;
    item it;

    if (!infile.is_open())
    {
        cerr << "File could not be opened" << endl;
        exit(-1);
    }

    while (!infile.eof())
    {
        infile >> it.weight >> it.price;
        items.push_back(it);
    }

    infile.close();

    return items;
}

/**
 * Najde maximalni mozny soucet cen produktu takovy,
 * ze soucet vah polozek do nej zapoctenych je
 * mensi nebo povolene nosnosti.
 *
 * @param items Vektor polozek, mezi nimiz hledame tu maximalni sadu
 * @param max_load Povolena nosnost - maximalni mozny soucet vah vybranych produktu
 * @return Nalezena maximalni mozna cena pri splneni podminek
 *
 */

item setter(bool *b, vector<item> *items)
{
    item sum = {0, 0};

    for (int i = 0; i < (*items).size(); i++)
    {
        if (b[i])
        {
            sum.weight += ((*items)[i]).weight;
            sum.price += ((*items)[i]).price;
        }
    }

    return sum;
}

int find_max(vector<item> items, int max_load)
{

    int maximum = 0;
    int elemCount = items.size();
    item sum = {0, 0};

    int setCount = 1;
    bool *bits = new bool[elemCount];

    for (int i = 0; i < elemCount; i++)
    {
        bits[i] = false;
        setCount *= 2;
    }

    sum = setter(bits, &items);

    if (sum.weight <= max_load)
    {
        maximum = sum.price;
    }

    setCount--;

    for (int i = 0; i < setCount; i++)
    {
        int j = 0;
        while (bits[j])
        {
            bits[j] = false;
            j++;
        }
        bits[j] = true;
        sum = setter(bits, &items);
        if (sum.weight <= max_load && sum.price > maximum)
        {
            maximum = sum.price;
        }
    }
    return maximum;
}

int main(int argc, char **argv)
{
    if (argc < 3)
    {
        cerr << "Missing arguments" << endl;
        exit(-1);
    }

    cout << find_max(read_file(argv[1]), stoi(argv[2])) << endl;
    return 1;
}