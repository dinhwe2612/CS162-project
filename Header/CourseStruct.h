#ifndef CourseStruct_h
#define CourseStruct_h

#include <string>

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