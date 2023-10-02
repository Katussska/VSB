#ifndef BANK_H
#define BANK_H

#include "Client.h"
#include "Account.h"

using namespace std;

class Bank
{
private:
    Client **Clients;
    int clientsMax;
    int clientsCount = 0;

    Account **Accounts;
    int accountsMax;
    int accountsCount = 0;

public:
    Bank(int clientsMax, int accountsMax);
    ~Bank();

    Client *getClient(int id);
    Account *getAccount(int number);

    Client *createClient(int id, string name);
    Account *createAccount(int number, Client *owner);
    Account *createAccount(int number, Client *owner, double interest);
    Account *createAccount(int number, Client *owner, Client *partner);
    Account *createAccount(int number, Client *owner, Client *partner, double interest);

    void addInterests();
};

#endif