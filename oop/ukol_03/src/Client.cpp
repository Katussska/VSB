#include "Client.h"

#include <utility>

Client::Client(int id, string name)
{
    this->id = id;
    this->name = std::move(name);
}

int Client::getId() const
{
    return this->id;
}

string Client::getName()
{
    return this->name;
}