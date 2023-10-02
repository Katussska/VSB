#include <iostream>
#include <string>
#include "KeyValue.h"
#include "Tree.h"

using namespace std;

void KeyValueFunction(int amount);

Tree *CreateTree();
void PrintTree(Tree *tree);
void Tab(Tree *tree);

int main()
{
    PrintTree(CreateTree());
    KeyValueFunction(15);
    return 0;
}

/* strom s otázkami a konečnými možnostmi, dal by se relativně jednoduše rekurzivně zadávat z konzole
(funkce by se ptala na key+value u zvoleného y/n, případně ukončení uzlu),
pro pohodlí zadaný předem, ať se při každém testu nemusí zadávat */

Tree *CreateTree()
{
    Tree *Dotaz = new Tree("・Je to savec?", "\nZvíře\n", 0);

    Dotaz->CreateNext("・Vodní?", "Savec", 'y');

    Dotaz->GetNext('y')->CreateNext("・Má ploutve?", "Vodní savec", 'y');

    Dotaz->GetNext('y')->GetNext('y')->CreateNext("・Pouze ve vodě?", "Mořský savec s ploutvemi", 'y');

    Dotaz->GetNext('y')->GetNext('y')->GetNext('y')->CreateNext("", "Vodní savec s ploutvemi žijící pouze ve vodě (delfín)", 'y');
    Dotaz->GetNext('y')->GetNext('y')->GetNext('y')->CreateNext("", "Vodní savec s ploutvemi žijící také mimo vodu (tuleň)", 'n');

    Dotaz->GetNext('y')->GetNext('y')->CreateNext("", "Vodní savec bez ploutví (Vydra)", 'n');

    Dotaz->GetNext('y')->CreateNext("・Je ochlupený?", "Suchozemský savec", 'n');

    Dotaz->GetNext('y')->GetNext('n')->CreateNext("・Je malý?", "Ochlupený suchozemský savec", 'y');

    Dotaz->GetNext('y')->GetNext('n')->GetNext('y')->CreateNext("", "Ochlupený malý suchozemský savec (krtek)", 'y');
    Dotaz->GetNext('y')->GetNext('n')->GetNext('y')->CreateNext("", "Ochlupený velký suchozemský savec (medvěd)", 'n');

    Dotaz->GetNext('y')->GetNext('n')->CreateNext("", "Bezsrstý suchozemský savec (slon)", 'n');

    Dotaz->CreateNext("・Je to pták?", "Jiný druh", 'n');

    Dotaz->GetNext('n')->CreateNext("・Umí létat?", "Pták", 'y');

    Dotaz->GetNext('n')->GetNext('y')->CreateNext("", "Létavý pták (čáp)", 'y');
    Dotaz->GetNext('n')->GetNext('y')->CreateNext("", "Nelétavý pták (slepice)", 'n');

    Dotaz->GetNext('n')->CreateNext("・Je to plaz?", "Jiný druh", 'n');
    Dotaz->GetNext('n')->GetNext('n')->CreateNext("", "Zvíře je plaz", 'y');
    Dotaz->GetNext('n')->GetNext('n')->CreateNext("", "Zvíře je jiný druh", 'n');

    return Dotaz;
}

void PrintTree(Tree *tree)
{
    cout << tree->GetValue() << endl;

    // nejdřív strana "Ano"
    if (tree->GetNext('y') != nullptr)
    {
        Tab(tree);
        cout << tree->GetKey() << endl;
        Tab(tree);
        cout << " Ano -> ";
        PrintTree(tree->GetNext('y'));
    }

    // pak strana "Ne"
    if (tree->GetNext('n') != nullptr)
    {
        Tab(tree);
        cout << " Ne -> ";
        PrintTree(tree->GetNext('n'));
    }
}

void Tab(Tree *tree)
{
    for (int i = 0; i < tree->GetDepth(); i++)
    {
        cout << "  ";
    }
}

void KeyValueFunction(int amount)
{
    KeyValue *pointer;
    int key = 1;
    double value = 0.5;
    KeyValue hodnota = KeyValue(key, value);
    pointer = &hodnota;
    for (int i = 0; i < amount; i++)
    {
        key++;
        value++;
        pointer = pointer->CreateNext(key, value);
    }
    pointer = &hodnota;
    do
    {
        cout << pointer->GetKey() << endl;
        pointer = pointer->GetNext();
    } while (pointer->GetNext() != nullptr);
}
