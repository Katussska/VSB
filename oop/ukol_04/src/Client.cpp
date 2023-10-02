#include "Client.h"

#include <utility>

int Client::objectsCount = 0;

Client::Client(int id, string name)
{
    this->id = id;
    this->name = std::move(name);
    Client::objectsCount += 1;
}

int Client::getId() const
{
    return this->id;
}

string Client::getName()
{
    return this->name;
}

int Client::getCount() const
{
    return this->objectsCount;
}