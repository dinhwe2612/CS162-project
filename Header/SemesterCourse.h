#ifndef SemesterCourse_h
#define SemesterCourse_h

#include <iostream>
#include <fstream>
#include <string.h>
#include <string>
#include <sstream>
#include "CourseStruct.h"
#include "SemesterStruct.h"
#ifdef _WIN32
    #include <direct.h>
#endif

bool CreateSemester(ASemester semester, string*& ListOfSemester, int& n);
bool AddCourse(string schoolYear, string semester, ACourse course, ACourse* ListOfCourse, int& n);

#endif