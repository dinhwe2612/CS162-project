#include "../Header/SemesterCourse.h"

using namespace std;

bool CreateSemester(ASemester semester, string*& ListOfSemester, int& n) {
    ifstream in; ofstream out;
    string address = "Data/SchoolYear/" + semester.schoolYear + "/" + semester.semester;
    if(mkdir(address.c_str()) == -1)
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
    out.open(txtaddress.c_str(), ios::app);
    string courseaddress = address + "/" + course.id + "-" + course.Class;
    if(mkdir(courseaddress.c_str()) == -1)
        return false;
    out << course.id << "-" << course.Class << '\n';
    out.close();
    txtaddress = courseaddress + "/Course_Info.txt";
    out.open(txtaddress.c_str());
    out << course.id << "-" << course.Class << '\n';
    out << course.name << '\n';
    out << course.Class << '\n';
    out.close();
    Course_Information(txtaddress, course);
    cout << '\n';
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
