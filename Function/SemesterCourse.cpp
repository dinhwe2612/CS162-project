#include "../Header/SemesterCourse.h"
#include "../Header/CourseStruct.h"
#include "../Header/SemesterStruct.h"
#include <algorithm>

bool CreateSemester(ASemester semester, string*& ListOfSemester, int& n) {
    ifstream in; ofstream out;
    string address = "Data/SchoolYear/" + semester.schoolYear + "/" + semester.semester;
    if (filesystem::is_directory(address))
        return false;
    if (!filesystem::create_directory(address))
        return false;
    address += "/Semester_Info.txt";
    out.open(address.c_str());
    out << semester.schoolYear << '\n';
    out << semester.semester << '\n';
    out << semester.startDate << '\n';
    out << semester.endDate << '\n';
    out.close();
    string* tmp = new string[n + 1];
    if (n > 0) {
        for (int i = 0; i < n; ++i)
            tmp[i] = ListOfSemester[i];
        delete[] ListOfSemester;
    }
    tmp[n] = semester.semester;
    ListOfSemester = tmp;
    ++n;
    return true;
}

void Course_Information(string txtaddress, ACourse course) {
    ofstream out;
    string str;
    out.open(txtaddress.c_str(), ios::app);
    out << course.teacher << '\n';
    out << course.credit << '\n';
    out << course.maxStudent << '\n';
    out << course.dayOfWeek << '\n';
    out << course.session << '\n';
    out.close();
}

bool AddCourse(string schoolYear, string semester, ACourse course, ACourse*& ListOfCourse, int& n) {
    ifstream in;
    ofstream out;
    string address = "Data/SchoolYear/" + schoolYear + "/" + semester;
    string txtaddress = address + "/Semester_Info.txt";
    string courseaddress = address + "/" + course.id + "-" + course.Class;
    if (filesystem::is_directory(courseaddress)) {
        return false;
    }
    if(!filesystem::create_directory(courseaddress))
        return false;
    out.open(txtaddress.c_str(), ios::app);
    out << course.id << "-" << course.Class << '\n';
    out.close();
    txtaddress = courseaddress + "/Course_Info.txt";
    out.open(txtaddress.c_str());
    out << course.id << "-" << course.Class << '\n';
    out << course.name << '\n';
    out << course.Class << '\n';
    out.close();
    Course_Information(txtaddress, course);
    ACourse* tmp = new ACourse[n + 1];
    if (n > 0) 
    {
        for (int i = 0; i < n; ++i) tmp[i] = ListOfCourse[i];
        delete[] ListOfCourse;
    }
    tmp[n] = course;
    ListOfCourse = tmp;
    ++n;
    return true;
}
// readfile and update file for efficiency
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
//
bool Update_CourseInformation(ACourse& course, string schoolYear, string semester)
{
    string FileName = "Data/SchoolYear/" + schoolYear + "/" + semester + "/" + course.id + "-" + course.Class;
    string address = FileName + "/Course_Info.txt";
    string *info = new string[9];
    // info[0] = "8";
    info[1] = course.id + "-" + course.Class;
    info[2] = course.name;
    info[3] = course.Class;
    info[4] = course.teacher;
    info[5] = to_string(course.credit);
    info[6] = to_string(course.maxStudent);
    info[7] = course.dayOfWeek;
    info[8] = course.session; 
    // Update_File(address, info);
    // delete[] info;
    ofstream out;
    out.open(address.c_str());
    for (int i = 1; i <= 8; i++) out << info[i] << '\n';
    out.close();
    delete[] info;
    return true;
}

