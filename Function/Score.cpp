#include"../Header/StudentStruct.h"
#include"../Header/StaffFunc.h"
#include"../Header/ScoreStruct.h"
#include "../Header/StudentFunc.h"
#include<fstream>
#include "../Header/score.h"

//  string* Read_File(string fileaddress)
//  {
//      ifstream in;
//      string* inf = new string[1000];
//      in.open(fileaddress.c_str());
//      string str;
//      int i = 1;
//      while (getline(in, str))
//      {
//          inf[i] = str;
//          i++;
//      }
//      inf[0] = to_string(i-1); 
//      in.close();
//      return inf; 
//  }

bool isValid(string s) {
	bool valid = false;
	int counter = 0;
	int n = strlen(s.c_str());
	if ((s[0] < '0' || s[0] > '9') || (s[n - 1] < '0' || s[n - 1]>'9')) {
		if (s != "-1") valid = false;
	}
	else {
		for (int i = 0; i < s.size(); i++) {
			if ((s[i] >= '0' && s[i] <= '9') || s[i] == '.') {
				valid = true;
				if (s[i] == '.')
					counter++;
			}
			else {
				valid = false;
				break;
			}
		}
		if (counter >= 2)
			valid = false;
	}

	if (n==2) {
		if(s[0]=='-' && s[1]=='1'){
		valid = true;
		}
	}
	return valid;
}

void loadStudentID(Student *&s, string path, int n) {
	ifstream ifs;
	ifs.open(path.c_str());
	int i = 0;
	while (!ifs.eof()) {
		ifs >> s[i].studentID;
		i++;
		if (i == n){
			break;
		}
	}
	ifs.close();
}

void loadStudentInfo(Student &s, string path) {
	ifstream ifs;
	ifs.open(path.c_str());
	string gender = "";
	getline(ifs, s.studentID);
	getline(ifs, s.firstName);
	getline(ifs, s.lastName);
	getline(ifs, s.Class);
	getline(ifs, gender);
	getline(ifs, s.DOB);
	getline(ifs, s.socialID);
	s.gender = stoi(gender);
	ifs.close();
}

int getNumberOf(string dir) {
	ifstream in;
	in.open(dir);
	string w;
	int n = 0;
	while (!in.eof()) {
		getline(in, w);
		//in.ignore(256, '\n');
		//in.ignore();
		in.ignore();
		if (w != "") n++;
	}
	in.close();
	return n;
} 

void loadScore1Student(ScoreBoard& s, string path) {
	ifstream ifs;
	ifs.open(path);
	ifs >> s.total;
	ifs >> s.finals;
	ifs >> s.midterm;
	ifs >> s.other;
	ifs.close();
}

void loadScoreboard(ScoreBoard*& s, string schoolyear, string semester, string course_name, int& n, string path) {
	//locale loc(std::locale(), new std::codecvt_utf8<wchar_t>);
	ifstream ifs;
	ifs.open(path.c_str());

	string ignore_line = "";
	getline(ifs, ignore_line, '\n');

	string no = "";
	string student_id = "";
	string student_fn = "";
	string student_ln = "";
	string Class = "", gender = "", DOB = "", socialID = "";
	string total = "", finals = "", midterm = "", other = "";
	int i = 0, j = 0;
	bool v1, v2, v3, v4;
	while (!ifs.eof()) {
		getline(ifs, no, ',');
		getline(ifs, student_id, ',');
		if (student_id == "")
			break;
		getline(ifs, student_ln, ',');
		getline(ifs, student_fn, ',');
		getline(ifs, Class, ',');
		getline(ifs, gender, ',');
		getline(ifs, DOB, ',');
		getline(ifs, socialID, ',');
		getline(ifs, total, ',');
		getline(ifs, finals, ',');
		getline(ifs, midterm, ',');
		getline(ifs, other);
		v1 = isValid(total);
		v2 = isValid(finals);
		v3 = isValid(midterm);
		v4 = isValid(other);
		try {
			if (v1 && v2 && v3 && v4) {
				s[i].studentid = student_id;
				s[i].lastname = student_ln;
				s[i].firstname = student_fn;
				s[i].total = stof(total);
				s[i].finals = stof(finals);
				s[i].midterm = stof(midterm);
				s[i].other = stof(other);
				i++;
			}
			else
				throw(505);
		}
		catch (...) {
			s[i].studentid = student_id;
			s[i].firstname = student_fn;
			s[i].lastname = student_ln;
			if (v1) s[i].total = stof(total);
			if (v2)s[i].finals = stof(finals);
			if (v3)s[i].midterm = stof(midterm);
			if (v4)s[i].other = stof(other);
			i++;
		}
		if (i == n)
			break;
	}
	n = i;
	ifs.close();
}


