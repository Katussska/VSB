#include "Class.h"

using namespace std;

Class::Class(int number, Teacher *teacher)
{
    this->number = number;
    this->teacher = teacher;
}

void Class::addStudent(string name)
{
    this->Students->push_back(Student(name));
}

Student *Class::getStudent(string name)
{
    for (int i = 0; i < Students->size(); i++)
    {
        if (this->Students->at(i).getName() == name)
        {
            return &this->Students->at(i);
        }
    }
}

Teacher *Class::getTeacher()
{
    return this->teacher;
}

void Class::Delete(string name)
{
    for (int i = 0; i < Students->size(); i++)
    {
        if (this->Students->at(i).getName() == name)
        {
            this->Students->erase(this->Students->begin() + i);
        }
    }
}