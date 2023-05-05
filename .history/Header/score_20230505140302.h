// this is a recommendation to follow, details can be changed depending on how you want your code to be. (e.g. change the format of the files)
// regardless, the requirements for each functions need to be satisfied.
#ifndef score_h
#define score_h
#include <string>

using namespace std;

struct ScoreBoard {
    string studentid, firstname, lastname;
<<<<<<< HEAD
    float total = -1, finals = -1, midterm = -1, other = -1;
=======
    float total=-1, finals=-1, midterm=-1, other=-1;
>>>>>>> 37f795d6fb21a73447f2fd26e7faccab6b2a77b5
}; // similar to Scoreboard in scoreStruct.h, but without string course

bool exportCourseStudentList(string destination, string schoolYear, string semester, string course);
// function returns true if succeed, else return false
// function recieves an argument for the export csv file destination
// a list of student ids of students enrolled in a course is stored in Student_ID_data.txt in its directory,
// for example Data/SchoolYear/2022-2023/Summer/CS162-22TT2/Student_ID_data.txt. (each id is on a seperated line)
// the export file needs to contain all information about the students in the course, including
// student id, first name, last name, class, gender, dob and social id. those information is stored in
// Data/Student/<student id>.txt, each piece of info on a line, follow the order as aforementioned.(0/1/2 represents male/female/other)
// sample format for csv file:
// 1,22125000,Van A,Nguyen,22TT1,0,01/01/2004,123456789098
// 2,22125001,Thi B,Le,22TT1,1,02/01/2004,123456789097

bool importCourseScoreBoard(string path, string schoolyear, string semester, string course);
// function returns true if succeed, else return false
// function recieves an argument for the import csv file path
// for the ease of accessing, each student's scores are stored in Data/SchoolYear/<school year>/<semester>/<course>/Score/<student id>.txt
// for example Data/SchoolYear/2022-2023/Summer/CS162-22TT2/Score/22125000.txt
// a score file of a course of a student only contains 4 values on 4 lines representing Total Mark, Final Mark, Midterm Mark, and Other Mark.

bool viewCourseScoreBoard(ScoreBoard*& scoreBoard, int& n, string schoolYear, string semester, string course);
// function returns true if succeed, else return false
// return back to the caller an array of Scoreboards and its size through n 
// (n is the size of the dynamic array of scoreBoard, it is recommended to set n = 0 before doing any relating operation since n may store a trash value)

bool updateStudentResult(ScoreBoard& studentScore, ScoreBoard modifiedScore, string schoolYear, string semester, string course);
// function returns true if succeed, else return false
// the caller will pass in an existing Scoreboard of a student and a modified one. Change the origin one to match
// the modified version and save those changes to the database

// bool viewClassScoreBoard()
// for this function i don't know what function prototype should i give you. the task is pretty complex, so it's up to you to solve
// just make sure that you return an array of something and its size so that the caller can use it to display to the UI
// this feature requires the the TOTAL (T.A has clarified this on facebook) marks of courses that a student studied, the gpa of a semester(s) and the overall gpa
// gpa of a semester is calculated by sum of all total marks of all the courses studied in that semester, each mutiply by the course's credit count,
// divided by the total number of credits. for example, if a student earned 10, 9.5 and 9 in 3 courses which have 3, 4, 5 credits respectively,
// the gpa of the semester will be (10*3 + 9.5*4 + 9*5)/(3 + 4 + 5)
// the overall gpa is the average of all studied semesters.


// bool viewClassOverallIn1Year(ScoreBoard*& s, string schoolYear, string Class);
// bool viewClassScoreBoardIn1Semester(ScoreBoard*& s, string schoolYear, string semester, string Class);
bool viewClassOverallIn1Year(ScoreBoard*& s, float *&scores, int &row, string schoolYear, string Class);
bool viewClassScoreBoardIn1Semester(ScoreBoard*& s, float *&scores, string *&courses, int &row, int &column, string schoolYear, string semester, string Class);
// two functions above can only view scoreboard of a class in one year
bool viewStudentScoreboard(ScoreBoard *&s, string *&courses, float *&gpa, string studentid, string schoolYear, int &n);
#endif