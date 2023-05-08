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

bool ViewCoursesStudent(Student &stu, ACourse *&course, ScoreBoard *&scores, int &n);
bool ViewSchoolYearStudent(Student &stu, string *&schoolYear, int &n);