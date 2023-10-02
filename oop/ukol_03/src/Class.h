#include "Student.h"
#include "Teacher.h"

using namespace std;

class Class
{
private:
    int number;
    Teacher *teacher;
    vector<Student> *Students;

public:
    Class(int number, Teacher *teacher);
    void addStudent(string name);
    Student *getStudent(string name);
    Teacher *getTeacher();
    void Delete(string name);
};