bool exportCourseStudentList(string destination, string schoolYear, string semester, string course) {
	ofstream ofs;
	//destination = toSchoolYear + schoolYear + '/' + semester + '/' + course;
	destination += "/";
	if (!filesystem::exists(destination))
		return false;

	
	string path = toSchoolYear + schoolYear + "/" + semester + "/" + course + "/" + "Student_ID_data.txt";
	int n = getNumberOf(path);
	Student* s = new Student[n];
	loadStudentID(s, path, n);
	for (int i = 0; i < n; i++) {
		path = toDataStudent + s[i].studentID + ".txt";
		loadStudentInfo(s[i], path);
	}

	destination += "Student_ID_data.csv";
	if (filesystem::exists(destination)) {
		int n1 = getNumberOf(destination) - 1;
		int counter = 0;
		ScoreBoard* scoreboard = new ScoreBoard[n1];
		Student* newStudent = new Student[n];
		ScoreBoard* newScore = new ScoreBoard[n];
		loadScoreboard(scoreboard, schoolYear, semester, course, n1, destination);
		for (int i = 0; i < n1; i++) {
			for (int j = 0; j < n; j++) {
				if (scoreboard[i].studentid == s[j].studentID) {
					newScore[counter] = scoreboard[i];
					newStudent[counter].studentID = scoreboard[i].studentid;
					counter++;
				}
			}
		}
		int appear = 0, index = 0;
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n1; j++) {
				if (s[i].studentID == scoreboard[j].studentid) {
					appear++;
				}
			}
			// appear=0: it does not appear in csv file
			// it is a new student
			// add to new scoreboard
			if (appear == 0) {
				newScore[counter + index].studentid = s[i].studentID;
				newStudent[counter + index].studentID = s[i].studentID;
				index++;
			}
			appear = 0;
		}
		for (int i = 0; i < n; i++) {
			path = toDataStudent + newStudent[i].studentID + ".txt";
			loadStudentInfo(newStudent[i], path);
		}

		for (int i = 0; i < n; i++) {
			path = toSchoolYear + schoolYear + "/" + semester + "/" + course + "/" + "Score/" + newScore[i].studentid + ".txt";
			if (filesystem::exists(path)) {
				loadScore1Student(newScore[i], path);
			}
		}

		remove(destination.c_str());
		ofs.open(destination.c_str());
		ofs << "No,Student ID,LastName,FirstName,Class,Gender,DOB,Social ID,Total,Finals,Midterm,Other" << "\n";
		for (int i = 0; i < n; i++) {
			ofs << i + 1 << ','
				<< newStudent[i].studentID << ','
				<< newStudent[i].lastName << ','
				<< newStudent[i].firstName << ','
				<< newStudent[i].Class << ','
				<< newStudent[i].gender << ','
				<< newStudent[i].DOB << ','
				<< newStudent[i].socialID << ','
				<< newScore[i].total << ',' << newScore[i].finals << ',' << newScore[i].midterm << ',' << newScore[i].other << '\n';
		}

		delete[] scoreboard;
		delete[] newScore;
		delete[] newStudent;
	}
	else {
		ofs.open(destination.c_str());
		ofs << "No,Student ID,LastName,FirstName,Class,Gender,DOB,Social ID,Total,Finals,Midterm,Other" << "\n";
		for (int i = 0; i < n; i++) {
			ofs << i + 1 << ','
				<< s[i].studentID << ','
				<< s[i].lastName << ','
				<< s[i].firstName << ','
				<< s[i].Class << ','
				<< s[i].gender << ','
				<< s[i].DOB << ','
				<< s[i].socialID << ','
				<< -1 << ',' << -1 << ',' << -1 << ',' << -1 << '\n';
		}
	}
	delete[] s;
	ofs.close();
	return true;
}

void write_Score(ScoreBoard s, string semester, string schoolyear, string course) {
	ofstream ofs;
	string path = toSchoolYear + schoolyear + "/" + semester + "/" + course + "/Score" + "/" + s.studentid + ".txt";
	//bool is = isPathExist(path);
	ofs.open(path, ios::app | ios::ate);
	ofs << s.total << '\n' << s.finals << '\n' << s.midterm << '\n' << s.other;
	ofs.close();
}
void saveScoreOf1Stu(ScoreBoard* s, string schoolyear, string semester, string course, int n) {//called after importing the scoreboard successfully
	for (int i = 0; i < n; i++) {
		write_Score(s[i], semester, schoolyear, course);
	}
}
void saveScore(string path, ScoreBoard* s, int n, string schoolyear, string semester, string course) {
	ofstream ofs;
	ofs.open(path, ios::app | ios::ate);
	for (int i = 0; i < n; i++) {
		ofs << s[i].studentid << "," << s[i].lastname << ',' << s[i].firstname << ',' << s[i].total << ',' << s[i].finals << ',' << s[i].midterm << ',' << s[i].other << '\n';
	}
	ofs.close();
	//saveScoreOf1Stu(s, schoolyear, semester, course, n);
}


