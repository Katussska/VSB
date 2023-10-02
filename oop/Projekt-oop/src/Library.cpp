#include "headers/Library.h"

int Library::numberOfLibrarians = 0;
int Library::numberOfUsers = 0;
int Library::numberOfRegisteredUsers = 0;

Library::Library(std::string name)
{
    this->name = name;
}

Library::~Library()
{
}

void Library::setName(std::string name)
{
    this->name = name;
}

std::string Library::getName()
{
    return name;
}

int Library::getNumberOfLibrarians()
{
    return numberOfLibrarians;
}

int Library::getNumberOfUsers()
{
    return numberOfUsers;
}

Librarian *Library::hireLibrarian(std::string name, std::string adress, int empId, double salary)
{

    Librarian *newLibrarian = new Librarian(name, adress, empId, salary);
    this->librarians.push_back(newLibrarian);

    numberOfLibrarians++;

    return newLibrarian;
}

void Library::fireLibrarian(std::string name)
{
    for (int i = 0; i < numberOfLibrarians; i++)
    {
        if (name == librarians.at(i)->getName())
        {
            this->librarians.erase((librarians.begin() + i));
            std::cout << "Knihovník " << name << " byl vyhozen." << std::endl;
            numberOfLibrarians--;
            return;
        }
    }
    std::cout << "Knihovník " << name << " nenalezen." << std::endl;
}

void Library::fireLibrarian(int empId)
{
    for (int i = 0; i < numberOfLibrarians; i++)
    {
        if (empId == librarians.at(i)->getEmployeeId())
        {
            this->librarians.erase((librarians.begin() + i));
            std::cout << "Knihovník s číslem " << empId << " byl vyhozen." << std::endl;
            numberOfLibrarians--;
            return;
        }
    }
    std::cout << "Knihovník s číslem " << empId << " nenalezen." << std::endl;
}

void Library::raiseSalaryToLibratians(double amount)
{
    for (int i = 0; i < numberOfLibrarians; i++)
    {
        librarians.at(i)->addMoney(amount);
    }
}

void Library::printLibrarians()
{
    if (numberOfLibrarians == 0)
    {
        std::cout << "Knhovna nemá žádné knihovníky" << std::endl;
        return;
    }

    else
    {
        for (int i = 0; i < numberOfLibrarians; i++)
        {
            std::cout << librarians.at(i)->getEmployeeId() << " " << librarians.at(i)->getName() << std::endl;
        }
    }
}

User *Library::addUser(std::string name, std::string adress)
{
    User *newUser = new User(name, adress);
    this->users.push_back(newUser);

    numberOfUsers++;

    return newUser;
}

void Library::deleteUser(std::string name)
{
    for (int i = 0; i < numberOfUsers; i++)
    {
        if (name == users.at(i)->getName())
        {
            {
                this->users.erase((users.begin() + i));
                std::cout << "Uživatel se jménem " << name << " byl smazán." << std::endl;
                numberOfUsers--;
                return;
            }
        }
        std::cout << "Uživatel se jménem " << name << " nenalezen." << std::endl;
    }
}

void Library::printUsers()
{
    if (numberOfUsers == 0)
    {
        std::cout << "Knhovna nemá žádné uživatele" << std::endl;
        return;
    }

    else
    {
        for (int i = 0; i < numberOfUsers; i++)
        {
            std::cout << users.at(i)->getName() << " " << users.at(i)->getAdress() << std::endl;
        }
    }
}

RegisteredUser *Library::addRegisteredUser(std::string name, std::string adress, int card, int phone, std::string email, std::string password)
{
    RegisteredUser *newRegisteredUser = new RegisteredUser(name, adress, card, phone, email, password);
    this->registeredUsers.push_back(newRegisteredUser);

    numberOfRegisteredUsers++;

    return newRegisteredUser;
}

void Library::deleteRegisteredUser(std::string name)
{
    for (int i = 0; i < numberOfRegisteredUsers; i++)
    {
        if (name == registeredUsers.at(i)->getName())
        {
            {
                this->registeredUsers.erase((registeredUsers.begin() + i));
                std::cout << "Registrovaný uživatel se jménem " << name << " byl vymazán." << std::endl;
                numberOfRegisteredUsers--;
                return;
            }
        }
    }
    std::cout << "Registrovaný uživatel se jménem " << name << " nenalezen." << std::endl;
}

void Library::deleteRegisteredUser(int cardId)
{
    for (int i = 0; i < numberOfRegisteredUsers; i++)
    {
        if (cardId == registeredUsers.at(i)->getCardId())
        {
            this->registeredUsers.erase((registeredUsers.begin() + i));
            std::cout << "Registrovaný uživatel s číslem " << cardId << " byl vymazán." << std::endl;
            numberOfRegisteredUsers--;
            return;
        }
    }
    std::cout << "Registrovaný uživatel s číslem " << cardId << " nenalezen." << std::endl;
}

