#include "headers/User.h"

int User::objectCount = 0;

User::User(std::string name, std::string adress)
{
    this->name = name;
    this->adress = adress;
    User::objectCount += 1;
}

User::~User()
{
}

void User::setName(std::string name)
{
    this->name = name;
}

void User::setAdress(std::string adress)
{
    this->adress = adress;
}

std::string User::getName()
{
    return name;
}

std::string User::getAdress()
{
    return adress;
}

void User::borrowBook(Book *book)
{
    this->borrowedBooks.push_back(book);
}

void User::returnBook(int id)
{
    this->borrowedBooks.erase((borrowedBooks.begin() + id));
}

void User::printBorrowedBooks()
{
    std::cout << "Seznam vypůjčených knih:" << std::endl;

    for (long unsigned int i = 0; i < borrowedBooks.size(); i++)
    {
        std::cout << borrowedBooks.at(i)->getTitle() << " " << borrowedBooks.at(i)->getAuthor() << std::endl;
    }
}