void checkData(string path, string schoolyear, string semester, string course) {
	// path += "/Student_ID_data.csv";
	//string path_out = ToSchoolYear + schoolyear + '/' + semester + '/' + course + "/Score" + '/' + course + ".txt";
	int n = 0, n1=0;

	// take the number of students from a csv file that has been imported before
	n = getNumberOf(path) - 1;
	//n2 = getNumberOf(path_out);
	ScoreBoard* s = new ScoreBoard[n];
	ScoreBoard* s1 = new ScoreBoard[n];
	//ScoreBoard* invalid = new ScoreBoard[n];
	loadScoreboard(s, schoolyear, semester, course, n, path);
	string pathToFolder = toSchoolYear + schoolyear + '/' + semester + '/' + course + "/Score/";
	string pathToFile = "";
	for (int i = 0; i < n; i++) {
		pathToFile = pathToFolder + s[i].studentid + ".txt";
		if (filesystem::exists(pathToFile)) {
			loadScore1Student(s1[i], pathToFile);
			if (s[i].total != s1[i].total || s[i].finals != s1[i].finals ||
				s[i].midterm != s1[i].midterm || s[i].other != s1[i].other) {
				s1[i] = s[i];
				remove(pathToFile.c_str());
				write_Score(s1[i], semester, schoolyear, course);
			}
		}
		else {
			write_Score(s[i], semester, schoolyear, course);
		}
	}
	delete[] s;
	delete[] s1;
	//delete[] invalid;
}
bool importCourseScoreBoard(string path, string schoolyear, string semester, string course) {
	// path += toSchoolYear + schoolyear + "/" + semester + "/" + course;
	cout << endl << path << endl;
	if (!filesystem::exists(path))
		return false;
	string toScore = toSchoolYear + schoolyear + "/" + semester + "/" + course;
	toScore += "/Score";
	// cout << toScore << endl;
	if (!filesystem::exists(toScore)) {
		filesystem::create_directory(toScore);
		cout << "Created" << endl;
	}
	checkData(path, schoolyear, semester, course);
	return true;
}

void viewScoreboard(ScoreBoard* s, int n) {
	cout << "No" << '\t'
		<< left << setw(15) << "Student ID"
		<< left << setw(20) << "Last Name"
		<< left << setw(20) << "First Name"
		<< left << setw(9) << "Total" << left << setw(9) << "Final" << left << setw(9) << "Midterm" << left << setw(9) << "Other" << endl;
	//cin.ignore();
	for (int i = 0; i < n; i++) {
		cout << i + 1 << "\t";
		cout << left << setw(15) << s[i].studentid;
		cout << left << setw(20) << s[i].lastname;
		cout << left << setw(20) << s[i].firstname;
		cout << left << setw(9);
		if (s[i].total >= 0 && s[i].total <= 10) {
			cout << s[i].total;
		}
		else
			cout << " ";
		cout << left << setw(9);
		if (s[i].finals >= 0 && s[i].finals <= 10) {
			cout << s[i].finals;
		}
		else
			cout << " ";
		cout << left << setw(9);
		if (s[i].midterm >= 0 && s[i].midterm <= 10) {
			cout << s[i].midterm;
		}
		else
			cout << " ";
		cout << left << setw(9);
		if (s[i].other >= 0 && s[i].other <= 10) {
			cout << s[i].other;
		}
		else
			cout << " ";
		cout << endl;
	}
}

bool viewCourseScoreBoard(ScoreBoard*& scoreBoard, int& n, string schoolYear, string semester, string course) {
	//string path = ToSchoolYear + schoolYear + '/' + semester + '/' + course + "/Score" + '/' + course + ".txt";
	string path = toSchoolYear + schoolYear + "/" + semester + "/" + course + "/Student_ID_data.txt";

	if (!filesystem::exists(path))
		return false;

	n = getNumberOf(path);
	scoreBoard = new ScoreBoard[n];
	Student *s = new Student[n];
	loadStudentID(s, path, n);
	for (int i = 0; i < n; i++) {
		path = toDataStudent + s[i].studentID + ".txt";
		loadStudentInfo(s[i], path);
		scoreBoard[i].studentid = s[i].studentID;
		scoreBoard[i].firstname = s[i].firstName;
		scoreBoard[i].lastname = s[i].lastName;
	}
	
	path = toSchoolYear + schoolYear + '/' + semester + '/' + course + "/Score/";
	for (int i = 0; i < n; i++) {
		string toStuFile = path + s[i].studentID + ".txt";
		if (filesystem::exists(toStuFile)) {
			loadScore1Student(scoreBoard[i], toStuFile);
		}
	}
	viewScoreboard(scoreBoard, n);
	return true;
}

