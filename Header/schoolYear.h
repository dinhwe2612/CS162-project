#pragma once
#include <iostream>
#include <fstream>
#include <filesystem>
#include <algorithm>
#include "../Header/StudentStruct.h"

using namespace std;

bool createSchoolYear(string *&ListOfSchoolYear, int &n, string schoolYear);
bool createClass(string*& ListOfClass, int& n, string Class, string schoolYear);
bool addStudent(Student student, string schoolYear, string Class);