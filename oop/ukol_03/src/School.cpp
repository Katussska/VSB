#include "School.h"

using namespace std;

School::School(string name)
{
    this->name = move(name);
}

Class *School::createClass(int id, Teacher *teacher)
{
    Class *newClass = new Class(id, teacher);
    this->Classes = new Class *[classesCount];
    this->classesCount++;

    return newClass;
}

Teacher *School::createTeacher(string name, int salary)
{
    Teacher *newTeacher = new Teacher(name, salary);
    this->Teachers = new Teacher *[teachersCount];
    this->teachersCount++;

    return newTeacher;
}

Student *School::createStudent(string name)
{
    Student *newStudent = new Student(name);
    this->Students = new Student *[studentsCount];
    this->studentsCount++;

    return newStudent;
}

Teacher *School::getTeacher(int number)
{
    for (int i = 0; i < classesCount; i++)
    {
        return this->Classes[i]->getTeacher();
    }
    cout << "No such class found." << endl;

    return 0;
}