bool updateStudentResult(ScoreBoard& studentScore, ScoreBoard modifiedScore, string schoolYear, string semester, string course) {
	string path = toSchoolYear + schoolYear + '/' + semester + '/' + course + "/Score" + '/' + studentScore.studentid + ".txt";
	if (!filesystem::exists(path) || studentScore.studentid != modifiedScore.studentid)
		return false;
	string* info = Read_File(path);
	float *a = new float[4] { modifiedScore.total, modifiedScore.finals, modifiedScore.midterm, modifiedScore.other };
	int i = 0;
	while (i < 4) {
		if (a[i] >= 0 && a[i] <= 10) {
			info[i + 1] = to_string(a[i]);
		}
		i++;
	}
	//Update_File(path, info);
	remove(path.c_str());
	//write_Score(studentScore, semester, schoolYear, course);
	studentScore.total = atof(info[1].c_str());
	studentScore.finals = atof(info[2].c_str());
	studentScore.midterm = atof(info[3].c_str());
	studentScore.other = atof(info[4].c_str());
	path = toDataStudent + studentScore.studentid + ".txt";
	Student s;
	loadStudentInfo(s, path);
	studentScore.lastname = s.lastName;
	studentScore.firstname = s.firstName;
	write_Score(studentScore, semester, schoolYear, course);

	delete[] a;
	//cout << "Update successfully!" << endl;
	return true;
}

void load1Class(ScoreBoard*& s, string path, int n) {
	ifstream ifs;
	ifs.open(path.c_str());
	string no = "";
	int i = 0;
	while (!ifs.eof()) {
		getline(ifs, no, ' ');
		getline(ifs, s[i].studentid);
		i++;
		if (i == n)
			break;
	}
	ifs.close();
}

string* loadCourseID(string path, int n) {
	ifstream in;
	path += "/Semester_Info.txt";
	in.open(path);

	string line1 = "", line2 = "", line3 = "", line4 = "";
	getline(in, line1, '\n');
	getline(in, line2, '\n');
	getline(in, line3, '\n');
	getline(in, line4, '\n');

	string id = "";
	int i = 0;
	string *info = new string[n];
	while (!in.eof()) {
		getline(in, id);
		in.ignore();
		info[i] = id;
		i++;
	}
	in.close();
	return info;
}

void loadCredit(string path, int &credit) {
	path += "/Course_Info.txt";
	ifstream ifs;
	ifs.open(path);
	string info = "";
	int i = 0;
	while (getline(ifs, info)) {
		i++;
		if (i == 5) {
			credit = atoi(info.c_str());
			break;
		}
	}
	ifs.close();
}
float** gpaOf1Semester(float** a, int *credits, int row, int column) {
	float gpa = 0;
	int times = 0;
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < column; j++) {
			if (a[i][j] != -1) {
				gpa += (a[i][j] * credits[j]);
				times += credits[j];
			}
		}
		if (times > 0) {
			a[i][column] = gpa / times;
		}
		else {
			a[i][column] = -1;
		}
		gpa = 0;
		times = 0;
	}
	return a;
}

float** getClassGPAIn1Semester(ScoreBoard*& classScore, string schoolYear, string semester, string Class, int& column, int& row) {
	string path = toSchoolYear + schoolYear + "/" + semester;

	//return false if semester does not exist
	//if (!isPathExist(path))
		//return false;

	path = toSchoolYear + schoolYear + "/Classes/" + Class + ".txt";
	//return false if class does not exist
	//if (!isPathExist(path))
		//return false;

	//Take a list of student id in a class
	row = getNumberOf(path);
	classScore = new ScoreBoard[row];
	load1Class(classScore, path, row);
	path = toSchoolYear + schoolYear + "/" + semester;
	column = getNumberOf(path + "/Semester_Info.txt") - 4;

	//Take courses in this semester
	string* courses;
	courses = loadCourseID(path, column);

	//Take credit of courses
	int* credits = new int[column];
	string pathToCredit;
	for (int i = 0; i < column; i++) {
		pathToCredit = path + '/' + courses[i];
		loadCredit(pathToCredit, credits[i]);
	}

	//Take total of each student in a class
	string pathToScore;
	float **score = new float* [row];
	for (int i = 0; i < row; i++) {
		score[i] = new float[column + 1];
	}
	for (int i = 0; i < column; i++) {
		pathToScore = path + '/' + courses[i] + "/Score/";
		for (int j = 0; j < row; j++) {
			pathToScore += classScore[j].studentid + ".txt";
			if (filesystem::exists(pathToScore)) {
				loadScore1Student(classScore[j], pathToScore);
				score[j][i] = classScore[j].total;
			}
			else {
				score[j][i] = -1;
			}
			pathToScore = path + '/' + courses[i] + "/Score/";
		}
	}
	//calculate gpa of each student in one semester
	score = gpaOf1Semester(score, credits, row, column);
	delete[] courses;
	return score;
}

