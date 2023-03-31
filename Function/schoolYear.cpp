#include <iostream>
#include <fstream>
#include <experimental/filesystem>
#include "../Header/StudentStruct.h"

using namespace std;

void createSchoolYear(string beginYear, string endYear) {
    string dir = "../Data/" + beginYear + '-' + endYear + '/';
    experimental::filesystem::create_directory(dir);
    experimental::filesystem::create_directory(dir + "Classes");
    experimental::filesystem::create_directory(dir + "Semester1");
    experimental::filesystem::create_directory(dir + "Semester2");
    experimental::filesystem::create_directory(dir + "Semester3");
}

// input student info from console
void getStudent(Student& student) {
    cout << "Enter student information" << endl;
    cout << "Student ID: ";
    cin >> student.studentID;
    cin.ignore();
    cout << "First name: ";
    getline(cin, student.firstName, '\n');
    cout << "Last name: ";    
    getline(cin, student.lastName, '\n');
    cout << "Gender(male/female/other): ";
    string gendertmp;
    cin >> gendertmp;
    if (gendertmp.compare("male") == 0)
        student.gender = 0;
    else if (gendertmp.compare("female") == 0)
        student.gender = 1;
    else
        student.gender = 2;
    cout << "Date of birth (DD/MM/YYYY): ";
    cin >> student.DOB;
    cout << "Class: ";
    cin >> student.Class;
    cout << "Social ID: ";
    cin >> student.socialID;
}

// find the current biggest student no. in a class to append the next student at the end.
int getStudentNo(string dir) {
    if (!experimental::filesystem::exists(dir))
        return 0;
    ifstream fin;
    fin.open(dir);
    int n = 0;
    while(!fin.eof()){
        fin.ignore(1000, '\n');
        fin.ignore();
        ++n;
    }
    return n;
}

void saveStudent(Student student, string schoolYear, string Class) {
    ofstream fout;
    fout.open("../Data/Students/" + student.studentID + ".txt");
    fout << student.studentID << endl;
    fout << student.firstName << endl;
    fout << student.lastName << endl;
    fout << student.gender << endl;
    fout << student.DOB << endl;
    fout << student.socialID << endl;
    fout.close();
    string dir = "../Data/" + schoolYear + "/Classes/" + Class + ".txt";
    int n = getStudentNo(dir);
    fout.open(dir, ios_base::app);
    fout << n + 1 << ' ' << student.studentID << endl;
    fout.close();
}

// function to import students info from csv file
// dir parameter is the directory of the csv file
void importStudent(string dir, string schoorYear, string Class) {
    ifstream fin;
    fin.open(dir);
    Student student;
    while(!fin.eof()) {
        fin.ignore(1000, ',');
        getline(fin, student.studentID, ',');
        getline(fin, student.firstName, ',');
        getline(fin, student.lastName, ',');
        string gendertmp;
        getline(fin, gendertmp, ',');
        if (gendertmp.compare("male") == 0 || gendertmp.compare("Male") == 0)
            student.gender = 0;
        else if (gendertmp.compare("female") == 0 || gendertmp.compare("Female") == 0)
            student.gender = 1;
        else
            student.gender = 2;
        getline(fin, student.DOB, ',');
        fin >> student.socialID;
        fin.ignore(1000, '\n');
        fin.ignore();
        saveStudent(student, schoorYear, Class);
    }
}

string getLastSchoolYear (string schoolYear) {
    string tmp = schoolYear.substr(0, 4);
    int year = stoi(tmp) - 1;
    string year1 = to_string(year);
    tmp = schoolYear.substr(5, 4);
    year = stoi(tmp) - 1;
    string year2 = to_string(year);
    return year1 + '-' + year2;
}

void add234(string schoolYear) {
    string lastSchoolYear = getLastSchoolYear(schoolYear);
    string path = "../Data/" + lastSchoolYear + "/Classes/"; //path of last year classes
    string dir = "../Data/" + schoolYear + "/Classes/"; // path of this year classes
    string classExclude = to_string((stoi(schoolYear.substr(2, 2)) - 4));
    for (auto& file : experimental::filesystem::directory_iterator(path)) {
        if (file.path().filename().string().substr(0, 2) != classExclude) {
            string filename = file.path().filename().string();
            string sourcePath = file.path()./*filename()*/string();
            string targetPath = dir + filename;
            experimental::filesystem::copy(sourcePath, targetPath, std::experimental::filesystem::copy_options::overwrite_existing);
        }
    }
}



int main() {
    string path = "";
    string Class = "22TT2";
    createSchoolYear("2022", "2023");
    // createSchoolYear("2021", "2022");
    importStudent(path, "2022-2023", Class);
    // Student student;
    // getStudent(student);
    // saveStudent(student, "2022-2023", Class);
    // add234("2022-2023");
}