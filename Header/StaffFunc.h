#pragma once
#include <iostream> 
#include <string.h>

using namespace std;

void Creat_A_Semester();

void AddCourse(string address);
void Course_Information(string txtaddress);
void View_ListofCourses(string address);
void Update_CourseInformation(string address);

void AddStudenttoCourse();
void RemoveStudentfromCourse();

//void Display();
string* Read_File(string fileaddress);
void Update_File(string fileaddress, string* information);
void MultiChoices();
