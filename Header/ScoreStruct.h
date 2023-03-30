#pragma once
#include<iostream>
#include<iomanip>
#include<sstream>
#include<sys/stat.h>
#include"StudentStruct.h"
using namespace std;

enum SemeState { FALL = 1, SUMMER = 2, AUTUMN = 3 };

struct Scoreboard {
	string studentID, lastname, firstname, course;
	float total, finals, midterm, other;
};

//These functions was offered to 
//import the scoreboard of a course
//view the scoreboard of a course
void importScoreboard(Scoreboard* s, string course_name, int& n);
void viewScoreboard(Scoreboard* s, string course_name, int N);
void staff_Views_Scoreboard(string &schoolyear, string &semester, string &course);

bool isPathExist(const string& path);
int getNumberOf(string dir);

void loadCourseInfo(string* courseId, string schoolyear, string semester, string path);
void printCourseID(string* id, int n);
void inputShoolYear(string& schoolyear, string &path);
void inputSemester(string& semester, string &path);
void inputCourse(string& course_id, string* courseID, int numberof_id, string &path);