#pragma once
#include <iostream>
#include <fstream>
#include <filesystem>
#include <algorithm>
#include <string>
#include "../Header/StudentStruct.h"

using namespace std;

bool createSchoolYear(string *&ListOfSchoolYear, int &n, string schoolYear);
bool createClass(string*& ListOfClass, int& n, string Class, string schoolYear);
bool addStudentToClass(Student*& listOfStudent, int& n, Student student, string schoolYear, string Class);
void importStudent(Student*& listOfStudent, int& n, string dir, string schoolYear, string Class);