float** getClassOverallGPA(ScoreBoard*& s, string schoolYear, string Class, int& row, int& column) {
	string path = toSchoolYear + schoolYear + "/Classes/" + Class + ".txt";
	float** score = nullptr;
	int times = 0;
	row = getNumberOf(path.c_str());
	float **gpa = new float* [row];
	for (int i = 0; i < row; i++)
		gpa[i] = new float[4];
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < 4; j++) {
			gpa[i][j] = -1;
		}
	}
	string semester = "Spring";
	path = toSchoolYear + schoolYear + "/" + semester;
	if (filesystem::exists(path)) {
		score = getClassGPAIn1Semester(s, schoolYear, semester, Class, column, row);
		for (int i = 0; i < row; i++) {
			gpa[i][0] = score[i][column];
		}
		times++;
	}
	semester = "Summer";
	path = toSchoolYear + schoolYear + "/" + semester;
	if (filesystem::exists(path)) {
		score = getClassGPAIn1Semester(s, schoolYear, semester, Class, column, row);
		for (int i = 0; i < row; i++) {
			gpa[i][1] = score[i][column];
		}
		times++;
	}
	semester = "Autumn";
	path = toSchoolYear + schoolYear + "/" + semester;
	if (filesystem::exists(path)) {
		score = getClassGPAIn1Semester(s, schoolYear, semester, Class, column, row);
		for (int i = 0; i < row; i++) {
			gpa[i][2] = score[i][column];
		}
		times++;
	}
	for (int i = 0; i < row; i++)
		delete[] score[i];
	delete[] score;
	float sum = 0;
	bool empty = false;
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < 3; j++) {
			if (gpa[i][j] >= 0 && gpa[i][j] <= 10) {
				sum += gpa[i][j];
				empty = true;
			}
		}
		if (empty) {
			sum /= times;
			gpa[i][3] = sum;
			sum = 0;
			empty = false;
		}
		else {
			gpa[i][3] = -1;
		}
	}
	return gpa;
}

bool viewClassOverallIn1Year(ScoreBoard*& s, float *&scores, int &row, string schoolYear, string Class) {
 	string path = toSchoolYear + schoolYear;
 	if (!filesystem::exists(path))
 		return false;
 	path += "/Classes/" + Class + ".txt";
 	if (!filesystem::exists(path))
 		return false;
 	int column = 0;
 	float** scores1 = getClassOverallGPA(s, schoolYear, Class, row, column);
 	scores = new float[row * 4];
 	for (int i = 0; i < row; i++) {
 		for (int j = 0; j < 4; j++) {
 			scores[i * 4 + j] = scores1[i][j];
 		}
 	}
 	for (int i = 0; i < row; i++) {
 		delete[] scores1[i];
 	}
 	delete[] scores1;
 	return true;
}

// bool viewClassOverallIn1Year(ScoreBoard*& s, string schoolYear, string Class) {
// 	string path = toSchoolYear + schoolYear;
// 	if (!filesystem::exists(path))
// 		return false;
// 	path += "/Classes/" + Class + ".txt";
// 	if (!filesystem::exists(path))
// 		return false;
// 	int row = 0, column = 0;
// 	float** scores = getClassOverallGPA(s, schoolYear, Class, row, column);
// 	string* semester = new string[3]{ "Spring","Summer","Autumn" };
// 	cout << left << setw(10) << "Student ID" << '\t';
// 	for (int i = 0; i < 3; i++) {
// 		cout << left << setw(15) << semester[i];
// 	}
// 	cout << left << setw(15) << "GPA" << endl;
// 	for (int i = 0; i < row; i++) {
// 		cout << left << setw(10) << s[i].studentid << '\t';
// 		for (int j = 0; j < 4; j++) {
// 			cout << left << setw(15) << scores[i][j];
// 		}
// 		cout << endl;
// 	}
// 	for (int i = 0; i < row; i++) {
// 		delete[] scores[i];
// 	}
// 	delete[] scores;
// 	return true;
// }

// bool viewClassScoreBoardIn1Semester(ScoreBoard*& s, string schoolYear, string semester, string Class) {
// 	string path = toSchoolYear + schoolYear;

// 	path += "/Classes/" + Class + ".txt";
// 	//return false if class does not exist
// 	if (!filesystem::exists(path))
// 		return false;

// 	path = toSchoolYear + schoolYear + '/' + semester + "/Semester_Info.txt";
// 	int row = 0;
// 	int column = getNumberOf(path) - 4;

// 	//Take courses in this semester
// 	string *courses;
// 	path = toSchoolYear + schoolYear + '/' + semester;
// 	courses = loadCourseID(path, column);

