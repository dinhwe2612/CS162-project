#include <iostream>
#include <fstream>
#include <string.h>
#include "../Header/StudentStruct.h"

#include "../Header/StaffFunc.h"

using namespace std;
void MultiChoices()
{
    // menu
    return;
}


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
    cin.ignore();
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
    cin.ignore();
    cout << "What is the class's name, who would attend this course?" << '\n';
    cin >> str;
    cout << '\n';
    out << str << '\n';
    cin.ignore();
    cout << "What is the teacher's name, who's in charge of this course?" << '\n';
    cin >> str;
    cout << '\n';
    out << str << '\n';
    cin.ignore();
    cout << "What is the number of credits for this course?" << '\n';
    cin >> str;
    cout << '\n';
    out << str << '\n';
    cin.ignore();
    cout << "What is the maximum number of students for the course, default is 50?" << '\n';
    cin >> str;
    cout << '\n';
    out << str << '\n';
    cin.ignore();
    cout << "What is the day of the week for this course, typing in MON TUE WED THU FRI SAT?" << '\n';
    // enum?
    cin >> str;
    cout << '\n';
    out << str << '\n';
    cin.ignore();
    cout << "What is the session in the day, typing in S1 (7:30), S2 (9:30), S3 (13:30) or S4 (15:30)?" << '\n';
    cin >> str;
    cout << '\n';
    out << str << '\n';
    cin.ignore();
    out.close();
    cout << "The data has been recorded!" << '\n';
    return;
}


void View_ListofCourses(string address)
{
    ifstream in;
    string txtaddress = address + "/Semester_Info.txt";
    in.open(txtaddress.c_str());
    //cout << (in.is_open() ? "MEOMEOMEO" : "NOPE");
    int i = 0;
    string str;
    while (in >> str)
    {
        i++;
        if (i > 4)
        {
            ifstream another_in;
            string another_str;
            string coursename;
            another_str = address + "/" + str + "/Course_Info.txt";
            another_in.open(another_str.c_str()); 
            another_in >> coursename; 
            cout << "Course " << i-4 << " : " << str << " " << coursename << '\n';
            another_in.close();
        }
    }
    in.close();
    return;
}

string* Read_File(string fileaddress)
{
    ifstream in;
    string* inf = new string[1000];
    in.open(fileaddress.c_str());
    string str;
    int i = 1;
    while (in >> str)
    {
        inf[i] = str;
        i++;
    }
    inf[0] = to_string(i-1); 
    in.close();
    return inf; 
}

void Update_File(string fileaddress, string* information)
{
    int i = 1;
    ofstream out;
    out.open(fileaddress.c_str());
    while (i <= atoi(information[0].c_str()))
    {
        out << information[i] << '\n';
        i++;
    }
    out.close();
    return;
}
void Update_CourseInformation(string address)
{
    View_ListofCourses(address);
    cout << "Here are the courses, please type the course id of the course you want to update: ";
    string course;
    cin >> course;
    cout << '\n';
    address = address + "/" + course + "/Course_Info.txt";
    string* inf;
    inf = Read_File(address);
    cout << "Which piece of information do you want to modify?" << '\n';
    cout << "1. Course Name" << '\n';
    cout << "2. Class Name" << '\n';
    cout << "3. Teacher Name" << '\n';
    cout << "4. Credits" << '\n';
    cout << "5. The max number of students" << '\n';
    cout << "6. The day of week" << '\n';
    cout << "7. The session for the day" << '\n';
    int choice;
    cout << "Please choose one by typing in the number from 1 to 7: ";
    cin >> choice;
    cout << '\n';
    string newinf;
    cout << "Now typing in the new information: ";
    cin >> newinf;
    cout << "Thank you, the information has been updated for you!" << '\n';
    inf[choice] = newinf;
    Update_File(address, inf);
    return;
}
//

void AddClasstoCourse_CSV(string fileaddress, string courseaddress)
{
    string* info;
    info = Read_File(fileaddress.c_str());
    string newfileaddress = courseaddress + "/Student_ID.csv";
    Update_File(newfileaddress, info);
    return;
}

void Add1StudenttoCourse(string studentid, string courseaddress) 
{
    string address = courseaddress + "/Student_ID.csv";
    ofstream out;
    out.open(address.c_str(), ios::app);
    out << studentid << '\n';
    out.close();
    cout << "This student with the ID has been added to the current course!" <<'\n';
    return;
}
void Remove1StudentfromCourse(string studentid, string courseaddress) 
{
    string address = courseaddress + "/Student_ID.csv";
    string* info;
    info = Read_File(address.c_str());
    int i = 1;
    ofstream out;
    out.open(address.c_str());
    while (i <= atoi(info[0].c_str()))
    {
        if (studentid != info[i])  out << info[i] << '\n';
        i++;
    }
    out.close();
    cout << "This student with the ID has been removed from the current course!" <<'\n';
    return;
}
// bout to done.
// update more information at one time.

//int main() {
//    Update_CourseInformation("../Data/SchoolYear/2122/Spring");
//    return 0;
//}