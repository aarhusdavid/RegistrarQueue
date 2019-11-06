#ifndef STUDENT_H
#define STUDENT_H

#include <iostream>

using namespace std;

class Student
{
    public:
        Student();
        ~Student();

        //variables for student
        int TimeArrived;
        int TimeRequired;
        double WaitTime;

        //method that increments wait
        void incrementWait();

};

#endif
