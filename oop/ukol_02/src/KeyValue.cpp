#include "KeyValue.h"

using namespace std;

KeyValue::KeyValue(int k, double v)
{
    this->key = k;
    this->value = v;
}

int KeyValue::GetKey()
{
    return this->key;
}

double KeyValue::GetValue()
{
    return this->value;
}