// 	//Score of courses that students in a class studied
// 	float **scores = getClassGPAIn1Semester(s, schoolYear, semester, Class, column, row);
// 	cout << left << setw(10) << "Student ID" << '\t';
// 	for (int i = 0; i < column; i++) {
// 		cout << left << setw(15) << courses[i];
// 	}
// 	cout << left << setw(15) << "GPA" << endl;
// 	for (int i = 0; i < row; i++) {
// 		cout << left << setw(10) << s[i].studentid << '\t';
// 		for (int j = 0; j < column + 1; j++) {
// 			if (scores[i][j] != -1) {
// 				cout << left << setw(15) << scores[i][j];
// 			}
// 			else {
// 				//student did not enroll this course
// 				cout << left << setw(15) << "-";
// 			}
// 		}
// 		cout << endl;
// 	}
// 	for (int i = 0; i < row; i++) {
// 		delete[] scores[i];
// 	}
// 	delete[] scores;
// 	return true;
// }

bool viewClassScoreBoardIn1Semester(ScoreBoard*& s, float *&scores, string *&courses, int &row, int &column, string schoolYear, string semester, string Class) {
	string path = toSchoolYear + schoolYear;

	path += "/Classes/" + Class + ".txt";
	//return false if class does not exist
	if (!filesystem::exists(path))
		return false;

	path = toSchoolYear + schoolYear + "/" + semester + "/Semester_Info.txt";
	// int row = 0;
	column = getNumberOf(path) - 4;

	//Take courses in this semester
	//string *courses;
	path = toSchoolYear + schoolYear + "/" + semester;
	courses = loadCourseID(path, column);

	//Score of courses that students in a class studied
	float** scores1 = getClassGPAIn1Semester(s, schoolYear, semester, Class, column, row);
	scores = new float[row * (column + 1)];
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < column + 1; j++) {
			scores[i * (column + 1) + j] = scores1[i][j];
		}
	}
	for (int i = 0; i < row; i++) {
		delete[] scores1[i];
	}
	delete[] scores1;
	return true;
}

void loadScore1Course(string pathToSemester, ScoreBoard *&s, string *courses, int n) {
	string destination = "";
	for (int i = 0; i < n; i++) {
		destination = pathToSemester + "/" + courses[i] + "/Score/" + s[0].studentid + ".txt";
		if (filesystem::exists(destination)) {
			loadScore1Student(s[i], destination);
		}
		destination = "";
	}
}

void loadStudentCourses(string path, string *&course, int n){
	ifstream ifs;
	ifs.open(path);
	int i=0, line=1;
	string ig_line="";
	while(!ifs.eof()){
		if(line>7){
			getline(ifs, course[i]);
			line++;
			i++;
		}
		else
		{
			getline(ifs, ig_line);
			line++;
		}
		if (i == n)
			break;
	}
	ifs.close();
}

void loadCourseName(string path, string &name){
	ifstream ifs;
	ifs.open(path);
	string ig_line="";
	getline(ifs, ig_line);
	getline(ifs, name);
	ifs.close();
}

void findScore(string path_string, string id, string *courses, string *&courseName, string *&schoolYears, string *&semesters, ScoreBoard *&s, int *&credits, string schoolYear, string semester, int n){
	for(int i=0;i<n;i++){
		string toCourse=path_string+"/"+courses[i];
		if(filesystem::exists(toCourse)){
			string toInfo=toCourse+"/Course_Info.txt";
			loadCourseName(toInfo, courseName[i]);
			loadCredit(toCourse, credits[i]);
			toCourse+="/Score/"+ id +".txt";
			loadScore1Student(s[i],toCourse);
			schoolYears[i]=schoolYear;
			semesters[i]=semester;
		}
	}
}

