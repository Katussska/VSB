#include <string>

using namespace std;

class Tree
{
private:
    string key;
    string value;
    Tree *nextY;
    Tree *nextN;
    int depth;

public:
    Tree(string left, string right, int depth);
    ~Tree();
    string GetKey();
    string GetValue();
    int GetDepth();
    Tree *GetNext(char strana);
    Tree *CreateNext(string k, string v, char strana);
};
