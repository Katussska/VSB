#include "headers/Book.h"

AudioBook::AudioBook(int id, std::string title, std::string author, std::string publisher, int year, std::string narrator, std::string duration)
    : Book(id, title, author, publisher, year)
{
    this->narrator = narrator;
    this->duration = duration;
}

void AudioBook::setNarrator(std::string narrator)
{
    this->narrator = narrator;
}

void AudioBook::setDuration(std::string duration)
{
    this->duration = duration;
}

std::string AudioBook::getNarrator() const
{
    return this->narrator;
}

std::string AudioBook::getDuration() const
{
    return this->duration;
}

void AudioBook::printInfo()
{
    std::cout << "Title: " << this->getTitle() << std::endl;
    std::cout << "Author: " << this->getAuthor() << std::endl;
    std::cout << "Publisher: " << this->getPublisher() << std::endl;
    std::cout << "Year Published: " << this->getYearPublished() << std::endl;
    std::cout << "Narrator: " << this->getNarrator() << std::endl;
    std::cout << "Duration: " << this->getDuration() << std::endl;
    std::cout << "Availability: " << this->getAvailability() << std::endl;
}