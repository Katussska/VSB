#include <string>
#include <iostream>
#include <vector>

class Book
{
private:
    int id;
    std::string title;
    std::string author;
    std::string publisher;
    int year_published;
    bool available;

public:
    Book(int id, std::string title, std::string author, std::string publisher, int year_published);

    void setID(int id);
    void setTitle(std::string title);
    void setAuthor(std::string author);
    void setPublisher(std::string publisher);
    void setYearPublished(int year);
    void setAvailable();
    void setNotAvailable();

    int getID();
    std::string getTitle();
    std::string getAuthor();
    std::string getPublisher();
    int getYearPublished();
    bool getAvailability();

    virtual void printInfo();
};

class EBook : public Book
{
private:
    std::string format;
    std::string size;

public:
    EBook(int id, std::string title, std::string author, std::string publisher, int year, std::string format, std::string size);

    void setFormat(std::string format);
    void setSize(std::string size);

    std::string getFormat() const;
    std::string getSize() const;

    void printInfo() override;
};

class AudioBook : public Book
{
protected:
    std::string narrator;
    std::string duration;

public:
    AudioBook(int id, std::string title, std::string author, std::string publisher, int year, std::string narrator, std::string duration);

    void setNarrator(std::string narrator);
    void setDuration(std::string duration);

    std::string getNarrator() const;
    std::string getDuration() const;

    void printInfo() override;
};
