#include "headers/User.h"

RegisteredUser::RegisteredUser(std::string name, std::string adress, int card, int phone, std::string email, std::string password)
    : User(name, adress)
{
    this->cardId = card;
    this->phone = phone;
    this->email = email;
    this->password = password;
}

RegisteredUser::~RegisteredUser()
{
}

void RegisteredUser::setCardId(int id)
{
    this->cardId = id;
}

void RegisteredUser::setPhone(int number)
{
    this->phone = number;
}

void RegisteredUser::setEmail(std::string email)
{
    this->email = email;
}

int RegisteredUser::getCardId()
{
    return cardId;
}

int RegisteredUser::getPhone()
{
    return phone;
}

std::string RegisteredUser::getEmail()
{
    return email;
}

std::string RegisteredUser::getPassword()
{
    return password;
}

void RegisteredUser::changePassword(std::string password, std::string newPassword)
{
    if (this->getPassword() == password)
    {
        this->password = newPassword;
    }
    else
    {
        std::cout << "Password does not match. Try it again." << std::endl;
    }
}