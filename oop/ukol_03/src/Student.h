#include "Grade.h"
#include <vector>

using namespace std;

class Student
{
private:
    string name;
    vector<Grade> *Grades;

public:
    Student(string name);
    string getName();
    void addGrade(int grade, string subject);
};
