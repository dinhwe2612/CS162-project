#pragma once
#include <iostream>
#include <filesystem>
#include <fstream>
#include <string>
#include <algorithm>
#include "../Header/StudentStruct.h"
#include "../Header/CourseStruct.h"
#include "../Header/ScoreStruct.h"

using namespace std;

bool LoadDataStudent(Student &stu, string username);
bool ViewCoursesStudent(string schoolYear, string semester, string studentID, ACourse *&course, ScoreBoard *&scores, int &n);
bool ViewSchoolYearStudent(Student &stu, string *&schoolYear, int &n);
bool ViewAllCoursesStudent(string studentID, ACourse *&listOfCourses, ScoreBoard *&scores, int &n);
bool viewScoreBoardInSchoolYear(string schoolYear, string studentID, ACourse* &listOfCourse, ScoreBoard* &scores, int &n);
bool viewScoreBoardAll(Student &stu, ACourse* &listOfCourse, ScoreBoard* &scores, int &n);
bool viewDropDownList(string studentID, string *&listOfDropDown, int &n);