#ifndef CLIENT_H
#define CLIENT_H

#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Client
{
private:
    int id;
    string name;

public:
    Client(int id, string name);
    int getId() const;
    string getName();
};

#endif