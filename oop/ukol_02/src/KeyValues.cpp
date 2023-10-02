#include "KeyValues.h"

using namespace std;

KeyValues::KeyValues(int n)
{
    this->keyValues = new KeyValue *[n];
    this->count = 0;
}

KeyValues::~KeyValues()
{
    // for (int i = 0; i < this->count; i++)
    // {
    //     delete this->keyValues[i];
    // }

    delete[] this->keyValues;
}

int KeyValues::Count()
{
    return this->count;
}

KeyValue *KeyValues::CreateObject(int k, double v)
{
    KeyValue *newObject = new KeyValue(k, v);

    this->keyValues[this->count] = newObject;
    this->count += 1;

    return newObject;
}

KeyValue *KeyValues::SearchObject(int k)
{
    for (int i = 0; i < this->count; i++)
    {
        if (this->keyValues[i]->GetKey() == k)
        {
            return this->keyValues[i];
        }
    }

    return nullptr;
}

KeyValue *KeyValues::RemoveObject(int k)
{
    auto newArray = new KeyValue *[this->count - 1];
    KeyValue *tmp;
    bool found = false;
    for (int i = 0; i < this->count; i++)
    {
        if (this->keyValues[i]->GetKey() == k)
        {
            tmp = this->keyValues[i];
            found = true;
            continue;
        }
        if (found == true)
        {
            newArray[i - 1] = this->keyValues[i];
            continue;
        }
        newArray[i] = this->keyValues[i];
    }
    this->count -= 1;
    this->keyValues = newArray;

    return tmp;
}