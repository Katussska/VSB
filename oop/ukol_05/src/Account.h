#ifndef ACCOUNT_H
#define ACCOUNT_H

#include "Client.h"

using namespace std;

class Account
{
private:
    int number;
    double balance = 0;
    double interest = 0;
    Client *owner;
    static int objectsCount;

public:
    Account(int number, Client *owner);
    Account(int number, Client *owner, double interest);

    int getNumber();
    int getCount() const;
    double getBalance();
    double getInterest();
    Client *getOwner();
    Client *getPartner();

    void setBalance(double money);

    void deposide(double amount);
    void withdraw(double amount);
    void addInterest();
};

class PartnerAccount : public Account
{
private:
    Client *partner;

public:
    PartnerAccount(int number, Client *owner, Client *partner);
    PartnerAccount(int number, Client *owner, Client *partner, double interest);

    Client *getPartner();
};

#endif