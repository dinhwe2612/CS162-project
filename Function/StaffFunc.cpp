#include <iostream>
#include <fstream>
#include <string.h>
#include "../Header/StudentStruct.h"

#include "../Header/StaffFunc.h"

// THE MULTICHOICES FUNCTION, WHICH IS THE MENU, IS APPLIED NOT ONLY FOR FUNCTIONS IN THIS FILE

using namespace std;
void MultiChoices()
{
    // add info to the students also.
    // add course info to student information
    // function record and push info to the struct to print out/ student.
    // Students' file text. class in course, add file student enrolled, add one specific students.
    // must change students' information.
    // the order of information.
    // menu
    // menu 
    
    return;
}


void Creat_A_Semester()
{
    ifstream in; ofstream out;
    string schoolyear;
    cout << "Select School-year for the semester in term of yyyy-yyyy: ";
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
    cout << "The semester has been created!" << '\n';
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
    getline(cin, courseid);
    cout << '\n';
    // struct stat sb;
    // // Calls the function with path as argument
    // // If the file/directory exists at the path returns 0
    // // If block executes if path exists
    // if (stat(folder, &sb) == 0)
    //     cout << "The path is valid!";
    // else
    //     cout << "The Path is invalid!";
    //if (is_file_exist(courseaddress) != true)  
    //{
    string coursename;
    cout << "What is the course name?" << '\n';
    getline(cin, coursename);
    cout << '\n';
    //cin.ignore();
    // out << courseid << '\n';
    // out.close();
    // out << str << '\n';
    //cin.ignore();
    string classname;
    cout << "What is the class's name, who would attend this course?" << '\n';
    getline(cin, classname);
    cout << '\n';
    //cin.ignore();
    string courseaddress = address + "/" + courseid + "-" + classname;
        if(mkdir(courseaddress.c_str()) == -1)
        cerr << " Error : " << strerror(errno) << '\n';
    else
        cout << "Course Created!"<<'\n';
    //}
    out << courseid << "-" << classname << '\n';
    out.close();
    cout << "Now continue to complete the course information!";
    cout << '\n';
    //cin.ignore();
    //use data abstraction
    txtaddress = courseaddress + "/Course_Info.txt";
    out.open(txtaddress.c_str());
    
    //out << str << '\n';Helu/////alu alu alu alu alu
    
    out << courseid << "-" << classname << '\n';
    out << coursename << '\n';
    out << classname << '\n';
    out.close();
    Course_Information(txtaddress);
    
    return;
}

// bool is_file_exist( std::string& FileName ) {
	
// 	const std::filesystem::path p = FileName ;
//     return ( std::filesystem::exists(p) );
// }


