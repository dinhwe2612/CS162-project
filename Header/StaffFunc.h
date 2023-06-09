#pragma once
#include <iostream> 
#include <string.h>
#include <sstream>
#include <fstream>
#include <algorithm>

using namespace std;

void Creat_A_Semester();

void AddCourse(string address);
void Course_Information(string txtaddress);
void View_ListofCourses(string address);
void Update_CourseInformation(string address);

void Add1StudenttoCourse(string studentid, string courseaddress);
void Remove1StudentfromCourse(string studentid, string courseaddress);
void AddClasstoCourse_CSV(string fileaddress, string courseaddress);


void AddDatatoStudentFile (string id, string schoolyear, string semester, string courseid, string* data);
void RemoveDatafromStudentFile (string id, string schoolyear, string semester, string courseid);

void DeleteACourse(string courseid_coursename_address);

//void Display();
string* Read_File(string fileaddress);
void Update_File(string fileaddress, string* information);
void MultiChoices();
