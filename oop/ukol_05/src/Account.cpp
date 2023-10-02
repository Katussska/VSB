#include "Account.h"

using namespace std;

int Account::objectsCount = 0;

Account::Account(int number, Client *owner)
{
    this->number = number;
    this->owner = owner;
}

Account::Account(int number, Client *owner, double interest)
{
    this->number = number;
    this->owner = owner;
    this->interest = interest;
}

PartnerAccount::PartnerAccount(int number, Client *owner, Client *partner) : Account(number, owner)
{
    this->partner = partner;
}

PartnerAccount::PartnerAccount(int number, Client *owner, Client *partner, double interest) : Account(number, owner, interest)
{
    this->partner = partner;
}

int Account::getNumber()
{
    return this->number;
}

int Account::getCount() const
{
    return this->objectsCount;
}

double Account::getBalance()
{
    return this->balance;
}

double Account::getInterest()
{
    return this->interest;
}

Client *Account::getOwner()
{
    return this->owner;
}

Client *PartnerAccount::getPartner()
{
    return this->partner;
}

void Account::setBalance(double money)
{
    this->balance = move(money);
}

void Account::deposide(double amount)
{
    this->balance += amount;
}

void Account::withdraw(double amount)
{
    if (amount <= this->balance)
    {
        this->balance -= amount;

        cout << "Withdraw succesful. Your new balance is: " << this->getBalance() << endl;
        return;
    }
    cout << "Not enough money. Your balance is: " << this->getBalance() << endl;
}

void Account::addInterest()
{
    this->balance += (balance * interest);
}