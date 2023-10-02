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
    Client *partner;
    static int objectsCount;

public:
    Account(int number, Client *owner);
    Account(int number, Client *owner, double interest);
    Account(int number, Client *owner, Client *partner);
    Account(int number, Client *owner, Client *partner, double interest);

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

#endif