bool AddClasstoCourse_CSV(string fileaddress, ACourse course, string schoolYear, string semester)
{
    string* info;
    ifstream in; ofstream out;
    string courseaddress = "Data/SchoolYear/" + schoolYear + "/" + semester + "/" + course.id + "-" + course.Class;
    string newfileaddress = courseaddress + "/Student_ID.csv";
    out.open(newfileaddress.c_str());
    in.open(fileaddress.c_str());
    info = new string[100];

        
        string line, word; //temp while in temp. in>>'\n';
        int index = 1;
        int i;
          while (getline(in, line)) 
          {
            
        string* row = new string[100];
        

        stringstream s(line);

         i = 1;
        while ( getline(s, word, ',') ) 
        {
            // cout << word << '\n';
            // cout << i << '\n';
            //ignore;
            row[i] = word;
            if (i == 1) info[index] = word;
            out << word << ',';
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
    return true;
}

bool Add1StudenttoCourse(string studentid, ACourse course, string schoolYear, string semester)
{
    string courseaddress = "Data/SchoolYear/" + schoolYear + "/" + semester + "/" + course.id + "-" + course.Class;
    string address = courseaddress + "/Student_ID_data.txt";
    string fileaddress = "Data/Student/" + studentid + ".txt";
    ifstream in;
    in.open(fileaddress.c_str());
    if (!in.is_open()) return false;
    string* check_if_exist = Read_File(address);
    for (int ka = 1; ka <= atoll(check_if_exist[0].c_str()); ka++)
    {
        if (check_if_exist[ka] == studentid) return false;
    }
    ofstream out;
    out.open(address.c_str(), ios::app);
    out << studentid << '\n';
    out.close();
    int number = 1;
    int* sorting = new int[100];
    string *id = Read_File(address);
    while (number <= atoll(id[0].c_str()))
    {
        sorting[number] = atoll(id[number].c_str());
        number++;
    }
    sorting[0] = number - 1;
    sort(sorting + 1, sorting + number);
    out.open(address.c_str());
    number = 1;
    while (number <= sorting[0])
    {
        out << sorting[number] << '\n';
        number++;
    }
    out.close();
    out.open(fileaddress.c_str(), ios::app);
    out << course.id << "-" << course.Class << '\n';
    out.close();
    return true;
}

bool Remove1StudentfromCourse(string studentid, ACourse course, string schoolYear, string semester)
{
    string courseaddress = "Data/SchoolYear/" + schoolYear + "/" + semester + "/" + course.id + "-" + course.Class;
    string address = courseaddress + "/Student_ID_data.txt";
    string* info;
    info = Read_File(address.c_str());
    int i = 1;
    ofstream out;
    out.open(address.c_str());
    while (i <= atoi(info[0].c_str()))
    {
        if (info[i] != studentid)  out << info[i] << '\n';
        i++;
    }
    i = 1;
    out.close();
    address = "../Data/Student/" + studentid + ".txt";
    info = Read_File(address);
    string tmp = course.id + "-" + course.Class;
    while (i <= atoi(info[0].c_str()))
    {
        if (info[i] == tmp) break;
        i++;
    }
    while (i <= atoi(info[0].c_str()) - 1)
    {
        info[i] = info[i + 1];
        i++;
    }
    info[0] = to_string(i - 1);
    Update_File(address, info);
    return true;
}
bool DeleteACourse(string schoolYear, string semester, ACourse course, ACourse*& courses, int& n)
{
    string courseid_coursename_address = "Data/SchoolYear/" + schoolYear + "/" + semester + "/" + course.id + "-" + course.Class;
    string id;
    ifstream in;
    string address = courseid_coursename_address + "/Student_ID_data.txt";
    in.open(address.c_str());
    while (getline(in, id, '\n'))
    {
        Remove1StudentfromCourse(id, course, schoolYear, semester);
    }
    in.close();
    address = "Data/SchoolYear/" + schoolYear + "/" + semester + "/Semester_Info.txt";
    string* info = Read_File(address);
    string tmp = course.id + "-" + course.Class;
    int i = 1;
    while (i <= atoi(info[0].c_str()))
    {
        if (info[i] == tmp) break;
        i++;
    }
    while (i <= atoi(info[0].c_str()) - 1)
    {
        info[i] = info[i+1];
        i++;
    }
    info[0] = to_string(i - 1);
    Update_File(address, info);
    filesystem::remove_all(courseid_coursename_address.c_str());
    if (n == 1) 
    {
        n--;
        delete[] courses;
        return true;
    }
    ACourse* temp = new ACourse[n - 1];
    int x = 0;
        for (int i = 0; i < n; ++i) 
        {
            if (courses[i].Class == course.Class && courses[i].id == course.id) {} else 
            {
                temp[x] = courses[i];
                x++;
            }
        }
        delete[] courses;
    courses = temp;
    --n;
    return true;
}

// int main()
// {
//     ACourse course;
//     course.id = "CS162";
//     course.Class = "22APCS2";
//     //AddClasstoCourse_CSV("D:/file.csv", course, "2023-2024", "Autumn");
//     //Add1StudenttoCourse("22124555", course, "2023-2024", "Autumn");
//     //Remove1StudentfromCourse("22124555", course, "2023-2024", "Autumn");
//     DeleteACourse
//     return 0;
// }

