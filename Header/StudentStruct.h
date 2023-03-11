#pragma once
#include <iostream> 
#include <string.h>

using namespace std;

struct Semester {
    string *nameOfCourses;
    float **scroreOfCourses;
};

struct SchoolYear {
    Semester Fall, Summer, Autumn;
};

struct Student {
    string firstName, lastName;
    string studentID;
    string socialID;
    string DOB;// date of birth
    int Gender;// 0 1 2 : Male Female Other
    string Class;
    SchoolYear *listOfSchoolYears;
};