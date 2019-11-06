#include <iostream>
#include <fstream>
#include "RegQueue.h"
#include "Student.h"
#include "Window.h"

//why are my TimeArrived var and TimeRequired var not printing out for each student
//how do I increment wait for each student in student

using namespace std;

int main(int argc, char** argv)
{
    // stores command line argument; acts as scanner class from java
    string file_name = argv[1];

    string strand;
    ifstream infile;
    infile.open(file_name);
    getline(infile, strand);
    int numWindows = stoi(strand); //number of windows open
    int time = 0; //var for time student arrived
    double totaltime; //var for total tick time for simulation
    double numStudents; //var for num of students per time tick
    double numStudents_over10 = 0; //var for students who total wait time is over 10 minutes
    double totalstudswait = 0; //var for total time used by students waiting for windows
    int workingWindows = 0; //var for working windows
    bool loop = true; // var simulation loop
    int clock = 0; //var for tick
    Window *dow; //window pointer
    Student *stud; //student pointer
    Student *Tstudent; //student object
    Student *NextStudent; //student object
    Student *nextPointer; //student pointer
    int windowSlot; // var for available window
    bool emptyWindows = false;
    bool isFull = false;

    //queue for student line and queue to hold students who are finished
    RegQueue<Student*> *studentLine = new RegQueue<Student*>; //queue for student line
    RegQueue<Student*> *completedLine = new RegQueue<Student*>; //queue for students leave line
    Window* openWindows[numWindows];
    for(int i = 0; i < numWindows; ++i)
    {
        openWindows[i] = new Window();
    }

    while(infile.peek() != EOF) //iterates through file line by line
    {
        getline(infile, strand); //gets tick time
        time = stoi(strand);
        getline(infile, strand); //gets number of students
        numStudents = stoi(strand);

        for(int i = 0; i < numStudents; ++i)
        {
            Student *st = new Student(); //creates student object
            st->TimeArrived = time; //stores their time arrived
            getline(infile, strand);
            st->TimeRequired = stoi(strand); //store their required time
            studentLine->insert(st); //insert student into the line
            // cout << studentLine->peek().TimeArrived;
        }
    }

    while(loop == true) //loop for the simulation
    {
        for(int i = 0; i < numWindows; i++) //forloop that checks to see if windows are occupied
        {
            if(openWindows[i]->occupied == true)
            {
                emptyWindows = false;
                break;
            }
            else
            {
                emptyWindows = true;
            }
        }

        if((emptyWindows == true) && (studentLine->isEmpty())) //if windows are empty and TimeRequired is empty loop ends
        {
            loop = false;
        }

        if(!studentLine->isEmpty()) //if student line is not empty
        {
            Tstudent = studentLine->peek(); //grabs memory address of the student at the front of the line
            stud = Tstudent;

            if(stud->TimeArrived == clock) //if
            {
                completedLine->insert(studentLine->remove()); //takes student out of line and puts them in completed line
                for(int p = 0; p < numWindows; p++) //iterates through windows to see what is open
                {
                    if(openWindows[p]->occupied == false)
                    {
                        windowSlot = p; //declares var for window that is open
                        break;
                    }
                }

                dow = openWindows[windowSlot]; //var for that window
                dow->helped = stud; //this window has this student
                dow->TimeLeft = stud->TimeRequired; //pointer to this windows timeleft and makes it the students time required
                dow->occupied = true; //pointer to this windows occupied bool value, makes it true

                ++workingWindows; //increments total working windows
            }
        }

        if(!studentLine->isEmpty()) //if studentline is not empty
        {
            NextStudent = studentLine->peek(); //grabs student from top of student line
            nextPointer = NextStudent; //dereferences that student
            if(nextPointer->TimeArrived != clock) //if the students time Arrived is not equal to the total clock
            {
                ++clock; //increment clock
                for(int j = 0; j < numWindows; j++) //iterates through windows
                {
                    if(openWindows[j]->occupied && (openWindows[j]->TimeLeft != 0)) //if window is occupied and this window still has timeleft
                    {
                        openWindows[j]->TimeLeft--; //decrements timeleft
                    }
                    else if(openWindows[j]->occupied && (openWindows[j]->TimeLeft == 0)) //if window is occupied and this window still has no timeleft
                    {
                        openWindows[j]->occupied = false;
                    }
                    else if(openWindows[j]->occupied == false)
                    {
                        openWindows[j]->idleTime++;
                    }
                }
            }
        }
        else
        {
            clock++;
            for(int j = 0; j < numWindows; j++)
            {
                if(openWindows[j]->occupied && (openWindows[j]->TimeLeft != 0)) //if window is occupied and this window still has timeleft
                {
                    openWindows[j]->TimeLeft--; //decrements timeleft
                }
                else if(openWindows[j]->occupied && (openWindows[j]->TimeLeft == 0)) //if window is occupied and this window still has no timeleft
                {
                    openWindows[j]->occupied = false;
                }
                else if(openWindows[j]->occupied == false)
                {
                    openWindows[j]->idleTime++; //increments timeleft
                }
            }
        }

    }

        //variables for stats
        double mean_window_idle_time = 0.0;
        double mean_window_total_idle_time = 0.0;
        int longest_idle_time = 0;
        int temp_idle_time = 0;
        int num_idle_over_5min = 0;

        //calculates window stats
        for(int i = 0; i < numWindows; ++i)
        {
            if(i == 0)
                longest_idle_time = openWindows[i]->idleTime;
            temp_idle_time = openWindows[i]->idleTime;
            if(temp_idle_time >= longest_idle_time)
                longest_idle_time = temp_idle_time;
            if(openWindows[i]->idleTime > 5)
                num_idle_over_5min++;
            mean_window_total_idle_time = mean_window_total_idle_time += openWindows[i]->idleTime;
        }
        mean_window_idle_time = mean_window_total_idle_time / numWindows;

        // if(completedLine->isFull())
        // {
        //     cout << endl;
        //     cout << "Student at front -> Wait Time: " << completedLine->peek()->WaitTime << endl;
        //     cout << "Student at front -> Time Arrived: " << completedLine->peek()->TimeArrived << endl;
        //     cout << "Student at front -> Time Required: " << completedLine->peek()->TimeRequired << endl;
        //     cout << endl;
        // }
        // else
        // {
        //     cout << "No students in completed line" << endl;
        // }
        //
        //
        //

    //closes file
    infile.close();

    //prints out stats to standard out
    cout << endl;
    cout << "Metrics" << endl;
    cout << "1. The mean student wait time:   " << endl;
    cout << "2. The median student wait time:   " << endl;
    cout << "3. The longest student wait time:   " << endl;
    cout << "4. The number of students waiting over 10 minutes:   " << endl;
    cout << "5. The mean window idle time:   " << mean_window_idle_time << " minutes" << endl;
    cout << "6. The longest window idle time:    " << longest_idle_time << " minutes" << endl;
    cout << "7. Number of windows idle for over 5 minutes:   " << num_idle_over_5min << " windows" << endl;
    cout << endl;



    return 0;
}