void Course_Information(string txtaddress)
{
    ofstream out;
    string str;
    //if (is_file_exist(txtaddress) == true) out.open(txtaddress.c_str(), ios::app);
    //else 
    //cin.ignore();
    out.open(txtaddress.c_str(), ios::app);
    cout << "What is the teacher's name, who's in charge of this course?" << '\n';
    getline(cin, str);
    cout << '\n';
    out << str << '\n';
    //cin.ignore();
    cout << "What is the number of credits for this course?" << '\n';
    getline(cin, str);
    cout << '\n';
    out << str << '\n';
    //cin.ignore();
    cout << "What is the maximum number of students for the course, default is 50?" << '\n';
    getline(cin, str);
    cout << '\n';
    out << str << '\n';
    //cin.ignore();
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
    // menu;
    ifstream in;
    string txtaddress = address + "/Semester_Info.txt";
    in.open(txtaddress.c_str());
    //cout << (in.is_open() ? "MEOMEOMEO" : "NOPE");
    int i = 0;
    string str;
    while (getline(in, str))
    {
        i++;
        if (i > 4)
        {
            ifstream another_in;
            string another_str;
            string courseid;
            string coursename;
            //string classname;
            another_str = address + "/" + str + "/Course_Info.txt";
            another_in.open(another_str.c_str()); 
            getline(in, courseid);
            getline(in, coursename);
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
    while (getline(in, str))
    {
        inf[i] = str;
        //strcpy(*(inf[i]), str);
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
    cout << "Here are the courses, please type the course id and the class name of the course you want to update: ";
    string course;
    cin >> course;
    string classname; cin >> classname;
    cout << '\n';
    address = address + "/" + course + "-" + classname + "/Course_Info.txt";
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
    inf[choice + 1] = newinf;
    Update_File(address, inf);
    // if class name or course id is updated, update the file semester info, rename the folder
    return;
}
//

void AddClasstoCourse_CSV(string fileaddress, string courseaddress)
{
    // alot of file csv.
    string* info;
    ifstream in; ofstream out;
    string newfileaddress = courseaddress + "/Student_ID.csv";
    out.open(newfileaddress.c_str());
    in.open(fileaddress.c_str(), ios::in);
    info = new string[1000];

        string* row = new string[1000];
        string line, word; //temp while in temp. in>>'\n';
        int index = 1;
          while (getline(in, line)) 
          {
  
        delete row;
        row = new string[1000];
  
        //getline(in, line);

        stringstream s(line);

        int i = 1;
        while ( getline(s, word, ',') ) 
        {
            //ignore;
            row[i] = word;
            if (i == 1) info[index] = word;
            out << word << ",";
            i++;
        }
        out << '\n';
        index++;
          }
          in.close();
          out.close();
          info[0] = to_string(index-1);
  
    string iddata = courseaddress + "/Student_ID_data.txt";
    Update_File(iddata, info);
    return;
}

void Add1StudenttoCourse(string studentid, string courseaddress) 
{
    string address = courseaddress + "/Student_ID_data.txt";
    int i = 0;
    int cnt = 0;
    string schoolyear = "";
    string semester = "";
    string course = "";
    while (address[i] != '\0')
    {
        if (address[i] == '/') cnt++;
        if (cnt == 2 && address[i] != '/') schoolyear += address[i];
        if (cnt == 3 && address[i] != '/') semester += address[i];
        if (cnt == 4 && address[i] != '/') course += address[i];
    }
    ofstream out;
    out.open(address.c_str(), ios::app);
    out << studentid << '\n';
    out.close();
    address = courseaddress + "/Course_Info.txt";
    string* information; 
    information = Read_File(address);
    AddDatatoStudentFile(studentid, schoolyear, semester, course, information);
    cout << "This student with the ID has been added to the current course!" <<'\n';
    return;
}
void Remove1StudentfromCourse(string studentid, string courseaddress) 
{
    string address = courseaddress + "/Student_ID_data.txt";
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
    int index = 0;
    int cnt = 0;
    string schoolyear = "";
    string semester = "";
    string course = "";
    while (address[index] != '\0')
    {
        if (address[index] == '/') cnt++;
        if (cnt == 2 && address[index] != '/') schoolyear += address[index];
        if (cnt == 3 && address[index] != '/') semester += address[index];
        if (cnt == 4 && address[index] != '/') course += address[index];
    }

    address = courseaddress + "/Course_Info.txt";
    string* information;
    information = Read_File(address);
    AddDatatoStudentFile(studentid, schoolyear, semester, course, information);
    // e moi có 4 cái hà, cái hàm m 5 cái lận
    // à hay nhỉ
    cout << "This student with the ID has been removed from the current course!" <<'\n';
    return;
}
// bout to done.
// update more information at one time.

//int main() {
//    Update_CourseInformation("../Data/SchoolYear/2122/Spring");
//    return 0;
//}
void AddDatatoStudentFile (string id, string schoolyear, string semester, string courseid, string* data)
{
    //add, remove student from course, linked list string for the data updating
    //store class name to access the information of the class
    string fileaddress = "../Data/Student/" + id + ".txt";
    string* info;
    info = Read_File(fileaddress);
    int i = 1;
    //ofstream out;
    //out.open(fileaddress.c_str());
    while (i <= atoi(info[0].c_str()))
    {
        if (info[i] == schoolyear) break;
        i++;
    }
    while (i <= atoi(info[0].c_str()))
    {
        if (info[i] == semester) break;
        i++;
    }
    while (i <= atoi(info[0].c_str()))
    {
        if (info[i] == courseid) break;
        i++;
    }
    while (i <= atoi(info[0].c_str()) - 7)
    {
        info[i] = info[i + 7];
        i++;
    }
    int j = 1;
    // characeter endline '\n' redundant;
    //out.close();
    while (j <= atoi(data[0].c_str()))
    {
        info[i] = data[j];
        j++; i++;
    }
    Update_File(fileaddress, info);
}

void DeleteACourse(string courseid_coursename_address)
{
    int rename(const char * oldname, const char * newname); + deleted/ invalid;
    string id;
    ifstream in;
    string address = courseid_coursename_address + "/Student_ID_data.txt";
    in.open(address.c_str());
    while (in >> id)
    {
        Remove1StudentfromCourse(id, courseid_coursename_address);
    }
    in.close();
    int index = 0;
    int cnt = 0;
    string schoolyear = "";
    string semester = "";
    string course = "";
    while (courseid_coursename_address[index] != '\0')
    {
        if (courseid_coursename_address[index] == '/') cnt++;
        if (cnt == 2 && courseid_coursename_address[index] != '/') schoolyear += courseid_coursename_address[index];
        if (cnt == 3 && courseid_coursename_address[index] != '/') semester += courseid_coursename_address[index];
        if (cnt == 4 && courseid_coursename_address[index] != '/') course += courseid_coursename_address[index];
    }
    //address = courseid_coursename_address - course + "Semester_Info.txt";
    address = "";
    index = 0; cnt = 0;
    while (courseid_coursename_address[index] != '\0')
    {
        if (courseid_coursename_address[index] == '/') cnt++;
        address += courseid_coursename_address[index];
        if (cnt == 4) break;
    }
    address += "Semester_Info.txt";
    string* info = Read_File(address);
    in.open(address.c_str());
    string str;
    int i = 1;
    while (in >> str)
    {
        if (str == course) break;
        i++;
    }
    while (i <= atoi(info[0].c_str()) - 1)
    {
        info[i] = info[i+1];
        i++;
    }
    info[0] = to_string(i - 1);
    Update_File(address, info);
    cout << "The course has been deleted!" << '\n';
    return;
}

// int main ()
// {
//     //Creat_A_Semester();
//     //AddCourse("../Data/SchoolYear/2021-2022/Autumn");
//     //Update_CourseInformation("../Data/SchoolYear/2021-2022/Autumn");
//     DeleteACourse("../Data/SchoolYear/2021-2022/Autumn//CS161-22APCS2");
//     return 0;
// }

