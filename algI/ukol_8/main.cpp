#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <cstdlib>
#include <ctime>

using namespace std;

struct Item
{
    int key;
    string value;
};

int comparisonCount;
int swapCount;

/**
 * Nacteni vstupniho souboru ciselniku do vektoru polozek reprezentovanych
 * strukturami Item, kazda polozka ma celociselny klic (identifikator)
 * a retezcovou hodnotu (nazev)
 * V souboru se ceka kazda polozka na samostatnem radku, na zacatku je
 * klic mezerou oddeleny od hodnoty, ta je potom az do konce radku.
 *
 * @param name Jmeno souboru, ze ktereho se polozky budou nacitat
 * @return Vektor vsech polozek nactenych ze souboru
 */
vector<Item> read_items(string name)
{

    ifstream infile;
    infile.open(name);
    vector<Item> items;
    Item it;

    if (!infile.is_open())
    {
        cerr << "File could not be opened" << endl;
        exit(-1);
    }

    while (!infile.eof())
    {
        infile >> it.key;
        if ((infile.rdstate() & std::ifstream::failbit) != 0)
            continue;
        infile.ignore(256, ' ');
        getline(infile, it.value);
        items.push_back(it);
    }
    infile.close();
    return items;
}

int First(vector<Item> &items, int l, int r)
{
    int pivot = items.begin()->key;

    int count = 0;
    for (int i = l + 1; i <= r; i++)
    {
        if (items.at(i).key <= pivot)
            count++;
    }

    int pivotIndex = l + count;
    swap(items.at(pivotIndex).key, items.at(l).key);
    swapCount++;

    int i = l, j = r;

    while (i < pivotIndex && j > pivotIndex)
    {

        while (items.at(i).key <= pivot)
        {
            i++;
        }

        while (items.at(j).key > pivot)
        {
            j--;
        }

        if (i < pivotIndex && j > pivotIndex)
        {
            swap(items.at(i++), items.at(j--));
            swapCount++;
        }
    }

    return pivotIndex;
}

int Random(vector<Item> &items, int l, int r)
{
    int pivot = rand() % items.size();

    int count = 0;
    for (int i = l + 1; i <= r; i++)
    {
        if (items.at(i).key <= pivot)
            count++;
    }

    int pivotIndex = l + count;
    swap(items.at(pivotIndex).key, items.at(l).key);
    swapCount++;

    int i = l, j = r;

    while (i < pivotIndex && j > pivotIndex)
    {

        while (items.at(i).key <= pivot)
        {
            i++;
        }

        while (items.at(j).key > pivot)
        {
            j--;
        }

        if (i < pivotIndex && j > pivotIndex)
        {
            swap(items.at(i++), items.at(j--));
            swapCount++;
        }
    }

    return pivotIndex;
}

/*int median(vector<Item> &items)
{
    size_t n = items.size() / 2;
    nth_element(items.begin(), items.begin() + n, items.end());
    return items.at(n).key;
}*/

int Median(vector<Item> &items, int l, int r)
{
    int pivot = 15;

    int count = 0;
    for (int i = l + 1; i <= r; i++)
    {
        if (items.at(i).key <= pivot)
            count++;
    }

    int pivotIndex = l + count;
    swap(items.at(pivotIndex).key, items.at(l).key);
    swapCount++;

    int i = l, j = r;

    while (i < pivotIndex && j > pivotIndex)
    {

        while (items.at(i).key <= pivot)
        {
            i++;
        }

        while (items.at(j).key > pivot)
        {
            j--;
        }

        if (i < pivotIndex && j > pivotIndex)
        {
            swap(items.at(i++), items.at(j--));
            swapCount++;
        }
    }

    return pivotIndex;
}

void Quicksort(vector<Item> &items, int l, int r, int (*pivot)(vector<Item> &, int, int))
{
    if (l >= r)
        return;

    int p = pivot(items, l, r);

    Quicksort(items, l, p - 1, pivot);

    Quicksort(items, p + 1, r, pivot);
}

int main(int argc, char **argv)
{
    if (argc < 2)
    {
        cerr << "Missing arguments" << endl;
        exit(-1);
    }
    std::srand(std::time(nullptr));

    vector<Item> items;
    items = read_items(argv[1]);
    vector<Item> items2 = items;
    vector<Item> items3 = items;

    comparisonCount = swapCount = 0;
    Quicksort(items, 0, items.size() - 1, First);
    cerr << "First: " << comparisonCount << " porovnani, " << swapCount << " prohozeni" << endl;
    for (int i = 0; i < items.size(); i++)
    {
        cout << items.at(i).key << " " << items.at(i).value << endl;
    }

    cout << endl;

    comparisonCount = swapCount = 0;
    Quicksort(items2, 0, items2.size() - 1, Random);
    cerr << "Random: " << comparisonCount << " porovnani, " << swapCount << " prohozeni" << endl;
    for (int i = 0; i < items.size(); i++)
    {
        cout << items2.at(i).key << " " << items2.at(i).value << endl;
    }

    cout << endl;

    comparisonCount = swapCount = 0;
    Quicksort(items3, 0, items2.size() - 1, Median);
    cerr << "Median: " << comparisonCount << " porovnani, " << swapCount << " prohozeni" << endl;
    for (int i = 0; i < items.size(); i++)
    {
        cout << items3.at(i).key << " " << items3.at(i).value << endl;
    }

    /*for (unsigned long i = 0; i < items.size(); i++)
    {
        if (items[i].key == items2[i].key && items[i].key == items3[i].key)
        {
            cout << items[i].key << " " << items[i].value << endl;
        }
        else
        {
            cout << "Vysledky serazeni se lisi" << endl;
            return 0;
        }
    }*/

    return 1;
}
