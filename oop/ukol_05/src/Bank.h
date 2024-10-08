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

    Account **Accounts;
    PartnerAccount **PartnerAccounts;
    int accountsMax;

public:
    Bank(int clientsMax, int accountsMax);
    ~Bank();

    Client *getClient(int id);
    Account *getAccount(int number);

    Client *createClient(int id, string name);
    Account *createAccount(int number, Client *owner);
    Account *createAccount(int number, Client *owner, double interest);
    PartnerAccount *createAccount(int number, Client *owner, Client *partner);
    PartnerAccount *createAccount(int number, Client *owner, Client *partner, double interest);

    void addInterests();
};

#endif