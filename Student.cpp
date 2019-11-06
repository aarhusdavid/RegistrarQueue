#include "Student.h"
#include <iostream>

using namespace std;

Student::Student()
{
    TimeArrived = 0;
    TimeRequired = 0;
    WaitTime = 0.0;

}

Student::~Student()
{
    //destructor
}

void Student::incrementWait()
{
    ++WaitTime;
}
