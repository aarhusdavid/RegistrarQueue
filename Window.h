#ifndef WINDOW_H
#define WINDOW_H

#include "Student.h"
#include <iostream>

using namespace std;

class Window
{
    public:
        Window();
        ~Window();

        //variables for windows
        double idleTime;
        int TimeLeft;
        Student *helped;
        bool occupied;
};

#endif
