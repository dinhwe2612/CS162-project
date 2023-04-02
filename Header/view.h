#include <iostream>
#include <filesystem>
#include <fstream>
#include <string>

using namespace std;

bool viewClasses(string schoolYear);
bool viewStudentInClass (string Class, string schoolYear);
bool viewCourses(string schoolYear, string semester);
bool viewStudentInCourse(string schoolYear, string semester, string course);
bool viewCoursesOfStudent(string id, string schoolYear, string semester);