#include "Class.h"

using namespace std;

class School
{
private:
    string name;
    Class **Classes;
    int classesCount;
    Teacher **Teachers;
    int teachersCount;
    Student **Students;
    int studentsCount;

public:
    School(string name);
    Class *createClass(int id, Teacher *teacher);
    Teacher *createTeacher(string name, int salary);
    Student *createStudent(string name);

    Teacher *getTeacher(int number);
};
