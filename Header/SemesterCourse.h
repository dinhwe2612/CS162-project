#ifndef SemesterCourse_h
#define SemesterCourse_h

#include <iostream>
#include <fstream>
#include <string.h>
#include <string>
#include <sstream>
#include "CourseStruct.h"
#include "SemesterStruct.h"
#include <algorithm>
#ifdef _WIN32
    #include <direct.h>
#endif

bool CreateSemester(ASemester semester, string*& ListOfSemester, int& n);
bool AddCourse(string schoolYear, string semester, ACourse course, ACourse*& ListOfCourse, int& n);
bool Update_CourseInformation(ACourse& course, string schoolYear, string semester);
bool AddClasstoCourse_CSV(string fileaddress, ACourse course, string schoolYear, string semester);
bool Add1StudenttoCourse(string studentid, ACourse course, string schoolYear, string semester);
bool Remove1StudentfromCourse(string studentid, ACourse course, string schoolYear, string semester);
bool DeleteACourse(string schoolYear, string semester, ACourse course, ACourse*& courses, int& n);


#endif