#include <iostream>
#include "fstream"
#include "string.h"
#include "StudentStruct.h"
#include "StaffFunc.h"
using namespace std;


void Creat_A_Semester()
{
    string schoolyear;
    cout << "Select School-year for the semester in term of yyyy: ";
    cin.getline(schoolyear, 4, '\n');
    cout<<'\n';
    cout << "Select the Spring, Summer or Autumn Semester by typing in 1, 2 or 3 respectively: ";
    int a; cin >> a;
    string semester;
    if (a == 1) semester = "Spring";
    else if (a == 2) semester = "Summer";
    else if (a == 3) semester = "Autumn";
    // \Users\HP\OneDrive\Documents\GitHub
    // "\"
    string address = "C:\CS162-project\Data\SchoolYear\" + schoolyear + "\" + semester;
    if(mkdir(address) == -1)
        cerr << " Error : " << strerror(errno) << '\n';
    else
        cout << "Semester Created";
    cout << "Select the date the semester starts: ";
    // create semester* semester = new Semester.
    // then all students' pointer semester point to this one.
    // struct Semester consists function inside: add course and course information (enum)
    // view listcourse
    // update course information
    // add or remove student
    // file text inside folder semester info.
    // struct Staff

}