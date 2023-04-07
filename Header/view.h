#include <iostream>
#include <filesystem>
#include <fstream>
#include <string>
#include <algorithm>
#include "../Header/StudentStruct.h"

using namespace std;

bool viewClasses(string*& classes, int & n, string schoolYear);
bool viewStudentInClass (string Class, string schoolYear, Student*& Students, int& n);
bool viewCourses(string schoolYear, string semester);
bool viewStudentInCourse(string schoolYear, string semester, string course);
bool viewCoursesOfStudent(string id, string schoolYear, string semester);
bool viewSchoolYear(string*& schoolYears, int& n);