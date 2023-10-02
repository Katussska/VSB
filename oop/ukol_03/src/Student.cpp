#include "Student.h"

using namespace std;

Student::Student(string name)
{
    this->name = move(name);
}

string Student::getName()
{
    return this->name;
}

void Student::addGrade(int grade, string subject)
{
    this->Grades->push_back(Grade(grade, subject));
}
