#include <iostream>
#include <vector>

using namespace std;

// Na vstupu je nejprve přirozené číslo (nosnost vozidla).
// Na každém dalším řádku je vždy dvojice přirozených čísel (váha předmětu, cena za jeho přepravu).
// Vozidlo s načtenou nosností může převézt najednou libovolný počet předmětů, ale součet jejich vah nesmí překročit nosnost.
// Za takový převoz dostane součet jednotlivých cen přepravených předmětů.
// Pro jednoduchost neřešme jednotky - prostě všechny váhy i nosnost jsou ve stejných jednotkách a všechny ceny ve stejné měně (není důležité, které).
// Úkolem je vytvořit funkci int find_max(vector<item> items, int max_load), která najde nejlepší cenu, kterou lze získat za jeden náklad.
// Typ item v parametru funkce je definován: struct item {int weight; int price;};

// K dispozici máte několik ukázkových vstupních souborů.
// Každý má (pro kontrolu správnosti vašeho programu) jméno podle správného výsledku, který by vaše funkce pro něj měla zjistit.
// Do komentáře v odevzdáváném zdrojovém kódu uveďte asymptotický odhad časové složitosti vašeho řešení.

struct item
{
    int weight;
    int price;
};

item setter(bool *b, vector<item> *items)
{
    int p = 0;
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
    int max = 0;
    int nrElem = items.size();
    item sum = {0, 0};

    int nrSets = 1;
    bool *bits = new bool[nrElem];
    for (int i = 0; i < nrElem; i++)
    {
        bits[i] = false;
        nrSets *= 2;
    }
    sum = setter(bits, &items);
    if (sum.weight <= max_load)
    {
        max = sum.price;
    }
    nrSets--;
    for (int i = 0; i < nrSets; i++)
    {
        int j = 0;
        while (bits[j])
        {
            bits[j] = false;
            j++;
        }
        bits[j] = true;
        sum = setter(bits, &items);
        if (sum.weight <= max_load && sum.price > max)
        {
            max = sum.price;
        }
    }
    return max;
}

int main(int argc, char **argv)
{
    vector<item> items;
    item it;
    int max_load;

    cin >> max_load;
    while (!cin.eof())
    {
        cin >> it.weight >> it.price;
        items.push_back(it);
    }

    cout << "Maximal possible income: " << find_max(items, max_load) << endl;
}