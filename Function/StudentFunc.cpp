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
    // cout << n << endl;
    if (n == 0) return true;
    //get info in course directory
    listOfCourse = new ACourse[n];
    scores = new ScoreBoard[n];
    int i = 0;
    ifstream fin;
    for(const auto & course : filesystem::directory_iterator(pathToSemester)) {
        if (course.path().stem().string() == "Semester_Info") continue;
        if (!IsInCourse(schoolYear, semester, course.path().stem().string(), studentID)) continue;
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
        if (!fin.is_open()) continue;
        fin >> scores[i].other;
        fin >> scores[i].midterm;
        fin >> scores[i].finals;
        fin >> scores[i].total;
        fin.close();
        ++i;
    }
    return true;
}

bool viewScoreBoardInSchoolYear(string schoolYear, string studentID, ACourse* &listOfCourse, ScoreBoard* &scores, int &n) {
    string pathToSchoolYear = "Data/SchoolYear/" + schoolYear + "/";
    int numberOfSemester = 0;
    for (const auto& course : filesystem::directory_iterator(pathToSchoolYear))
        if (course.path().stem().string() != "Classes")
            ++numberOfSemester;
    string* semesters = new string[numberOfSemester];
    int j = 0;
    for (const auto& course : filesystem::directory_iterator(pathToSchoolYear))
        if (course.path().stem().string() != "Classes") {
            semesters[j] = course.path().stem().string();
            ++j;
        }
    //count n
    n = 0;
    int* numOfCourseEachSem = new int[numberOfSemester];
    for (int i = 0; i < numberOfSemester; ++i) {
        int num = 0;
        string pathToSemester = "Data/SchoolYear/" + schoolYear + "/" + semesters[i] + "/";
        if (!ValidDirectory(pathToSemester))
            return false;
        for(const auto & course : filesystem::directory_iterator(pathToSemester)) 
            if (IsInCourse(schoolYear, semesters[i], course.path().stem().string(), studentID))
                ++num;
        n += num;
        numOfCourseEachSem[i] = num;
    }
    
    // cout << n << endl;
    if (n == 0) return true;
    //get info in course directory
    listOfCourse = new ACourse[n];
    scores = new ScoreBoard[n];
    int i = 0;
    ifstream fin;
    for (int k = 0; k < numberOfSemester; ++k) {
        string pathToSemester = "Data/SchoolYear/" + schoolYear + "/" + semesters[k] + "/";
        for(const auto & course : filesystem::directory_iterator(pathToSemester)) {
            if (course.path().stem().string() == "Semester_Info") continue;
            if (!IsInCourse(schoolYear, semesters[k], course.path().stem().string(), studentID)) continue;
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
            if (!fin.is_open()) continue;
            fin >> scores[i].other;
            fin >> scores[i].midterm;
            fin >> scores[i].finals;
            fin >> scores[i].total;
            fin.close();
            ++i;
        }
    }
    return true;
}

bool viewScoreBoardAll(Student &stu, ACourse* &listOfCourse, ScoreBoard* &scores, int &n) {
    // get a list of school year the student studied
    string* schoolYear;
    int numOfSchoolYear;
    ViewSchoolYearStudent(stu, schoolYear, numOfSchoolYear);

    // create 2D arrays to store courses and their scores of each year seperately
    ACourse** listOfCoursesEachYear = new ACourse*[numOfSchoolYear];
    ScoreBoard** scoresEachYear = new ScoreBoard*[numOfSchoolYear];
    int* numOfCourseEachYear = new int[numOfSchoolYear];
    n = 0;
    for (int i = 0; i < numOfSchoolYear; ++i) {
        int num = 0;
        viewScoreBoardInSchoolYear(schoolYear[i], stu.studentID, listOfCoursesEachYear[i], scoresEachYear[i], numOfCourseEachYear[i]);
        n += num;
    }

    // merge the list courses and scores of each year above a single list of courses and scores
    listOfCourse = new ACourse[n];
    scores = new ScoreBoard[n];
    int i = 0;
    for (int j = 0; j < numOfSchoolYear; ++j)
        for (int k = 0; k < numOfCourseEachYear[i]; ++k) {
            listOfCourse[i] = listOfCoursesEachYear[j][k];
            scores[i] = scoresEachYear[j][k];
            ++i;
        }
    
    // delete temprorary data structures
    delete[] schoolYear;
    delete numOfCourseEachYear;
    for (int j = 0; j < numOfSchoolYear; ++j) {
        delete[] listOfCoursesEachYear[j];
        delete[] scoresEachYear[j];
    }
    delete[] listOfCoursesEachYear;
    delete[] scoresEachYear;
}

bool ViewAllCoursesStudent(string studentID, ACourse *&listOfCourses, ScoreBoard *&scores, int &n) {
    n = 0;
    filesystem::path pathToData = "Data/SchoolYear/";
    //for count n
    for(const auto & schoolyear : filesystem::directory_iterator(pathToData)) {
        if (!schoolyear.is_directory()) continue;
        for(const auto & semester : filesystem::directory_iterator(schoolyear.path())) {
            if (!semester.is_directory()) continue;
            for(const auto & course : filesystem::directory_iterator(semester.path())) {
                if (!course.is_directory()) continue;
                if (!IsInCourse(schoolyear.path().stem().string(), semester.path().stem().string(), course.path().stem().string(), studentID)) continue;
                ++n;
            }
        }
    }
    if (n == 0) return true;
    //for load data
    listOfCourses = new ACourse[n];
    scores = new ScoreBoard[n];
    int i = 0;
    for(const auto & schoolyear : filesystem::directory_iterator(pathToData)) {
        if (!schoolyear.is_directory()) continue;
        for(const auto & semester : filesystem::directory_iterator(schoolyear.path())) {
            if (!semester.is_directory()) continue;
            for(const auto & course : filesystem::directory_iterator(semester.path())) {
                if (!course.is_directory()) continue;
                if (!IsInCourse(schoolyear.path().stem().string(), semester.path().stem().string(), course.path().stem().string(), studentID)) continue;
                
                // cout << course.path().string() << endl;

                string pathToCourse = course.path().string() + "/";
                ifstream fin;
                //get info course
                fin.open(pathToCourse + "Course_Info.txt");
                if (!fin.is_open())
                    return false;
                getline(fin, listOfCourses[i].id);
                while(listOfCourses[i].id.size() && listOfCourses[i].id.back() != '-') listOfCourses[i].id.pop_back();
                listOfCourses[i].id.pop_back(); 
                getline(fin, listOfCourses[i].name);
                getline(fin, listOfCourses[i].Class);
                getline(fin, listOfCourses[i].teacher);
                fin >> listOfCourses[i].credit;
                fin >> listOfCourses[i].maxStudent;
                getline(fin, listOfCourses[i].dayOfWeek);
                getline(fin, listOfCourses[i].session);
                fin.close();
                //get score
                fin.open(pathToCourse + "Score/" + studentID + ".txt");
                if (!fin.is_open()) continue;
                fin >> scores[i].other;
                fin >> scores[i].midterm;
                fin >> scores[i].finals;
                fin >> scores[i].total;
                fin.close();
                ++i;
                // cout << listOfCourses[i].name << '\n';
            }
        }
    }
    // cout << n << endl;

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