#ifndef CourseStruct_h
#define CourseStruct_h

#include <string>
using namespace std;

struct ACourse {
    string id;
    string name;
    string Class;
    string teacher;
    int credit;
    int maxStudent = 50;
    string dayOfWeek;
    string session;
};

#endif