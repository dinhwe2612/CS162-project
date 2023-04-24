#include"../Header/StudentStruct.h"
#include"../Header/StaffFunc.h"
#include"../Header/ScoreStruct.h"
#include<fstream>
#include"Score.h"

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
	s.Gender = stoi(gender);
	ifs.close();
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

bool exportCourseStudentList(string destination, string schoolYear, string semester, string course) {
	ofstream ofs;
	destination = toSchoolYear + schoolYear + '/' + semester + '/' + course;
	if (!isPathExist(destination))
		return false;


	string path = ToSchoolYear + schoolYear + '/' + semester + '/' + course + '/' + "Student_ID_data.txt";
	int n = getNumberOf(path);
	Student* s = new Student[n];
	loadStudentID(s, path);
	for (int i = 0; i < n; i++) {
		path = toDataStudent + s[i].studentID + ".txt";
		loadStudentInfo(s[i], path);
	}

	destination += "/Student_ID_data.csv";
	ofs.open(destination.c_str());
	ofs << "No,Student ID,LastName,FirstName,Class,Gender,DOB,Social ID,Total,Finals,Midterm,Other" << "\n";
	for (int i = 0; i < n; i++) {
		ofs << i + 1 << ','
			<< s[i].studentID << ','
			<< s[i].lastName << ','
			<< s[i].firstName << ','
			<< s[i].Class << ','
			<< s[i].Gender << ','
			<< s[i].DOB << ','
			<< s[i].socialID << ','
			<< -1 << ',' << -1 << ',' << -1 << ',' << -1 << '\n';
	}
	ofs.close();
	return true;
}

void loadScoreboard(ScoreBoard* s, string schoolyear, string semester, string course_name, int& n, string path) {
	//locale loc(std::locale(), new std::codecvt_utf8<wchar_t>);
	ifstream ifs;
	//string path_in = pathToSchoolYear + schoolyear + '/' + semester + '/' + course_name + '/' + course_name + ".csv";
	string path_txt = toSchoolYear + schoolyear + '/' + semester + '/' + course_name + "/Score" + '/' + course_name + ".txt";

	ifs.open(path.c_str());

	if (path != path_txt) {
		string ignore_line = "";
		getline(ifs, ignore_line, '\n');
	}

	string no = "";
	string student_id = "";
	string student_fn = "";
	string student_ln = "";
	string Class = "", gender = "", DOB = "", socialID = "";
	string total = "", finals = "", midterm = "", other = "";
	int i = 0;
	bool v1, v2, v3, v4;
	while (!ifs.eof()) {
		if (path != path_txt) {
			getline(ifs, no, ',');
		}
		getline(ifs, s[i].studentid, ',');
		if (s[i].studentid == "")
			break;
		getline(ifs, s[i].lastname, ',');
		getline(ifs, s[i].firstname, ',');
		if (path != path_txt) {
			getline(ifs, Class, ',');
			getline(ifs, gender, ',');
			getline(ifs, DOB, ',');
			getline(ifs, socialID, ',');
		}
		getline(ifs, total, ',');
		getline(ifs, finals, ',');
		getline(ifs, midterm, ',');
		getline(ifs, other);
		if (path != path_txt) {
			v1 = isValid(total);
			v2 = isValid(finals);
			v3 = isValid(midterm);
			v4 = isValid(other);
			try {
				if (v1 && v2 && v3 && v4) {
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
				cout << "Invalid data!\n";
				cout << s[i].studentid << " " << s[i].lastname << " " << s[i].firstname << " " << s[i].total << " " << s[i].finals << " " << s[i].midterm << " " << s[i].other << endl;
			}
		}
		else if (path == path_txt) {
			s[i].total = stof(total);
			s[i].finals = stof(finals);
			s[i].midterm = stof(midterm);
			s[i].other = stof(other);
			i++;
		}
		if (i == n) {
			break;
		}
	}
	//n = i;
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
	saveScoreOf1Stu(s, schoolyear, semester, course, n);
}

void checkData(string path, string schoolyear, string semester, string course) {
	path += "/Student_ID_data.csv";
	string path_out = toSchoolYear + schoolyear + '/' + semester + '/' + course + "/Score" + '/' + course + ".txt";
	int n = 0, n1 = 0, n2 = 0;
	n1 = getNumberOf(path) - 1;
	n2 = getNumberOf(path_out);
	ScoreBoard* s = new ScoreBoard[51];
	ScoreBoard* s1 = new ScoreBoard[n1];
	ScoreBoard* s2 = new ScoreBoard[n2];
	loadScoreboard(s1, schoolyear, semester, course, n1, path);
	if (isPathExist(path_out)) {
		loadScoreboard(s2, schoolyear, semester, course, n2, path_out);
		//cout << s2[1].studentID << endl;
		//n1 -= 1;
		//n2 -= 1;
		compareData(s1, s2, s, n1, n2, n);;
	}

	//Show duplicate data
	if (n > 0) {
		cout << "The duplicate data:\n";
		for (int i = 0; i < n; i++) {
			cout << s[i].studentid << " " << s[i].lastname << " " << s[i].firstname << " " << s[i].total << " " << s[i].finals << " " << s[i].midterm << " " << s[i].other << endl;
		}
	}

	//write the new data to file if it has new data from csv file
	if (n1 > 0) {
		saveScore(path_out, s1, n1, schoolyear, semester, course);
		cout << "Import Successfully!\n";
	}
	else {
		cout << "There is no new data to import!\n";
	}
	delete[] s;
	delete[] s1;
	delete[] s2;
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

void compareData(ScoreBoard* s1, ScoreBoard* s2, ScoreBoard* s, int& n1, int& n2, int& n) {
	int counter = 0;
	bool update = false;
	for (int i = 0; i < n2; i++) {
		for (int j = 0; j < n1; j++) {
			if (s2[i].studentid == s1[j].studentid &&
				(s2[i].total != s1[j].total || s2[i].finals != s1[j].finals ||
					s2[i].midterm != s1[j].midterm || s2[i].other != s1[j].other)) {
				//counter++;
				update = true;
			}
			else if (s2[i].studentid == s1[j].studentid &&
				s2[i].total == s1[j].total && s2[i].finals == s1[j].finals &&
				s2[i].midterm == s1[j].midterm && s2[i].other == s1[j].other) {
				//save lines that are redundant
				n++;
				s[n - 1] = s1[j];
				//remove lines that are redundant
				for (int z = j; z < n1 - 1; z++) {
					s1[z] = s1[z + 1];
				}
				n1--;
				update = false;
			}
			if (update) {
				s2[i] = s1[j];
				for (int z = j; z < n1 - 1; z++) {
					s1[z] = s1[z + 1];
				}
				n1--;
				//counter = 0;
				update = false;
			}
		}
		//counter = 0;
		update = false;
	}
}

bool importCourseScoreBoard(string path, string schoolyear, string semester, string course) {
	path += toSchoolYear + schoolyear + '/' + semester + '/' + course;
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


int main() {
	//exportCourseStudentList("", "2021-2022", "Autumn", "CS161-22APCS2");
	//importCourseScoreBoard("", "2021-2022", "Autumn", "CS161-22APCS2");
	return 0;
}

