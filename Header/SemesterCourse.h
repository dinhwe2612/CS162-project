#ifndef SemesterCourse_h
#define SemesterCourse_h

#include <iostream>
#include <fstream>
#include <string.h>
#include <string>
#include <sstream>
#include "CourseStruct.h"
#include "SemesterStruct.h"
#include <filesystem>
#ifdef _WIN32
    #include <direct.h>
#endif

bool CreateSemester(ASemester semester, string*& ListOfSemester, int& n);
bool AddCourse(string schoolYear, string semester, ACourse course, ACourse*& ListOfCourse, int& n);
bool Update_CourseInformation(ACourse& course);
bool AddClasstoCourse_CSV(string fileaddresss);
bool Add1StudenttoCourse(string studentid, ACourse course);
bool Remove1StudentfromCourse(string studentid, ACourse course);
bool DeleteACourse(ACourse course, ACourse*& courses, int& n);

#endif