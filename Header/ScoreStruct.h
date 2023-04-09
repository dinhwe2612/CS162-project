#pragma once
#include<iostream>
#include<iomanip>
#include<sstream>
#include<sys/stat.h>
#include"../Header/StudentStruct.h"
using namespace std;

enum SemeState { FALL = 1, SUMMER = 2, AUTUMN = 3 };

struct Scoreboard {
	string studentID, lastname, firstname, course;
	float total, finals, midterm, other;
};

//These functions was offered to
//19.export a list of students in a course to a csv file (has not been finished yet)
//20.import the scoreboard of a course
//21.view the scoreboard of a course
void importScoreboard(Scoreboard* s, string course_name, int& n);
//void viewScoreboard(Scoreboard* s, string course_name, int N);
void viewScoreboard(Scoreboard* s, string course_name, int N);

bool isPathExist(const string& path);
int getNumberOf(string dir);
//string convertIntToString(int a);
//int getCurrentYear();
//string getCurrentSemester(string& path);

void loadCourseInfo(string* courseId, string schoolyear, string semester, string path);
void printCourseID(string* id, int n);
void inputShoolYear(string& schoolyear, string &path, bool &type);
void inputSemester(string& semester, string &path, bool &type);
void inputCourse(string& course_id, string* courseID, int numberof_id, string &path, bool &type);

//Student Result files, importing functions
void create_StudentID_TXTFile(string studentID);
void write_Score(Scoreboard s, string semester, string schoolyear);
void saveScoreOf1Stu(Scoreboard* s, string schoolyear, string semester, int n);
void importOption(string schoolyear, string semester, string course);

//Staff export a list of students in a course to a csv file using this function
void exportStuScoreListToCsv(string& schoolyear, string& semester, string& course); 
//To view the scoreboard of a course
void staff_Views_Scoreboard(string &schoolyear, string &semester, string &course);
