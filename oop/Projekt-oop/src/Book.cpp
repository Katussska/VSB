#include "headers/Book.h"

Book::Book(int id, std::string title, std::string author, std::string publisher, int year_published)
{
    this->id = id;
    this->year_published = year_published;
    this->title = title;
    this->author = author;
    this->publisher = publisher;
    this->available = true;
}

void Book::setID(int id)
{
    this->id = id;
}

void Book::setTitle(std::string title)
{
    this->title = title;
}

void Book::setAuthor(std::string author)
{
    this->author = author;
}

void Book::setPublisher(std::string publisher)
{
    this->publisher = publisher;
}

void Book::setYearPublished(int year)
{
    this->year_published = year;
}

void Book::setAvailable()
{
    this->available = true;
}

void Book::setNotAvailable()
{
    this->available = false;
}

int Book::getID()
{
    return this->id;
}

std::string Book::getTitle()
{
    return this->title;
}

std::string Book::getAuthor()
{
    return this->author;
}

std::string Book::getPublisher()
{
    return this->publisher;
}

int Book::getYearPublished()
{
    return this->year_published;
}

bool Book::getAvailability()
{
    if (this->available == 1)
    {
        return true;
    }
    else
    {
        return false;
    }
}

void Book::printInfo()
{
    std::cout << "Title: " << this->getTitle() << std::endl;
    std::cout << "Author: " << this->getAuthor() << std::endl;
    std::cout << "Publisher: " << this->getPublisher() << std::endl;
    std::cout << "Year Published: " << this->getYearPublished() << std::endl;
}