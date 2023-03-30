#include"StudentStruct.h"
#include"StaffFunc.h"
#include"ScoreStruct.h"
#include<fstream>

//The maximum number of students in the course
#define MAX_NO_STUDENTS 50

//Import the result of a course from a csv file
void importScoreboard(Scoreboard* s, string course_name, int& n) {
	//locale loc(std::locale(), new std::codecvt_utf8<wchar_t>);
	ifstream ifs;
	ifs.open("../Data/" + course_name + ".csv");
	//string no = "";
	//int i = 0;
	string ignore_line = "";
	getline(ifs, ignore_line, '\n');

	string no = "";
	string student_id = "";
	string student_fn = "";
	string student_ln = "";
	string total = "", finals = "", midterm = "", other = "";
	int i = 0;
	while (!ifs.eof()) {
		getline(ifs, no, ',');
		getline(ifs, student_id, ',');
		getline(ifs, student_ln, ',');
		getline(ifs, student_fn, ',');
		getline(ifs, total, ',');
		getline(ifs, finals, ',');
		getline(ifs, midterm, ',');
		getline(ifs, other, '\n');
		ifs.ignore();

		s[i].studentID = student_id;
		s[i].lastname = student_ln;
		s[i].firstname = student_fn;
		s[i].total = stof(total);
		s[i].finals = stof(finals);
		s[i].midterm = stof(midterm);
		s[i].other = stof(other);
		//saveScoreOfStudent(s[i], semes_state, this_year);
		i++;
	}
	n = i;
	ifs.close();
}

void viewScoreboard(Scoreboard* s, string course_name, int N) {
	for (int i = 0; i < N; i++) {
		cout << i + 1 << "\t";
		cout << s[i].studentID << "\t";
		cout << left << setw(20) << s[i].lastname;
		cout << left << setw(10) << s[i].firstname << "\t";
		cout << s[i].total << "\t";
		cout << s[i].finals << "\t";
		cout << s[i].midterm << "\t";
		cout << s[i].other << endl;
	}
}

void staff_Views_Score() {
	string course;
	cout << "Which course do you want to view score? Please, enter the course: ";
	getline(cin, course, '\n');
	int n = 0;
	Scoreboard* s = new Scoreboard[MAX_NO_STUDENTS];
	importScoreboard(s, course, n);
	viewScoreboard(s, course, n);
	delete[] s;
}

int main() {
	create_StudentResult_File();
	staff_Views_Score();
	return 0;
}