void Library::printRegisteredUsers()
{
    if (this->numberOfRegisteredUsers == 0)
    {
        std::cout << "Knhovna nemá žádné registrované uživatele" << std::endl;
        return;
    }

    else
    {
        for (int i = 0; i < this->numberOfRegisteredUsers; i++)
        {
            std::cout << registeredUsers.at(i)->getCardId() << " " << registeredUsers.at(i)->getName() << " " << registeredUsers.at(i)->getAdress();
            std::cout << registeredUsers.at(i)->getPhone() << " " << registeredUsers.at(i)->getEmail() << std::endl;
        }
    }
}

void Library::printALLUsers()
{
    std::cout << "Seznam uživatelů: " << std::endl;

    printUsers();

    std::cout << std::endl;
    std::cout << "Seznam registrovaných uživatelů: " << std::endl;

    printRegisteredUsers();
}

void Library::addBook(int id, std::string title, std::string author, std::string publisher, int year_published)
{
    this->books.push_back(new Book(id, title, author, publisher, year_published));
}

void Library::removeBook(int id)
{
    for (long unsigned int i = 0; i < books.size(); i++)
    {
        if (id == books.at(i)->getID())
        {
            this->books.erase((books.begin() + i));
            std::cout << "Kniha s číslem " << id << " byla vymazána." << std::endl;
            return;
        }
        else
        {
            std::cout << "Kniha s číslem " << id << " nenalezena." << std::endl;
            return;
        }
    }
}

void Library::removeBook(std::string title)
{
    for (long unsigned int i = 0; i < books.size(); i++)
    {
        if (title == books.at(i)->getTitle())
        {
            this->books.erase((books.begin() + i));
            std::cout << "Kniha s názvem " << title << " byla vymazána." << std::endl;
            return;
        }
        else
        {
            std::cout << "Kniha s názvem " << title << " nenalezena." << std::endl;
            return;
        }
    }
}

void Library::printAvailableBooks()
{
    for (long unsigned int i = 0; i < books.size(); i++)
    {
        if (books.at(i)->getAvailability() == 1)
        {
            std::cout << books.at(i)->getTitle() << " " << books.at(i)->getAuthor() << std::endl;
        }
    }
}

void Library::printUnavailableBooks()
{
    for (long unsigned int i = 0; i < books.size(); i++)
    {
        if (books.at(i)->getAvailability() == 0)
        {
            std::cout << books.at(i)->getTitle() << " " << books.at(i)->getAuthor() << std::endl;
        }
    }
}

void Library::printBooks()
{
    std::cout << "Seznam knih:" << std::endl;

    for (long unsigned int i = 0; i < books.size(); i++)
    {
        std::cout << books.at(i)->getTitle() << " - " << books.at(i)->getAuthor() << std::endl;
    }
}

void Library::addEBook(int id, std::string title, std::string author, std::string publisher, int year_published, std::string format, std::string size)
{
    this->ebooks.push_back(new EBook(id, title, author, publisher, year_published, format, size));
}

void Library::removeEBook(int id)
{
    for (long unsigned int i = 0; i < ebooks.size(); i++)
    {
        if (id == ebooks.at(i)->getID())
        {
            this->ebooks.erase((ebooks.begin() + i));
            std::cout << "E-Kniha s číslem " << id << " byla vymazána." << std::endl;
            return;
        }
        else
        {
            std::cout << "E-Kniha s číslem " << id << " nenalezena." << std::endl;
            return;
        }
    }
}

void Library::removeEBook(std::string title)
{
    for (long unsigned int i = 0; i < ebooks.size(); i++)
    {
        if (title == ebooks.at(i)->getTitle())
        {
            this->ebooks.erase((ebooks.begin() + i));
            std::cout << "E-Kniha s názvem " << title << " byla vymazána." << std::endl;
            return;
        }
        else
        {
            std::cout << "E-Kniha s názvem " << title << " nenalezena." << std::endl;
            return;
        }
    }
}

void Library::printAvailableEBooks()
{
    for (long unsigned int i = 0; i < ebooks.size(); i++)
    {
        if (ebooks.at(i)->getAvailability() == 1)
        {
            std::cout << ebooks.at(i)->getTitle() << " " << ebooks.at(i)->getAuthor() << std::endl;
        }
    }
}

void Library::printUnavailableEBooks()
{
    for (long unsigned int i = 0; i < ebooks.size(); i++)
    {
        if (ebooks.at(i)->getAvailability() == 0)
        {
            std::cout << ebooks.at(i)->getTitle() << " " << ebooks.at(i)->getAuthor() << std::endl;
        }
    }
}

void Library::printEBooks()
{
    std::cout << "Seznam e-knih:" << std::endl;

    for (int i = 0; i < ebooks.size(); i++)
    {
        std::cout << ebooks.at(i)->getTitle() << " - " << ebooks.at(i)->getAuthor() << std::endl;
    }
}

