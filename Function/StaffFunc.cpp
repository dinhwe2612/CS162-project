#include <iostream>
#include "fstream"
#include "string.h"
#include "../Header/StudentStruct.h"

#include "../Header/StaffFunc.h"

using namespace std;


void Creat_A_Semester()
{
    ifstream in; ofstream out;
    string schoolyear;
    cout << "Select School-year for the semester in term of yyyy: ";
    getline(cin, schoolyear);
    cout<<'\n';
    cout << "Select the Spring, Summer or Autumn Semester by typing in 1, 2 or 3 respectively: ";
    int a; cin >> a;
    string semester;
    if (a == 1) semester = "Spring";
    else if (a == 2) semester = "Summer";
    else if (a == 3) semester = "Autumn";
    // \Users\HP\OneDrive\Documents\GitHub
    // "\"
    string address = "../Data/SchoolYear/" + schoolyear + "/" + semester;
    if(mkdir(address.c_str()) == -1)
        cerr << " Error : " << strerror(errno) << '\n';
    else
        cout << "Semester Created!"<<'\n';
    string date;
    cout << "Select the date the semester starts in term of ddmmyy: ";
    cin >> date;
    //out.open() append mode open file in which folder
    cout<<'\n';
    cout << "Select the date the semester ends in term of ddmmyy: ";
    cin >> date;
    cout<<'\n';
    //out.open() append mode open file in which folder
    // data in text file, create folder, modify text file of students
    // create semester* semester = new Semester.
    // then all students' pointer semester point to this one.
    // struct Semester consists function inside: add course and course information (enum)
    // view list of courses
    // update course information
    // add or remove student
    // file text inside folder semester info.
    // struct Staff
    // add students to course data abstraction or, out file cpp, write file and compile file cpp "add student" in some folder specific.
    // add student remove students, 
    // type in semester id, course id to 2122unlock these feature
    // give options for guest.
}
//int main() {
     
 //   Creat_A_Semester();
 //    return 0;
 //}
