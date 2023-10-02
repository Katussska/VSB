#include "Bank.h"

using namespace std;

Bank::Bank(int clientsMax, int accountsMax)
{
    this->clientsMax = move(clientsMax);
    this->accountsMax = move(accountsMax);
}

Bank::~Bank()
{
    /*for (int i = 0; i < clientsCount; i++)
    {
        delete this->Clients[i];
    }

    this->clientsCount = 0;

    for (int i = 0; i < accountsCount; i++)
    {
        delete this->Accounts[i];
    }

    this->accountsCount = 0;*/

    delete this;
}

Client *Bank::getClient(int id)
{
    for (int i = 0; i < this->Clients[0]->getCount(); i++)
    {
        if (this->Clients[i]->getId() == id)
        {
            return this->Clients[i];
        }
    }
    cout << "No such client found." << endl;

    return 0;
}

Account *Bank::getAccount(int number)
{
    for (int i = 0; i < this->Accounts[0]->getCount(); i++)
    {
        if (this->Accounts[i]->getNumber() == number)
        {
            return this->Accounts[i];
        }
    }
    cout << "No such account found." << endl;

    return 0;
}

Client *Bank::createClient(int id, string name)
{
    if (this->Clients[0]->getCount() < this->clientsMax)
    {
        Client *newClient = new Client(id, name);

        this->Clients = new Client *[clientsMax];

        return newClient;
    }
    cout << "The maximum of clients has been reached." << endl;

    return 0;
}

Account *Bank::createAccount(int number, Client *owner)
{
    if (this->Accounts[0]->getCount() < accountsMax)
    {
        Account *newAccount = new Account(number, owner);

        this->Accounts = new Account *[accountsMax];

        return newAccount;
    }
    cout << "The maximum of accounts has been reached." << endl;

    return 0;
}

Account *Bank::createAccount(int number, Client *owner, double interest)
{
    if (this->Accounts[0]->getCount() < accountsMax)
    {
        Account *newAccount = new Account(number, owner, interest);

        this->Accounts = new Account *[accountsMax];

        return newAccount;
    }
    cout << "The maximum of accounts has been reached." << endl;

    return 0;
}

PartnerAccount *Bank::createAccount(int number, Client *owner, Client *partner)
{
    if (this->Accounts[0]->getCount() < accountsMax)
    {
        PartnerAccount *newAccount = new PartnerAccount(number, owner, partner);

        this->PartnerAccounts = new PartnerAccount *[accountsMax];

        return newAccount;
    }

    cout << "The maximum of accounts has been reached." << endl;

    return 0;
}

PartnerAccount *Bank::createAccount(int number, Client *owner, Client *partner, double interest)
{
    if (this->Accounts[0]->getCount() < accountsMax)
    {
        PartnerAccount *newAccount = new PartnerAccount(number, owner, partner, interest);

        this->PartnerAccounts = new PartnerAccount *[accountsMax];

        return newAccount;
    }
    cout << "The maximum of accounts has been reached." << endl;

    return 0;
}

void Bank::addInterests()
{
    for (int i = 0; i < this->Accounts[0]->getCount(); i++)
    {
        this->Accounts[i]->addInterest();
    }
}
