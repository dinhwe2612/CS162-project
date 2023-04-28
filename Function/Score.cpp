#include"../Header/StudentStruct.h"
#include"../Header/StaffFunc.h"
#include"../Header/ScoreStruct.h"
#include<fstream>
#include "../Header/score.h"

void create_StudentResult_File(string dir) {
	int check;
	check = _mkdir(dir.c_str());

	// check if directory is created or not
	if (!check)
		cout << "Directory created\n";
	else {
		cout << "Unable to create directory\n";
		return;
	}
}

int getNumberOf(string dir) {
	ifstream in;
	in.open(dir);
	string w;
	int n = 0;
	while (!in.eof()) {
		getline(in, w, '\n');
		//in.ignore(256, '\n');
		//in.ignore();
		in.ignore();
		n++;
	}
	in.close();
	return n;
}

bool isPathExist(const string& path) {
	struct stat buffer;
	return (stat(path.c_str(), &buffer) == 0);
}

void loadStudentID(Student*& s, string path) {
	ifstream ifs;
	ifs.open(path.c_str());
	int i = 0;
	while (!ifs.eof()) {
		ifs >> s[i].studentID;
		i++;
	}
	ifs.close();
}

void loadStudentInfo(Student& s, string path) {
	ifstream ifs;
	ifs.open(path.c_str());
	string gender = "";
	getline(ifs, s.studentID);
	getline(ifs, s.lastName);
	getline(ifs, s.firstName);
	getline(ifs, s.Class);
	getline(ifs, gender);
	getline(ifs, s.DOB);
	getline(ifs, s.socialID);
	s.gender = stoi(gender);
	ifs.close();
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


bool exportCourseStudentList(string destination, string schoolYear, string semester, string course) {
	ofstream ofs;
	destination += "/";
	if (!isPathExist(destination))
		return false;


	string path = toSchoolYear + schoolYear + '/' + semester + '/' + course + '/' + "Student_ID_data.txt";
	int n = getNumberOf(path);
	Student* s = new Student[n];
	loadStudentID(s, path);
	for (int i = 0; i < n; i++) {
		path = toDataStudent + s[i].studentID + ".txt";
		loadStudentInfo(s[i], path);
	}

	destination += "Student_ID_data.csv";
	//int n1 = getNumberOf(destination) - 1;
	//int counter = 0;
	//ScoreBoard* newScore = new ScoreBoard[n];

	if (isPathExist(destination)) {
		int n1 = getNumberOf(destination) - 1;
		int counter = 0;
		ScoreBoard* scoreboard = new ScoreBoard[n1];
		Student* newStudent = new Student[n];
		ScoreBoard* newScore = new ScoreBoard[n];
		//ScoreBoard* invalid = new ScoreBoard[n];
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
	ofs.close();
	delete[] s;
	return true;
}

bool isValid(string s) {
	bool valid = false;
	int counter = 0;
	int n = strlen(s.c_str());
	if ((s[0] < '0' || s[0] > '9') || (s[n - 1] < '0' || s[n - 1]>'9')) {
		valid = false;
	}
	else {
		for (int i = 0; i < strlen(s.c_str()); i++) {
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
	return valid;
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
void write_Score(ScoreBoard s, string semester, string schoolyear, string course) {
	ofstream ofs;
	string path = toSchoolYear + schoolyear + '/' + semester + '/' + course + "/Score" + '/' + s.studentid + ".txt";
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
	path += "/Student_ID_data.csv";
	int n = 0, n1=0;

	// take the number of students from a csv file that has been imported before
	n = getNumberOf(path) - 1;
	ScoreBoard* s = new ScoreBoard[n];
	ScoreBoard* s1 = new ScoreBoard[n];
	loadScoreboard(s, schoolyear, semester, course, n, path);
	string pathToFolder = toSchoolYear + schoolyear + '/' + semester + '/' + course + "/Score/";
	string pathToFile = "";
	for (int i = 0; i < n; i++) {
		pathToFile = pathToFolder + s[i].studentid + ".txt";
		if (isPathExist(pathToFile)) {
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
}

bool importCourseScoreBoard(string path, string schoolyear, string semester, string course) {
	path = toSchoolYear + schoolyear + '/' + semester + '/' + course;
	
	if (!isPathExist(path))
		return false;
	string toScore = toSchoolYear + schoolyear + '/' + semester + '/' + course;
	toScore += "/Score";
	if (!isPathExist(toScore)) {
		create_StudentResult_File(toScore);
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
	string path = toSchoolYear + schoolYear + '/' + semester + '/' + course + "/Score/" + course + ".txt";
	if (!isPathExist(path))
		return false;
	n = getNumberOf(path);
	scoreBoard = new ScoreBoard[n];
	Student *s = new Student[n];
	loadStudentID(s, path);
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
		if (isPathExist(toStuFile)) {
			loadScore1Student(scoreBoard[i], toStuFile);
		}
	}
	// viewScoreboard(scoreBoard, n);
	return true;
}

bool updateStudentResult(ScoreBoard& studentScore, ScoreBoard modifiedScore, string schoolYear, string semester, string course) {
	string path = toSchoolYear + schoolYear + '/' + semester + '/' + course + "/Score" + '/' + studentScore.studentid + ".txt";
	if (!isPathExist(path) || studentScore.studentid != modifiedScore.studentid)
		return false;
	string* info = Read_File(path);
	float* a = new float[4]{ modifiedScore.total, modifiedScore.finals, modifiedScore.midterm, modifiedScore.other };
	int i = 0;
	while (i < 4) {
		if (a[i] >= 0 && a[i] <= 10) {
			info[i + 1] = to_string(a[i]);
		}
		i++;
	}
	remove(path.c_str());
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
	string* info = new string[n];
	while (!in.eof()) {
		getline(in, id);
		in.ignore();
		info[i] = id;
		i++;
	}
	in.close();
	return info;
}

void loadCredit(string path, int& credit) {
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
float** gpaOf1Semester(float** a, int* credits, int row, int column) {
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
			a[i][column] = gpa;
		}
		gpa = 0;
		times = 0;
	}
	return a;
}

float** getClassGPAIn1Semester(ScoreBoard*& classScore, string schoolYear, string semester, string Class, int& column, int& row) {
	string path = toSchoolYear + schoolYear + '/' + semester;

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
	path = toSchoolYear + schoolYear + '/' + semester;
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
	float** score = new float* [row];
	for (int i = 0; i < row; i++) {
		score[i] = new float[column + 1];
	}
	for (int i = 0; i < column; i++) {
		pathToScore = path + '/' + courses[i] + "/Score/";
		for (int j = 0; j < row; j++) {
			pathToScore += classScore[j].studentid + ".txt";
			if (isPathExist(pathToScore)) {
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
	float** gpa = new float* [row];
	for (int i = 0; i < row; i++)
		gpa[i] = new float[4];
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < 4; j++) {
			gpa[i][j] = 0;
		}
	}
	string semester = "Spring";
	path = toSchoolYear + schoolYear + '/' + semester;
	if (isPathExist(path)) {
		score = getClassGPAIn1Semester(s, schoolYear, semester, Class, column, row);
		for (int i = 0; i < row; i++) {
			gpa[i][0] = score[i][column];
		}
		times++;
	}
	semester = "Summer";
	path = toSchoolYear + schoolYear + '/' + semester;
	if (isPathExist(path)) {
		score = getClassGPAIn1Semester(s, schoolYear, semester, Class, column, row);
		for (int i = 0; i < row; i++) {
			gpa[i][1] = score[i][column];
		}
		times++;
	}
	semester = "Autumn";
	path = toSchoolYear + schoolYear + '/' + semester;
	if (isPathExist(path)) {
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
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < 3; j++) {
			sum += gpa[i][j];
		}
		sum /= times;
		gpa[i][3] = sum;
		sum = 0;
	}
	return gpa;
}

bool viewClassOverallIn1Year(ScoreBoard*& s, string schoolYear, string Class) {
	string path = toSchoolYear + schoolYear;
	if (!isPathExist(path))
		return false;
	path += "/Classes/" + Class + ".txt";
	if (!isPathExist(path))
		return false;
	int row = 0, column = 0;
	float** scores = getClassOverallGPA(s, schoolYear, Class, row, column);
	string* semester = new string[3]{ "Spring","Summer","Autumn" };
	cout << left << setw(10) << "Student ID" << '\t';
	for (int i = 0; i < 3; i++) {
		cout << left << setw(15) << semester[i];
	}
	cout << left << setw(15) << "GPA" << endl;
	for (int i = 0; i < row; i++) {
		cout << left << setw(10) << s[i].studentid << '\t';
		for (int j = 0; j < 4; j++) {
			cout << left << setw(15) << scores[i][j];
		}
		cout << endl;
	}
	for (int i = 0; i < row; i++) {
		delete[] scores[i];
	}
	delete[] scores;
	return true;
}

bool viewClassScoreBoardIn1Semester(ScoreBoard*& s, string schoolYear, string semester, string Class) {
	string path = toSchoolYear + schoolYear;

	path += "/Classes/" + Class + ".txt";
	//return false if class does not exist
	if (!isPathExist(path))
		return false;

	path = toSchoolYear + schoolYear + '/' + semester + "/Semester_Info.txt";
	int row = 0;
	int column = getNumberOf(path) - 4;

	//Take courses in this semester
	string* courses;
	path = toSchoolYear + schoolYear + '/' + semester;
	courses = loadCourseID(path, column);

	//Score of courses that students in a class studied
	float** scores = getClassGPAIn1Semester(s, schoolYear, semester, Class, column, row);
	cout << left << setw(10) << "Student ID" << '\t';
	for (int i = 0; i < column; i++) {
		cout << left << setw(15) << courses[i];
	}
	cout << left << setw(15) << "GPA" << endl;
	for (int i = 0; i < row; i++) {
		cout << left << setw(10) << s[i].studentid << '\t';
		for (int j = 0; j < column + 1; j++) {
			if (scores[i][j] != -1) {
				cout << left << setw(15) << scores[i][j];
			}
			else {
				//student did not enroll this course
				cout << left << setw(15) << "-";
			}
		}
		cout << endl;
	}
	for (int i = 0; i < row; i++) {
		delete[] scores[i];
	}
	delete[] scores;
	return true;
}

void loadScore1Course(string pathToSemester, ScoreBoard*& s, string* courses, int n) {
	string destination = "";
	for (int i = 0; i < n; i++) {
		destination = pathToSemester + "/" + courses[i] + "/Score/" + s[0].studentid + ".txt";
		if (isPathExist(destination)) {
			loadScore1Student(s[i], destination);
		}
		destination = "";
	}
}

bool viewStudentScoreboard(ScoreBoard*& s, string*& courses, float*& gpa, string studentid, string schoolYear, int& n) {
	string path = toSchoolYear + schoolYear;
	if (!isPathExist(path))
		return false;
	string pathToStu = toDataStudent + studentid + ".txt";
	if (!isPathExist(pathToStu))
		return false;
	Student stu;
	loadStudentInfo(stu, pathToStu);
	s[0].lastname = stu.lastName + " " + stu.firstName;
	int times = 0;
	int columnSp = 0, columnS = 0, columnA = 0, size = 0;
	string pathToSp = path + "/Spring";
	s[0].studentid = studentid;
	if (isPathExist(pathToSp)) {
		columnSp = getNumberOf(pathToSp + "/Semester_Info.txt") - 4;
		string* courseSp = loadCourseID(pathToSp, columnSp);
		for (int i = 0; i < columnS; i++) {
			courses[i] = courseSp[i];
		}
		loadScore1Course(pathToSp, s, courseSp, columnSp);
		//Take credit of courses
		int* credits = new int[columnSp];
		string pathToCredit;
		for (int i = 0; i < columnSp; i++) {
			pathToCredit = pathToSp + '/' + courseSp[i];
			loadCredit(pathToCredit, credits[i]);
		}

		//Take total of each student in a class
		string pathToScore;
		float** score = new float* [1];
		//column is the number of courses which save total of each course 
		//column + 1 is for saving gpa
		score[0] = new float[columnSp + 1];

		//column is the number of courses
		//each row in Scoreboard array save score of one course
		for (int i = 0; i < columnSp; i++) {
			pathToScore = path + '/' + courseSp[i] + "/Score/";
			pathToScore += studentid + ".txt";
			if (isPathExist(pathToScore)) {
				loadScore1Student(s[i], pathToScore);
				s[i].firstname = "Spring";
				score[0][i] = s[i].total;
			}
			else {
				score[0][i] = -1;
			}
		}
		//calculate gpa of each student in one semester
		score = gpaOf1Semester(score, credits, 1, columnSp);
		gpa[0] = score[0][columnSp];
		delete[] score[0];
		delete[] score;
	}
	size += columnSp;


	pathToSp = path + "/Summer";
	if (isPathExist(pathToSp)) {
		//s[size].firstname = "Summer";
		columnS = getNumberOf(pathToSp + "/Semester_Info.txt") - 4;
		string* courseSp = loadCourseID(pathToSp, columnS);
		for (int i = 0; i < columnS; i++) {
			courses[i + size] = courseSp[i];
		}
		loadScore1Course(pathToSp, s, courseSp, columnS);
		//Take credit of courses
		int* credits = new int[columnS];
		string pathToCredit;
		for (int i = 0; i < columnS; i++) {
			pathToCredit = pathToSp + '/' + courseSp[i];
			loadCredit(pathToCredit, credits[i]);
		}

		//Take total of each student in a class
		string pathToScore;
		float** score = new float* [1];
		//column is the number of courses which save total of each course 
		//column + 1 is for saving gpa
		score[0] = new float[columnS + 1];

		//column is the number of courses
		//each row in Scoreboard array save score of one course
		for (int i = 0; i < columnS; i++) {
			pathToScore = path + '/' + courseSp[i] + "/Score/";
			pathToScore += studentid + ".txt";
			if (isPathExist(pathToScore)) {
				loadScore1Student(s[i + size], pathToScore);
				score[0][i] = s[i + size].total;
				s[i + size].firstname = "Summer";
			}
			else {
				score[0][i] = -1;
			}
		}
		//calculate gpa of each student in one semester
		score = gpaOf1Semester(score, credits, 1, columnS);
		gpa[1] = score[0][columnS];
		delete[] score[0];
		delete[] score;
	}
	size += columnS;

	pathToSp = path + "/Autumn";
	if (isPathExist(pathToSp)) {
		//s[size].firstname = "Autumn";
		columnA = getNumberOf(pathToSp + "/Semester_Info.txt") - 4;
		string* courseSp = loadCourseID(pathToSp, columnA);
		for (int i = 0; i < columnA; i++) {
			courses[i + size] = courseSp[i];
		}
		loadScore1Course(pathToSp, s, courseSp, columnA);
		//Take credit of courses
		int* credits = new int[columnA];
		string pathToCredit;
		for (int i = 0; i < columnA; i++) {
			pathToCredit = pathToSp + '/' + courseSp[i];
			loadCredit(pathToCredit, credits[i]);
		}

		// Take total of each student in a class
		string pathToScore;
		float** score = new float* [1];
		// column variable stores the number of courses
		// each column save total score of each course
		// final column is for saving gpa
		score[0] = new float[columnA + 1];

		// each row in Scoreboard array save score of one course
		// the number of elements in the array is the number of courses
		for (int i = 0; i < columnA; i++) {
			pathToScore = pathToSp + '/' + courseSp[i] + "/Score/";
			pathToScore += studentid + ".txt";
			if (isPathExist(pathToScore)) {
				loadScore1Student(s[i + size], pathToScore);
				score[0][i] = s[i + size].total;
				s[i + size].firstname = "Autumn";
			}
			else {
				score[0][i] = -1;
			}
		}
		size += columnA;
		//calculate gpa of each student in one semester
		score = gpaOf1Semester(score, credits, 1, columnA);
		gpa[2] = score[0][columnA];
		delete[] score[0];
		delete[] score;
	}

	n = size;
	return true;
}

//int main() {
	//string destination = "";
	//if (exportCourseStudentList(destination, "2021-2022", "Autumn", "CS162-22CTT2")) {
		//cout << "Successfully!" << endl;
	//}
	//else
	//	cout << "File does not exist\n";
	
	///*string path = "";
	//if (importCourseScoreBoard(path, "2021-2022", "Autumn", "CS162-22CTT2")) {
	//	cout << "Successfully!" << endl;
	//}
	//else {
	//	cout << "File does not exist!" << endl;
	//}*/
	/*ScoreBoard* s = new ScoreBoard;
	int n = 0;
	if (viewCourseScoreBoard(s, n, "2021-2022", "Autumn", "CS162-22CTT2")) {
		cout << "Successfully!" << endl;
	}
	else {
		cout << "File does not exist!" << endl;
	}*/
	//ScoreBoard studentScore, modifiedScore;
	//studentScore.studentid = "2212";
	//modifiedScore.studentid = "2212";
	//modifiedScore.other = 10;
	//updateStudentResult(studentScore, modifiedScore, "2021-2022", "Autumn", "CS162-22CTT1");
	// //ScoreBoard* s = nullptr;
	//string* courses = nullptr;
	//float** scores=nullptr;
	//int row = 0, column = 0;
	/*if (!viewClassScoreBoardIn1Semester(s, "2021-2022", "Autumn", "22CTT1")) {
		cout << "School year, Semester or Class does not exist!\n";
	}
	else {
		cout << "Successfully!" << endl;
	}*/

	/*if (!viewClassOverallIn1Year(s, "2021-2022", "22CTT1"))
		cout << "School year or Class does not exist" << endl;
	else
		cout << "Successfully!" << endl;*/

	/*ScoreBoard* s = new ScoreBoard[100];
	string* courses = new string[100];
	float* gpa = new float[3]{ -1,-1,-1 };
	int n = 0, z = 0;
	string* semester = new string[3]{ "Spring","Summer","Autumn" };
	if (viewStudentScoreboard(s, courses, gpa, "2212", "2021-2022", n)) {
		cout << "Student ID: " << s[0].studentid << endl;
		cout << "Full Name: " << s[0].lastname << endl;
		for (int i = 0; i < 3; i++) {
			cout << "\n*" << semester[i] << "*" << endl;
			for (int j = z; j < n; j++) {
				if (s[j].firstname != semester[i]) {
					z = j;
					break;
				}
				cout << left << setw(15) << courses[j]
					<< left << setw(9) << s[j].total
					<< left << setw(9) << s[j].finals
					<< left << setw(9) << s[j].midterm
					<< left << setw(9) << s[j].other << endl;
			}
			cout << "GPA: " << gpa[i] << endl;
		}
		float overall = 0;
		for (int i = 0; i < 3; i++) {
			if (gpa[i] != -1)
				overall += gpa[i];
		}
		cout << "\nOverall GPA: " << overall / 3 << endl;
	}
	else {
		cout << "Student id or school year does not exist" << endl;
	}
	delete[] s;
	delete[] courses;
	delete[] gpa;
	delete[] semester;*/

	//return 0;
//}
