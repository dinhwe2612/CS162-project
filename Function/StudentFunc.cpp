#include "../Header/StudentFunc.h"

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

bool ViewSchoolYearStudent(Student &stu, string *&schoolYear, int &n) {
    n = 0;
    const filesystem::path path = "../Data/SchoolYear/";
    int i = 0;
    if (!checkDirectory(path))
        return false;
    for (const auto & entry : filesystem::directory_iterator(path)) {
        if (entry.is_directory()) {
            const filesystem::path pathtmp = "../Data/SchoolYear/" + entry.path().stem().string() + "/Classes/" + stu.Class + ".txt";
            if (filesystem::exists(pathtmp))
                ++n;
        }
    }
    schoolYear = new string[n];
    n = 0;
    for (const auto & entry : filesystem::directory_iterator(path)) {
        if (entry.is_directory()) {
            const filesystem::path pathtmp = "../Data/SchoolYear/" + entry.path().stem().string() + "/Classes/" + stu.Class + ".txt";
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

bool ViewCoursesStudent(Student &stu, ACourse *&course, ScoreBoard *&scores, int &n) {
    //get name in studentid.txt
    n = 0;
    string pathToStudentFile = "../Data/Student/" + stu.studentID + ".txt";
    ifstream fin(pathToStudentFile);
    if (!fin.is_open())
        return false;
    int cnt = 0;
    string tmp;
    while(cnt < 7) getline(fin, tmp), ++cnt;
    while(getline(fin, tmp)) {
        if (tmp == "") break;
        ++n;
    }
    fin.close();
    fin.open(pathToStudentFile);
    cnt = 0;
    while(cnt < 7) getline(fin, tmp), ++cnt;
    course = new ACourse[n];
    cnt = 0;
    while(getline(fin, tmp)) {
        if (tmp == "") break;
        course[cnt++].name = tmp;
    }
    fin.close();
    //get info in course directory
    scores = new ScoreBoard[n];
    for(int i = 0; i < n; ++i) {
        //get info course
        string pathToCourse = FindPathCourse(course[i].name);
        fin.open(pathToCourse + "Course_Info.txt");
        if (!fin.is_open())
            return false;
        getline(fin, tmp);
        getline(fin, course[i].name);
        getline(fin, course[i].Class);
        getline(fin, course[i].teacher);
        fin >> course[i].credit;
        fin >> course[i].maxStudent;
        getline(fin, course[i].dayOfWeek);
        getline(fin, course[i].session);
        fin.close();
        //get score
        fin.open(pathToCourse + "Score/" + stu.studentID + ".txt");
        if (!fin.is_open())
            return false;
        fin >> scores[i].other;
        fin >> scores[i].midterm;
        fin >> scores[i].finals;
        fin >> scores[i].total;
        fin.close();
    }
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