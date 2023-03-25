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
    address += "/Semester_Info.txt";
    cout << "Select the date the semester starts in term of ddmmyy: ";
    cin >> date;
    out.open(address.c_str());
    out << schoolyear << '\n';
    out << semester << '\n';
    out << date << '\n';
    //out.open() append mode open file in which folder
    cout<<'\n';
    cout << "Select the date the semester ends in term of ddmmyy: ";
    cin >> date;
    out << date << '\n';
    cout<<'\n';
    out.close();
    //return the address to the below function
    return;
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
void AddCourse(string address)
{
    ifstream in;
    ofstream out;
    string txtaddress = address + "/Semester_Info.txt";
    out.open(txtaddress.c_str(), fstream::app);
    cout << "Please input your course id: ";
    string courseid;
    cin >> courseid;
    cout << '\n';
    out << courseid << '\n';
    out.close();
    string courseaddress = address + "/" + courseid;
    if(mkdir(courseaddress.c_str()) == -1)
        cerr << " Error : " << strerror(errno) << '\n';
    else
        cout << "Course Created!"<<'\n';
    cout << "Now continue to complete the course information!";
    cout << '\n';
    //use data abstraction
    txtaddress = courseaddress + "/Course_Info.txt";
    Course_Information(txtaddress);
    return;
}


void Course_Information(string txtaddress)
{
    ofstream out;
    out.open(txtaddress.c_str());
    string str;
    cout << "What is the course name?" << '\n';
    cin >> str;
    cout << '\n';
    out << str << '\n';
    cout << "What is the class's name, who would attend this course?" << '\n';
    cin >> str;
    cout << '\n';
    out << str << '\n';
    cout << "What is the teacher's name, who's in charge of this course?" << '\n';
    cin >> str;
    cout << '\n';
    out << str << '\n';
    cout << "What is the number of credits for this course?" << '\n';
    cin >> str;
    cout << '\n';
    out << str << '\n';
    cout << "What is the maximum number of students for the course, default is 50?" << '\n';
    cin >> str;
    cout << '\n';
    out << str << '\n';
    cout << "What is the day of the week for this course, typing in MON TUE WED THU FRI SAT?" << '\n';
    // enum?
    cin >> str;
    cout << '\n';
    out << str << '\n';
    cout << "What is the session in the day, typing in S1 (7:30), S2 (9:30), S3 (13:30) or S4 (15:30)?" << '\n';
    cin >> str;
    cout << '\n';
    out << str << '\n';
    out.close();
    return;
}


void View_ListofCourses(string address)
{
    ifstream in;
    string txtaddress = address + "/Semester_Info.txt";
    in.open(txtaddress.c_str());
    int i = 0;
    string str;
    while (in >> str)
    {
        i++;
        if (i > 4)
        {
            ifstream another_in;
            string another_str;
            another_str = address + str + "/Course_Info.txt";
            another_in.open(another_str.c_str());
            another_in >> another_str;
            cout << "Course " << i-4 << " : " << str << " " << another_str << '\n';
            another_in.close();
        }
    }
    in.close();
    return;
}


void Update_CourseInformation(string address)
{}

void AddStudenttoCourse() {}
void RemoveStudentfromCourse() {}
// bout to done.