void Library::addAudioBook(int id, std::string title, std::string author, std::string publisher, int year_published, std::string narrator, std::string duration)
{
    this->audiobooks.push_back(new AudioBook(id, title, author, publisher, year_published, narrator, duration));
}

void Library::removeAudioBook(int id)
{
    for (long unsigned int i = 0; i < audiobooks.size(); i++)
    {
        if (id == audiobooks.at(i)->getID())
        {
            this->audiobooks.erase((audiobooks.begin() + i));
            std::cout << "Audiokniha s číslem " << id << " byla vymazána." << std::endl;
            return;
        }
        else
        {
            std::cout << "Audiokniha s číslem " << id << " nenalezena." << std::endl;
            return;
        }
    }
}

void Library::removeAudioBook(std::string title)
{
    for (long unsigned int i = 0; i < audiobooks.size(); i++)
    {
        if (title == audiobooks.at(i)->getTitle())
        {
            this->audiobooks.erase((audiobooks.begin() + i));
            std::cout << "Audiokniha s názvem " << title << " byla vymazána." << std::endl;
            return;
        }
        else
        {
            std::cout << "Audiokniha s názvem " << title << " nenalezena." << std::endl;
            return;
        }
    }
}

void Library::printAvailableAudioBooks()
{
    for (long unsigned int i = 0; i < audiobooks.size(); i++)
    {
        if (audiobooks.at(i)->getAvailability() == 1)
        {
            std::cout << audiobooks.at(i)->getTitle() << " - " << audiobooks.at(i)->getAuthor() << std::endl;
        }
    }
}

void Library::printUnavailableAudioBooks()
{
    for (long unsigned int i = 0; i < audiobooks.size(); i++)
    {
        if (audiobooks.at(i)->getAvailability() == 0)
        {
            std::cout << audiobooks.at(i)->getTitle() << " - " << audiobooks.at(i)->getAuthor() << std::endl;
        }
    }
}

void Library::printAudioBooks()
{
    std::cout << "Seznam audioknih:" << std::endl;

    for (long unsigned int i = 0; i < audiobooks.size(); i++)
    {
        std::cout << audiobooks.at(i)->getTitle() << "-  " << audiobooks.at(i)->getAuthor() << std::endl;
    }
}

void Library::printALLAvailableBooks()
{
    std::cout << "Seznam dostupných knih:" << std::endl;
    this->printAvailableBooks();

    std::cout << "Seznam dostupných e-knih:" << std::endl;
    this->printAvailableEBooks();

    std::cout << "Seznam dostupných audioknih:" << std::endl;
    this->printAvailableAudioBooks();
}

void Library::printALLUnavailableBooks()
{
    std::cout << std::endl;
    std::cout << "Seznam nedostupných knih:" << std::endl;
    this->printUnavailableBooks();

    std::cout << std::endl;
    std::cout << "Seznam nedostupných e-knih:" << std::endl;
    this->printUnavailableEBooks();

    std::cout << std::endl;
    std::cout << "Seznam nedostupných audioknih:" << std::endl;
    this->printUnavailableAudioBooks();
}

void Library::printALLBooks()
{
    std::cout << std::endl;
    this->printBooks();

    std::cout << std::endl;
    this->printEBooks();

    std::cout << std::endl;
    this->printAudioBooks();
}

void Library::borrowBook(User *user, int id) // přetížené metody, 1. způsob jak zavolat borrowBook (user)
{
    for (long unsigned int i = 0; i < books.size(); i++)
    {
        if (books.at(i)->getID() == id)
        {
            if (books.at(i)->getAvailability() == 0)
            {
                std::cout << "Kniha " << books.at(i)->getTitle() << " nelze vypůjčit." << std::endl;
                return;
            }
            else
                user->borrowBook(books.at(i));
            books.at(i)->setNotAvailable();
        }
    }
}

void Library::borrowBook(RegisteredUser *user, int id) // přetížené metody, 2. způsob jak zavolat borrowBook (registered user)
{
    for (long unsigned int i = 0; i < books.size(); i++)
    {
        if (books.at(i)->getID() == id)
        {
            if (books.at(i)->getAvailability() == 0)
            {
                std::cout << "Kniha nelze vypůjčit." << std::endl;
                return;
            }
            else
                user->borrowBook(books.at(i));
            books.at(i)->setNotAvailable();
        }
    }
}

void Library::returnBook(User *user, int id)
{
    for (long unsigned int i = 0; i < books.size(); i++)
    {
        if (books.at(i)->getID() == id)
        {
            user->returnBook(i);
        }
    }
}

void Library::returnBook(RegisteredUser *user, int id)
{
    for (long unsigned int i = 0; i < books.size(); i++)
    {
        if (books.at(i)->getID() == id)
        {
            user->returnBook(i);
        }
    }
}

void Library::addDVD(int id, std::string title, std::string duration)
{
    this->media.push_back(new DVD(id, title, duration));
}

void Library::addCD(int id, std::string title, int numberOfTracks, std::string duration)
{
    this->media.push_back(new CD(id, title, numberOfTracks, duration));
}