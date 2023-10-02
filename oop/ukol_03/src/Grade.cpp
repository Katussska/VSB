#include "Grade.h"

using namespace std;

Grade::Grade(int grade, string subject)
{
    this->grade = grade;
    this->subject = move(subject);
}
