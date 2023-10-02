#include "KeyValue.h"

using namespace std;

class KeyValues
{
private:
    KeyValue **keyValues;
    int count;

public:
    KeyValues(int n);
    ~KeyValues();
    KeyValue *CreateObject(int k, double v);
    KeyValue *SearchObject(int key);
    KeyValue *RemoveObject(int k);
    int Count();
};
