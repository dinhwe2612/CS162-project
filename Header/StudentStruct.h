#pragma once
#include <iostream> 
#include <string.h>
#include<direct.h>
// IF YOU WANT TO UPDATE ONE SPECIFIC FILE, 2 FUNCTIONS IN StaffFunc.h  MAY HELP.
// FOR SPECIFIC, THEY TAKE IN THE INFORMATION AS A BLOCK OF STRING THAT
// YOU'RE ABLE TO UPDATE, AND THEN OVERWRITE THE OLD FILE WITH NEW INFORMATION.

using namespace std;

struct Semester {
    string *nameOfCourses;
    float **scroreOfCourses;
    // course id consists of characters?
    string* start_date;
    string* end_date;
};

struct SchoolYear {
    Semester Spring, Summer, Autumn;
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

//why not struct Course?