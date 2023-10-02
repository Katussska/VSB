#include "Bank.h"
#include "Car.h"

using namespace std;

int main()
{
    Bank *mBank = new Bank(2, 10);
    Client *client_1 = mBank->createClient(128, "Honza Zahradníček");
    Client *client_2 = mBank->createClient(745, "Petr Okénko");

    Account *account_1 = mBank->createAccount(429, client_1, client_2, 0.5);

    cout << client_1->getName() << endl;
    cout << client_1->getId() << endl;

    account_1->setBalance(900.001);
    cout << account_1->getBalance() << endl;

    account_1->deposide(100);
    cout << account_1->getBalance() << endl;

    account_1->addInterest();
    cout << account_1->getBalance() << endl;

    account_1->withdraw(2000);
    account_1->withdraw(100);

    // check for max clients
    Client *client_3 = mBank->createClient(45, "Petr Sedačka");

    Account *account_2 = mBank->createAccount(11, client_2, 0.5);

    account_2->setBalance(100);
    account_1->setBalance(100);

    cout << "account_1: " << account_1->getBalance() << endl;
    cout << "account_2: " << account_2->getBalance() << endl;

    Account *a = mBank->createAccount(357, client_1);
    PartnerAccount *pa = mBank->createAccount(941, client_1, client_2);

    PrivateCar osobak("Skoda", "Fabia", 2014, "cerna", 5, 5);
    osobak.maxSpeed(180);
    osobak.numberOfSeats();

    Truck nakladak("Nevim", "Netusim", 2008, "bila", 70000);
    nakladak.maxSpeed(90);

    cout << a->getOwner()->getName() << endl;

    return 0;
}
