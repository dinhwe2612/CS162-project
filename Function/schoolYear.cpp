#include "../Header/schoolYear.h"

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
    string lastYearPath = "Data/SchoolYear/" + lastSchoolYear + "/Classes/"; //path of last year classes
    string thisYearPath = "Data/SchoolYear/" + schoolYear + "/Classes/"; // path of this year classes
    string classExclude = to_string((stoi(schoolYear.substr(2, 2)) - 4));
    for (auto& file : filesystem::directory_iterator(lastYearPath)) {
        if (file.path().filename().string().substr(0, 2) >= classExclude) {
            string filename = file.path().filename().string();
            string sourcePath = file.path().string();
            string targetPath = thisYearPath + filename;
            filesystem::copy(sourcePath, targetPath, std::filesystem::copy_options::overwrite_existing);
        }
    }
}

// return true if execute successfully
// return false if directories cannot be created or school year already exists
bool createSchoolYear(string *&ListOfSchoolYear, int &n, string schoolYear) {
    string dir = "Data/SchoolYear/" + schoolYear + '/';
    // if the schoolYear already exists return false
    if (filesystem::is_directory(dir))
        return false;
    filesystem::create_directories(dir);
    filesystem::create_directories(dir + "Classes");
    filesystem::create_directories(dir + "Spring");
    filesystem::create_directories(dir + "Summer");
    filesystem::create_directories(dir + "Autumn");

    string *tmp = new string[n + 1];
    if (n > 0) {
        for (int i = 0; i < n; ++i)
            tmp[i] = ListOfSchoolYear[i];
        delete[] ListOfSchoolYear;
    }
    tmp[n] = schoolYear;
    ListOfSchoolYear = tmp;
    ++n;
    sort(ListOfSchoolYear, ListOfSchoolYear + n, greater<string>());
    add234(schoolYear);
    return true;
}

// return true if execute successfully
// return false if directories cannot be created or school year already exists
bool createClass(string*& ListOfClass, int& n, string Class, string schoolYear) {
    string dir = "Data/SchoolYear/" + schoolYear + "/Classes/" + Class + ".txt";
    if (filesystem::is_regular_file(dir))
        return false;
    ofstream fout;
    fout.open(dir);
    fout.close();

    string *tmp = new string[n + 1];
    if (n > 0) {
        for (int i = 0; i < n; ++i)
            tmp[i] = ListOfClass[i];
        delete[] ListOfClass;
    }
    tmp[n] = Class;
    ListOfClass = tmp;
    ++n;
    sort(ListOfClass, ListOfClass + n);
    return true;
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
    if (!filesystem::exists(dir))
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

// add student to the student database and the class list of the student
// return true if execute successfully
// return false when student already exists, or cannot add student due to errors
bool addStudent(Student student, string schoolYear, string Class) {
    string studentDir = "Data/Student/";
    if (filesystem::exists(studentDir + student.studentID + ".txt"))
        return false;
    if (!filesystem::exists(studentDir)) 
        filesystem::create_directories(studentDir);
    ofstream fout;
    fout.open(studentDir + student.studentID + ".txt");
    fout << student.studentID << endl;
    fout << student.firstName << endl;
    fout << student.lastName << endl;
    fout << student.gender << endl;
    fout << student.DOB << endl;
    fout << student.socialID << endl;
    fout.close();
    string dir = "Data/SchoolYear/" + schoolYear + "/Classes/" + Class + ".txt";
    int n = getStudentNo(dir);
    fout.open(dir, ios_base::app);
    fout << n + 1 << ' ' << student.studentID << endl;
    fout.close();
    return true;
}

bool addStudentToClass(Student*& listOfStudent, int& n, Student student, string schoolYear, string Class) {
    addStudent(student, schoolYear, Class);

    // update list of student
    Student* tmp = new Student[n + 1];
    for (int i = 0; i < n; ++i)
        tmp[i] = listOfStudent[i];
    listOfStudent = tmp;
    ++n;
    return true;
}

// function to import students info from csv file
// dir parameter is the directory of the csv file
void importStudent(string dir, string schoolYear, string Class) {
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
        addStudent(student, schoolYear, Class);
    }
}

// int main() {
// //     string path = "../../import/21TT1.csv";
// //     string Class = "21TT1";
// //     createSchoolYear("2022", "2023");
// //     createSchoolYear("2021", "2022");
// //     importStudent(path, "2022-2023", Class);
// //     Student student;
// //     getStudent(student);
// //     saveStudent(student, "2022-2023", Class);
//     string* listOfSchoolYear;
//     int n = 0;
//     createSchoolYear(listOfSchoolYear, n, "2023-2024");
//     return 0;
// }