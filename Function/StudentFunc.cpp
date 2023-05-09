#include "../Header/StudentFunc.h"

bool ValidDirectory(const filesystem::path& path) {
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

bool LoadDataStudent(Student &stu, string username) {
    ifstream fin("Data/Student/" + username + ".txt");
    if (!fin.is_open())
        return false;
    getline(fin, stu.studentID);
    getline(fin, stu.firstName);
    getline(fin, stu.lastName);
    getline(fin, stu.Class);
    fin >> stu.gender;
    getline(fin, stu.DOB);
    getline(fin, stu.DOB);
    getline(fin, stu.socialID);
    fin.close();
    return true;
}

bool ViewSchoolYearStudent(Student &stu, string *&schoolYear, int &n) {
    n = 0;
    const filesystem::path path = "Data/SchoolYear/";
    int i = 0;
    if (!ValidDirectory(path))
        return false;
    for (const auto & entry : filesystem::directory_iterator(path)) {
        if (entry.is_directory()) {
            const filesystem::path pathtmp = "Data/SchoolYear/" + entry.path().stem().string() + "/Classes/" + stu.Class + ".txt";
            if (filesystem::exists(pathtmp))
                ++n;
        }
    }
    schoolYear = new string[n];
    n = 0;
    for (const auto & entry : filesystem::directory_iterator(path)) {
        if (entry.is_directory()) {
            const filesystem::path pathtmp = "Data/SchoolYear/" + entry.path().stem().string() + "/Classes/" + stu.Class + ".txt";
            if (filesystem::exists(pathtmp))
                schoolYear[n++] = entry.path().stem().string();
        }
    }
    sort(schoolYear, schoolYear + n, greater<string>());
    return true;
}

string FindPathCourse(string nameCourseFile) {
    const filesystem::path path = "../Data/SchoolYear/";
    for(const auto & schoolYear : filesystem::directory_iterator(path)) {//iterate through school year
        if (schoolYear.is_directory()) {
            const filesystem::path pathToSchoolYear = path.string() + schoolYear.path().stem().string() + "/";
            for(const auto & semester : filesystem::directory_iterator(pathToSchoolYear)) {//iterate through semester
                if (semester.path().stem().string() == "Classes") continue;
                const filesystem::path pathToSemester = pathToSchoolYear.string() + semester.path().stem().string() + "/";
                for(const auto & course : filesystem::directory_iterator(pathToSemester)) {//iterate through course
                    if (!course.is_directory()) continue;
                    string pathToCourse = pathToSemester.string() + course.path().stem().string() + "/";
                    if (course.path().stem().string() == nameCourseFile)
                        return pathToCourse;
                }
            }
        }
    }
    return "";
}

bool IsInCourse(string schoolYear, string semester, string courseName, string studentID) {
    string pathToStudentIDData = "Data/SchoolYear/" + schoolYear + "/" + semester + "/" + courseName + "/Student_ID_data.txt";
    ifstream fin(pathToStudentIDData);
    if (!fin.is_open())
        return false;
    string tmp;
    while(!fin.eof()) {
        getline(fin, tmp);
        if (tmp == studentID) {
            fin.close();
            return true;
        }
    }
    fin.close();
    return false;
}

bool ViewCoursesStudent(string schoolYear, string semester, string studentID, ACourse *&listOfCourse, ScoreBoard *&scores, int &n) {
    //count n
    string pathToSemester = "Data/SchoolYear/" + schoolYear + "/" + semester + "/";
    n = 0;
    if (!ValidDirectory(pathToSemester))
        return false;
    for(const auto & course : filesystem::directory_iterator(pathToSemester)) {
        if (IsInCourse(schoolYear, semester, course.path().stem().string(), studentID))
            ++n;
    }
    //get info in course directory
    listOfCourse = new ACourse[n];
    scores = new ScoreBoard[n];
    int i = 0;
    ifstream fin;
    for(const auto & course : filesystem::directory_iterator(pathToSemester)) {
        if (course.path().stem().string() == "Semester_Info") continue;
        //get info course
        string pathToCourse = course.path().string() + "/";
        fin.open(pathToCourse + "Course_Info.txt");
        if (!fin.is_open())
            return false;
        getline(fin, listOfCourse[i].id);
        while(listOfCourse[i].id.size() && listOfCourse[i].id.back() != '-') listOfCourse[i].id.pop_back();
        listOfCourse[i].id.pop_back(); 
        getline(fin, listOfCourse[i].name);
        getline(fin, listOfCourse[i].Class);
        getline(fin, listOfCourse[i].teacher);
        fin >> listOfCourse[i].credit;
        fin >> listOfCourse[i].maxStudent;
        getline(fin, listOfCourse[i].dayOfWeek);
        getline(fin, listOfCourse[i].session);
        fin.close();
        //get score
        fin.open(pathToCourse + "Score/" + studentID + ".txt");
        if (!fin.is_open())
            return false;
        fin >> scores[i].other;
        fin >> scores[i].midterm;
        fin >> scores[i].finals;
        fin >> scores[i].total;
        fin.close();
        ++i;
    }
    return true;
}

// int main() {
//     Student stu;
//     stu.Class = "22TT2";
//     stu.studentID = "22125016";
//     string *schoolYear;
//     int n;
//     ViewSchoolYearStudent(stu, schoolYear, n);
//     cout << n << '\n';
//     for(int i = 0; i < n; ++i) {
//         cout << schoolYear[i] << '\n';
//     }
//     ACourse *course;
//     ScoreBoard *scores;
//     ViewCoursesStudent(stu, course, scores, n);
//     cout << n << endl;
//     for(int i = 0; i < n; ++i) {
//         cout << course[i].name << ' ' << scores[i].total << '\n';
//     }
//     return 0;
// }