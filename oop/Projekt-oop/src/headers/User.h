#include "Book.h"

class User
{
private:
    std::string name;
    std::string adress;
    std::vector<Book *> borrowedBooks;
    static int objectCount;

public:
    User(std::string name, std::string adress);
    ~User();

    void setName(std::string name);
    void setAdress(std::string adress);

    std::string getName();
    std::string getAdress();

    void borrowBook(Book *book);
    void returnBook(int id);
    void printBorrowedBooks();
    void printSomething()
    { // změna chování
        std::cout << "This is a user." << std::endl;
    }
};

class RegisteredUser : public User
{
private:
    int cardId;
    int phone;
    std::string email;
    std::string password;

public:
    RegisteredUser(std::string name, std::string adress, int card, int phone, std::string email, std::string password);
    ~RegisteredUser();

    void setCardId(int id);
    void setPhone(int number);
    void setEmail(std::string email);

    int getCardId();
    int getPhone();
    std::string getEmail();
    std::string getPassword();

    void changePassword(std::string password, std::string newPassword);
    void printSomething()
    { // změna chování
        std::cout << "This is a registered user." << std::endl;
    }
};

class Librarian : public User
{
private:
    int employeeId;
    double salary;

public:
    Librarian(std::string name, std::string adress, int empId, double salary);
    ~Librarian();

    void setEmployeeId(int id);
    void setSalary(double salary);

    int getEmployeeId();
    double getSalary();

    void addMoney(double amount);
    void printSomething()
    { // změna chování
        std::cout << "This is a librarian." << std::endl;
    }
};
