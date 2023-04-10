#include "../Header/view.h"

bool checkDirectory(const filesystem::path& path) {
    if (!filesystem::exists(path)) {
        // path does not exist
        return false;
    }

    if (!filesystem::is_directory(path)) {
        // path is not a directory
        return false;
    }

    return true;
}

string getPath (string s, string name = "", string schoolYear = "") {
    if (s.compare("Class") == 0)
        return "../Data/SchoolYear/" + schoolYear + "/Classes/" + name;
    else if (s.compare("Student") == 0)
        return "Data/Student/" + name + ".txt";
    else if (s.compare("Course") == 0) 
        return "Data/SchoolYear/" + schoolYear + "/" + name + "/";
    else if (s.compare("StudentInCourse") == 0) 
        return "Data/SchoolYear/" + schoolYear + "/" + name + "/" + "Student_ID_data.txt";
    else if (s.compare("SchoolYear") == 0)
        return "Data/SchoolYear/";
    else
        return "";
}

// return true if execute successfully
// return false if directory-related errors occur
bool viewClasses(string*& classes, int & n, string schoolYear) {
    const filesystem::path path = getPath("Class", "", schoolYear);
    if (!checkDirectory(path))
        return false;
    n = 0;
    for (const auto & entry : filesystem::directory_iterator(path))
        if (entry.is_regular_file())
            ++n;
    classes = new string[n];
    int i = 0;
    for (const auto & entry : filesystem::directory_iterator(path))
        if (entry.is_regular_file()) {
            classes[i] = entry.path().stem().string();
            ++i;
        }

    return true;
}

int getStudentNo(string Class, string schoolYear) {
    const filesystem::path dir = getPath("Class", Class + ".txt", schoolYear);
    if (!filesystem::exists(dir))
        return 0;
    ifstream fin;
    fin.open(dir);
    string tmp;
    fin >> tmp;
    if (tmp == "")
        return 0;
    fin.close();
    fin.open(dir);
    int n = 0;
    while(!fin.eof()){
        fin.ignore(1000, '\n');
        fin.ignore();
        ++n;
    }
    fin.close();
    return n;
}

bool viewStudentInClass (string Class, string schoolYear, Student*& students, int& n) {
    const filesystem::path path = getPath("Class", Class + ".txt", schoolYear);
    if (!filesystem::exists(path)) {
        // file does not exist
        return false;
    }
    ifstream fin;
    fin.open(path);
    n = getStudentNo(Class, schoolYear);
    students = new Student[n];
    int i = 0;
    while (!fin.eof()) {
        string studentID;
        fin.ignore();
        fin >> studentID;
        fin.ignore(1000, '\n');
        fin.ignore();
        // get info about student from Data/Student
        ifstream fi;
        string gender;
        fi.open(getPath("Student", studentID));
        getline(fi, students[i].studentID, '\n');
        getline(fi, students[i].firstName, '\n');
        getline(fi, students[i].lastName, '\n');
        getline(fi, gender, '\n');
        if (gender == "0")
            students[i].gender = 0;
        else if (gender == "1")
            students[i].gender = 1;
        else
            students[i].gender = 2;
        getline(fi, students[i].DOB, '\n');
        getline(fi, students[i].socialID, '\n');
        fi.close();
        ++i;
    }
    fin.close();
    cerr << n << '\n';
    //LOI NE CAU FIX DUM DI
    if (students[0].studentID == "") n = 0;//dòng này để tạm cho nó đỡ ngu
    for(int i = 0; i < n; ++i)
        cerr << (students[i].studentID == "") << '\n';
    return true;
}

// view course IDs of a particular semester in a school year
bool viewCourses(string schoolYear, string semester) {
    const filesystem::path path = getPath("Course", semester, schoolYear);
    if (!checkDirectory(path))
        return false;
    for (const auto & entry : filesystem::directory_iterator(path))
        if (entry.is_directory())
            cout << entry.path().stem().string() << endl;
    return true;
}

// view student ids in a course
bool viewStudentInCourse(string schoolYear, string semester, string course) {
    string path = getPath("StudentInCourse", semester + "/" + course, schoolYear);
    if (!checkDirectory(path))
        return false;
    ifstream fin;
    fin.open(path);
    cout << "Student IDs of " << course << "course in " << semester << " semester in " << schoolYear;
    if (!fin.is_open())
        return false;
    while(!fin.eof()) {
        string studentID;
        fin >> studentID;
        cout << studentID << endl;
    }
    return true;
}

// view courses that a student studied
bool viewCoursesOfStudent(string id, string schoolYear, string semester) {
    string path = getPath("Course", semester, schoolYear);
    if (!checkDirectory(path))
        return false;

    // count the number of course in the semester
    int n = 0;
    for (const auto & entry : filesystem::directory_iterator(path))
        if (entry.is_directory())
            ++n;
    
    // make a string array of courses
    string* courses = new string[n];
    int i = 0;
    for (const auto & entry : filesystem::directory_iterator(path))
        if (entry.is_directory()) {
            courses[i] = entry.path().stem().string();
            ++i;
        }

    // check which course the student studied in the semester
    string* studentCourses = new string [n];
    int j = 0;
    for (int i = 0; i < n; ++i) {
        string coursePath = path + courses[i] + "/Student_ID_data.txt";
        ifstream fin;
        fin.open(coursePath);
        if (!fin.is_open())
            continue;
        while (!fin.eof()) {
            string studentID;
            fin >> studentID;
            if (studentID.compare("") == 0)
                break;
            if (studentID.compare(id) == 0) {
                studentCourses[j] = courses[i];
                ++j;
            }
            fin.ignore(1000, '\n');
        }
        fin.close();
    }

    // print out
    for (int i = 0; i < j; ++i)
        cout << studentCourses[i] << ' ';
    delete[]courses;
    delete[]studentCourses;
    return true;
}

bool viewSchoolYear (string*& schoolYears, int& n) {
    n = 0;
    const filesystem::path path = getPath("SchoolYear");
    int i = 0;
    if (!checkDirectory(path))
        return false;
    for (const auto & entry : filesystem::directory_iterator(path))
        if (entry.is_directory())
            ++n;
    schoolYears = new string[n];
    for (const auto & entry : filesystem::directory_iterator(path))
        if (entry.is_directory()) {
            schoolYears[i] = entry.path().stem().string();
            ++i;
        }
    sort(schoolYears, schoolYears + n, greater<string>());
    return true;
}

int main() {
//     string schoolYear = "2022-2023";
//     string Class = "22TT2";
//     if (!viewClasses(schoolYear))
//         cout << "The school year has not been created yet, or the database has been corrupted.";

//     if (!viewCourses(schoolYear, "Spring"))
//         cout << "Course does not exist.";
//     if (!viewStudentInCourse(schoolYear, "Spring", "12345"))
//         cout << "Course Student List does not exist.";

//     if (!viewCoursesOfStudent("22125002", "2021-2022", "Autumn"))
//         cout << "Student ID, school year or semester does not exist.";
//     Student* students;
//     int n = 0;
//     if (!viewStudentInClass(Class, schoolYear, students, n))
//         cout << "Class not found.";
//     else
//         for (int i = 0; i < n; ++i)
//             cout << students[i].studentID << ' ';

//     delete[]students;
    cout << getStudentNo("22TT1", "2022-2023");
    return 0;
}
