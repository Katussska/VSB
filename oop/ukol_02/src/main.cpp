#include "KeyValues.h"
#include "Invoice.h"

using namespace std;

void KVfunction();
void printArray(KeyValues *array);
void INVFunction();

int main()
{
    KVfunction();

    INVFunction();

    return 0;
}

void KVfunction()
{
    int N = 5;
    KeyValues *myKeyValues = new KeyValues(N);

    KeyValue *myKeyValue = myKeyValues->CreateObject(0, 0.5);

    for (int i = 1; i < N; i++)
    {
        myKeyValues->CreateObject(i, i + 0.5);
    }
// printArray
    printArray(myKeyValues);

    // cout << myKeyValues->Count() << endl;

    cout << myKeyValues->RemoveObject(3)->GetValue() << endl;

    // cout << myKeyValues->Count() << endl;

    // printArray(myKeyValues);

    delete myKeyValues;
}

void printArray(KeyValues *array)
{
    for (int i = 0; i < array->Count(); i++)
    {
        cout << array->SearchObject(i)->GetValue() << endl;
    }
}

void INVFunction()
{
    cout << "Faktura" << endl;

    Invoice *faktura = new Invoice(125, "Kateřina", "Baierová", "Masarykova 420");

    faktura->addItem("mléko", 17.90);
    faktura->addItem("chleba", 35.60);
    faktura->addItem("sýr", 40.20);
    faktura->addItem("šunka", 53.80);

    cout << faktura->priceSum() << endl;
}