bool viewStudentScoreboard(Student student, string *&courses, string *&courseName, string *&schoolYears, string *&semesters, ScoreBoard *&s, float &overall, int &n){
    string path="Data/Student/"+student.studentID+".txt";
	if (!filesystem::exists(path))
		return false;

	loadStudentInfo(student, path);
	n=getNumberOf(path)-7;
	if (n <= 0)
		return false;

	courses=new string[n];
	courseName=new string[n];
	s=new ScoreBoard[n];
	int *credits=new int[n];
	schoolYears=new string[n];
	semesters=new string[n];
	string semester="";

	loadStudentCourses(path, courses, n);
	filesystem::path schoolyear{"Data/SchoolYear/"};
    for (auto const& dir_entry : std::filesystem::directory_iterator{schoolyear}) 
    {
      filesystem::path dir{dir_entry.path()};
      string path_string{dir.generic_u8string()};
	  filesystem::path y_y{dir_entry.path().filename()};
	  string schoolYear{y_y.generic_u8string()};
      string tosemester = "";
	  tosemester = path_string+"/Spring";
      if(filesystem::exists(tosemester)){
		//string toCourse=path_string+"/";
		semester="Spring";
		findScore(tosemester, student.studentID, courses, courseName, schoolYears, semesters, s, credits, schoolYear, semester, n);
      }
	  tosemester = path_string+"/Summer";
	  if(filesystem::exists(tosemester)){
		//string toCourse=path_string+"/";
		semester="Summer";
		findScore(tosemester, student.studentID, courses, courseName, schoolYears, semesters, s, credits, schoolYear, semester, n);
      }
	  tosemester = path_string+"/Autumn";
	  if(filesystem::exists(tosemester)){
		//string toCourse=path_string+"/";
		semester="Autumn";
		findScore(tosemester, student.studentID, courses, courseName, schoolYears, semesters, s, credits, schoolYear, semester, n);
      }
	}
	
	float sum=0;
	int sumOfCredit=0;
	for(int i=0;i<n;i++){
		if(s[i].total!=-1){
		sum+=(s[i].total*credits[i]);
		sumOfCredit+=credits[i];
		}
	}

	for(int i=0;i<n;i++){
		for(int j=i+1;j<n;j++){
			if(courseName[j]==courseName[i] && s[i].total!=-1){
				sum-=(s[i].total*credits[i]);
				sumOfCredit-=credits[i];
				break;
			}
		}
	}
	overall=sum/sumOfCredit;
	return true;
}

bool viewClassScoreBoardInSemester(Student *&stu, int &stuSize, ACourse **&courses, ScoreBoard **&s, int *&scoreBoardSize, string schoolYear, string semester, string Class) {
	string tmp;
	ifstream fin;

	// load student	
	string pathToClass = "Data/SchoolYear/" + schoolYear + "/Classes/" + Class + ".txt";
	cout << pathToClass << endl;
	fin.open(pathToClass);
	if (!fin.is_open())
		return false;
	stuSize = getNumberOf(pathToClass);
	// cout << stuSize << endl;
	fin.close();
	stu = new Student[stuSize];
	fin.open(pathToClass);
	for (int i = 0; i < stuSize; ++i) {
		fin >> tmp >> stu[i].studentID;
		string path = "Data/Student/" + stu[i].studentID + ".txt";
		loadStudentInfo(stu[i], path);
	}
	fin.close();
	
	//load score
	scoreBoardSize = new int[stuSize];
	s = new ScoreBoard*[stuSize];
	courses = new ACourse*[stuSize];
	
	for (int i = 0; i < stuSize; ++i) {
		ViewCoursesStudent(schoolYear, semester, stu[i].studentID, courses[i], s[i], scoreBoardSize[i]);
	}
	// cout << stuSize << endl;
	// for(int i = 0; i < stuSize; ++i) {
	// 	cout << stu[i].studentID << ' ' << scoreBoardSize[i] << ": ";
	// 	for(int j = 0; j < scoreBoardSize[i]; ++j) {
	// 		cout << courses[i][j].id << ' ';
	// 	}
	// 	cout << endl;
	// }

	return true;
}

bool viewClassScoreBoardAllSemester(Student *&stu, int &stuSize, ACourse **&courses, ScoreBoard **&s, int *&scoreBoardSize, string schoolYear, string semester, string Class) {
string tmp;
	ifstream fin;

	// load student	
	string pathToClass = "Data/SchoolYear/" + schoolYear + "/Classes/" + Class + ".txt";
	cout << pathToClass << endl;
	fin.open(pathToClass);
	if (!fin.is_open())
		return false;
	stuSize = getNumberOf(pathToClass);
	// cout << stuSize << endl;
	fin.close();
	stu = new Student[stuSize];
	fin.open(pathToClass);
	for (int i = 0; i < stuSize; ++i) {
		fin >> tmp >> stu[i].studentID;
		string path = "Data/Student/" + stu[i].studentID + ".txt";
		loadStudentInfo(stu[i], path);
	}
	fin.close();
	
	//load score
	scoreBoardSize = new int[stuSize];
	s = new ScoreBoard*[stuSize];
	courses = new ACourse*[stuSize];
	
	for (int i = 0; i < stuSize; ++i) {
		ViewAllCoursesStudent(stu[i].studentID, courses[i], s[i], scoreBoardSize[i]);
	}
	// cout << stuSize << endl;
	// for(int i = 0; i < stuSize; ++i) {
	// 	cout << stu[i].studentID << ' ' << scoreBoardSize[i] << ": ";
	// 	for(int j = 0; j < scoreBoardSize[i]; ++j) {
	// 		cout << courses[i][j].id << ' ';
	// 	}
	// 	cout << endl;
	// }

	return true;
}

