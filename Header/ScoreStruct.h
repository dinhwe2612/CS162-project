#pragma once
#include<iostream>
#include<iomanip>
#include"StudentStruct.h"
using namespace std;

enum SemeState { FALL = 1, SUMMER = 2, AUTUMN = 3 };

struct Scoreboard {
	string studentID, lastname, firstname, course;
	float total, finals, midterm, other;
};

//void exportStudentList(string path, Student* stu, int& numberOf_stu);
//void importScoreboard(string path, Scoreboard* s, int& );
void importScoreboard(Scoreboard* s, string course_name, int& n);

//void save_Each_Student(Scoreboard* s, int semes_state, string this_year, int n);
//int getNumberOf(string dir);

//void saveScoreOfStudent(Scoreboard s, int semes_state, string this_year);
//void write_Score(Scoreboard s, SemeState se, string this_year);
//void viewScoreboard(Scoreboard* &s, string course_name, int &N);
bool checkDirectory(ofstream& fout, string path);
void create_StudentResult_File();
void create_StudentID_CSVFile(string studentID);
void viewScoreboards(Scoreboard* s, string course_name, int N);