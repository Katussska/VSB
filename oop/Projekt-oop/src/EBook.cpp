#include "headers/Book.h"

EBook::EBook(int id, std::string title, std::string author, std::string publisher, int year, std::string format, std::string size)
    : Book(id, title, author, publisher, year) // hierarchie (ebook z book a to samé i audiobook)
{
    this->format = format;
    this->size = size;
}

void EBook::setFormat(std::string format)
{
    this->format = format;
}

void EBook::setSize(std::string size)
{
    this->size = size;
}

std::string EBook::getFormat() const
{
    return format;
}

std::string EBook::getSize() const
{
    return size;
}

void EBook::printInfo()
{
    std::cout << "Title: " << this->getTitle() << std::endl;
    std::cout << "Author: " << this->getAuthor() << std::endl;
    std::cout << "Publisher: " << this->getPublisher() << std::endl;
    std::cout << "Year Published: " << this->getYearPublished() << std::endl;
    std::cout << "Format: " << this->getFormat() << std::endl;
    std::cout << "Size: " << this->getSize() << std::endl;
    std::cout << "Availability: " << this->getAvailability() << std::endl;
}