//  int main() {
	/////19
	/*string destination = "";
	if (exportCourseStudentList(destination, "2021-2022", "Autumn", "CS162-22CTT2")) {
		cout << "Successfully!" << endl;
	}
	else
		cout << "File does not exist\n";*/

	/////20
	/*string path = "";
	if (importCourseScoreBoard(path, "2021-2022", "Autumn", "CS162-22CTT2")) {
		cout << "Successfully!" << endl;
	}
	else {
		cout << "File does not exist!" << endl;
	}*/

	/////21
	//ScoreBoard* s;
	/*int n = 0;
	if (viewCourseScoreBoard(s, n, "2021-2022", "Autumn", "CS162-22CTT2")) {
		cout << "Successfully!" << endl;
	}
	else {
		cout << "File does not exist!" << endl;
	}
	delete[] s;*/

	/////22
	/*ScoreBoard studentScore, modifiedScore;
	studentScore.studentid = "2212";
	modifiedScore.studentid = "2212";
	modifiedScore.other = 9.9;
	updateStudentResult(studentScore, modifiedScore, "2021-2022", "Autumn", "CS162-22CTT2");
	cout << studentScore.total << " " << studentScore.finals << " " << studentScore.midterm << " " << studentScore.other << endl;*/
	
	/////23
	/*ScoreBoard* s;
	string* courses;
	float *scores;
	int row = 0, column = 0;
	if (!viewClassScoreBoardIn1Semester(s, scores, courses, row, column, "2021-2022", "autumn", "22ctt2")) {
		cout << "school year, semester or class does not exist!\n";
	}
	else {
		cout << left << setw(10) << "student id" << '\t';
		for (int i = 0; i < column; i++) {
			cout << left << setw(15) << courses[i];
		}
		cout << left << setw(15) << "gpa" << endl;
		for (int i = 0; i < row; i++) {
			cout << left << setw(10) << s[i].studentid << '\t';
			for (int j = 0; j < column + 1; j++) {
				if (scores[i * (column + 1) + j] != -1) {
					cout << left << setw(15) << scores[i * (column + 1) + j];
				}
				else {
					//student did not enroll this course
					cout << left << setw(15) << " ";
				}
			}
			cout << endl;
		}
		cout << "successfully!" << endl;
	}
	delete[] s;
	delete[] courses;
	delete[] scores;*/

	/////23
	/*ScoreBoard* s;
	float *scores;
	int row = 0;
	if (!viewClassOverallIn1Year(s, scores, row, "2021-2022", "22CTT2"))
		cout << "School year or Class does not exist" << endl;
	else {
		string* semester = new string[3]{ "Spring","Summer","Autumn" };
		cout << left << setw(10) << "Student ID" << '\t';
		for (int i = 0; i < 3; i++) {
			cout << left << setw(15) << semester[i];
		}
		cout << left << setw(15) << "GPA" << endl;
		for (int i = 0; i < row; i++) {
			cout << left << setw(10) << s[i].studentid << '\t';
			for (int j = 0; j < 4; j++) {
				if (scores[i * 4 + j] >= 0 && scores[i * 4 + j] <= 10) {
					cout << left << setw(15) << scores[i * 4 + j];
				}
				else
					cout << left << setw(15) << " ";
			}
			cout << endl;
		}
		cout << "Successfully!" << endl;
	}*/

	/////24
	// Student student;
	// student.studentID="2212";
	// string *courses;
	// string *courseName;
	// ScoreBoard *s;
	// string *schoolYears;
	// string *semesters;
	// float overall=0;
	// int n=0;
	// if (viewStudentScoreboard(student, courses, courseName, schoolYears, semesters, s, overall, n))
	// {
	// 	cout << student.studentID << endl;
	// 	cout << left << setw(15) << "Course"
	// 		 << left << setw(50) << "Course Name"
	// 		 << left << setw(19) << "School Year"
	// 		 << left << setw(12) << "Semester"
	// 		 << left << setw(9) << "Total"
	// 		 << left << setw(9) << "Final"
	// 		 << left << setw(9) << "Midterm"
	// 		 << left << setw(9) << "Other" << endl;
	// 	for (int i = 0; i < n; i++)
	// 	{
	// 		cout << left << setw(15) << courses[i]
	// 			 << left << setw(50) << courseName[i]
	// 			 << left << setw(19) << schoolYears[i]
	// 			 << left << setw(12) << semesters[i]
	// 			 << left << setw(9) << s[i].total
	// 			 << left << setw(9) << s[i].finals
	// 			 << left << setw(9) << s[i].midterm
	// 			 << left << setw(9) << s[i].other << endl;
	// 	}
	// 	cout << "Overall GPA: " << overall << endl;
	// }
	// else
	// 	cout << "Student does not exist!" << endl;
	// delete[] courses;
	// delete[] courseName;
	// delete[] s;
	// delete[] schoolYears;
	// delete[] semesters;
	/*for (int i = 0; i < row; i++) {
		delete[] scores[i];
	}
	delete[] scores;*/
//  	return 0;
//  }
