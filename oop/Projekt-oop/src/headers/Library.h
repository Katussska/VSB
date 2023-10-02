#include "User.h"
#include "Media.h"

class Library
{
private:
    std::string name;
    std::vector<Librarian *> librarians;
    static int numberOfLibrarians;
    std::vector<User *> users;
    static int numberOfUsers;
    std::vector<RegisteredUser *> registeredUsers;
    static int numberOfRegisteredUsers;
    std::vector<Book *> books;
    std::vector<EBook *> ebooks;
    std::vector<AudioBook *> audiobooks;
    std::vector<Media *> media;

public:
    Library(std::string name);
    ~Library();

    void setName(std::string name);
    std::string getName();

    int getNumberOfLibrarians();
    int getNumberOfUsers();

    Librarian *hireLibrarian(std::string name, std::string adress, int empId, double salary);
    void fireLibrarian(std::string name);
    void fireLibrarian(int empId);
    void raiseSalaryToLibratians(double amount);
    void printLibrarians();

    User *addUser(std::string name, std::string adress);
    void deleteUser(std::string name);
    void printUsers();

    RegisteredUser *addRegisteredUser(std::string name, std::string adress, int card, int phone, std::string email, std::string password);
    void deleteRegisteredUser(std::string name);
    void deleteRegisteredUser(int cardId);
    void printRegisteredUsers();

    void printALLUsers();

    void addBook(int id, std::string title, std::string author, std::string publisher, int year_published);
    void removeBook(int id);
    void removeBook(std::string title);
    void printAvailableBooks();
    void printUnavailableBooks();
    void printBooks();

    void addEBook(int id, std::string title, std::string author, std::string publisher, int year_published, std::string format, std::string size);
    void removeEBook(int id);
    void removeEBook(std::string title);
    void printAvailableEBooks();
    void printUnavailableEBooks();
    void printEBooks();

    void addAudioBook(int id, std::string title, std::string author, std::string publisher, int year_published, std::string narrator, std::string duration);
    void removeAudioBook(int id);
    void removeAudioBook(std::string title);
    void printAvailableAudioBooks();
    void printUnavailableAudioBooks();
    void printAudioBooks();

    void printALLAvailableBooks();
    void printALLUnavailableBooks();
    void printALLBooks();

    void addDVD(int id, std::string title, std::string duration);
    void addCD(int id, std::string title, int numberOfTracks, std::string duration);

    void borrowBook(User *user, int id);
    void borrowBook(RegisteredUser *user, int id);
    void returnBook(User *user, int id);
    void returnBook(RegisteredUser *user, int id);
};
