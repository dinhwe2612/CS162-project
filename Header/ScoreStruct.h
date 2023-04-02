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
//19.export a list of students in a course to a csv file 
//20.import the scoreboard of a course
//21.view the scoreboard of a course
void importScoreboard(Scoreboard* s, string course_name, int& n);
void viewScoreboard(Scoreboard* s, string course_name, int N);

bool isPathExist(const string& path);
int getNumberOf(string dir);
string convertIntToString(int a);
int getCurrentYear();
string getCurrentSemester(string& path);

void loadCourseInfo(string* courseId, string schoolyear, string semester, string path);
void printCourseID(string* id, int n);
void inputShoolYear(string& schoolyear, string &path, bool &type);
void inputSemester(string& semester, string &path, bool &type);
void inputCourse(string& course_id, string* courseID, int numberof_id, string &path, bool &type);

void loadStudentListOf1Course(string& path, Scoreboard* s, int& n);
void exportStuScoreList(string pathToScore, string course, Scoreboard* s, int& numberOf_stu);

//Staff export a list of students in a course to a csv file using this function
void exportStuScoreListToCsv(string& schoolyear, string& semester, string& course); 
//To view the scoreboard of a course
void staff_Views_Scoreboard(string &schoolyear, string &semester, string &course);
