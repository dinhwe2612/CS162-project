#include <iostream>
#include <filesystem>
#include <fstream>
#include <string>
#include <algorithm>
#include "../Header/CourseStruct.h"
#include "../Header/SemesterStruct.h"
#include "../Header/StudentStruct.h"

using namespace std;

bool viewClasses(string*& classes, int & n, string schoolYear);
bool viewStudentInClass (string Class, string schoolYear, Student*& Students, int& n);
bool viewCourses(string schoolYear, string semester, ACourse*& ListOfCourses, int& n);
bool viewStudentInCourse(string schoolYear, string semester, ACourse course, Student*& students, int& n);
bool viewSchoolYear(string*& schoolYears, int& n);
bool viewSemester (string schoolYear, string*& semesters, int& n);