#include"../Header/StudentStruct.h"
#include"../Header/StaffFunc.h"
#include"../Header/ScoreStruct.h"
#include<fstream>

//The maximum number of students in the course
#define MAX_NO_STUDENTS 50

const string pathToSchoolYear = "../Data/SchoolYear/";
const string toSemesterInfo_txt = "/Semester_Info.txt";
//Import the result of a course from a csv file
void importScoreboard(Scoreboard* s, string course_name, int& n, string path) {
	fstream ifs, ofs;
	ifs.open(path + '/' + course_name + '/' + course_name + ".csv", ios::in);
	ofs.open(path + '/' + course_name + '/' + course_name + "-SCORE.txt", ios::out);
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

		/*s[i].studentID = student_id;
		s[i].lastname = student_ln;
		s[i].firstname = student_fn;
		s[i].total = stof(total);
		s[i].finals = stof(finals);
		s[i].midterm = stof(midterm);
		s[i].other = stof(other);*/
		ofs << i + 1 << ',';
		ofs << student_id << ',';
		ofs << student_ln << ',';
		ofs << student_fn << ',';
		ofs << total << ',';
		ofs << finals << ',';
		ofs << midterm << ',';
		ofs << other << '\n';

		i++;
	}
	n = i;
	ifs.close();
	ofs.close();
	cout << "Import successfully!\n";
}

/*void viewScoreboard(Scoreboard* s, string course_name, int N) {
	cout << "No\t"
		<< "Student ID\t"
		<< left << setw(20) << "Last Name"
		<< left << setw(10) << "First Name\t"
		<< "Total\t"
		<< "Final\t"
		<< "Midterm\t"
		<< "Other\n";
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
}*/

void viewScoreboard(string path, string course_id) {
	cout << "No\t"
		<< "Student ID\t"
		<< left << setw(20) << "Last Name"
		<< left << setw(10) << "First Name\t"
		<< "Total\t"
		<< "Final\t"
		<< "Midterm\t"
		<< "Other\n";
	ifstream ifs;
	ifs.open(path + '/' + course_id + '/' + course_id + "-SCORE.txt");

	string no = "";
	string student_id = "";
	string student_fn = "";
	string student_ln = "";
	string total = "", finals = "", midterm = "", other = "";
	while (!ifs.eof()) {
		getline(ifs, no, ',');
		if (no == "")
			break;
		getline(ifs, student_id, ',');
		getline(ifs, student_ln, ',');
		getline(ifs, student_fn, ',');
		getline(ifs, total, ',');
		getline(ifs, finals, ',');
		getline(ifs, midterm, ',');
		getline(ifs, other, '\n');
		//ifs.ignore();

		cout << no << "\t";
		cout << student_id << "\t";
		cout << left << setw(20) << student_ln;
		cout << left << setw(10) << student_fn << "\t";
		cout << total << "\t";
		cout << finals << "\t";
		cout << midterm << "\t";
		cout << other << '\n';
	}
	ifs.close();
}

void staff_Views_Scoreboard(string& schoolyear, string& semester, string& course) {
	//string path = "..Data/SchoolYear";
	string path = pathToSchoolYear;
	string path_txt = "";
	string path_To_Txt = "";
	bool type = false; // if information is typed and exists, type=true, otherwise false (used for input functions: sy,semester,course)
	int option;
	cout << "Press 1 to continue with viewing score\n";
	cout << "Press 0 to exit\n";
	cout << "Please, press one key: ";
	cin >> option;
	cin.ignore(32767, '\n');
	do {
		if (option == 1) {
			inputShoolYear(schoolyear, path, type);
			if (!type) return;
			inputSemester(semester, path, type);
			if (!type) return;
			path_txt = path + toSemesterInfo_txt;
			int numOf_id = getNumberOf(path_txt);
			numOf_id = numOf_id - 4;
			if (numOf_id == 0)
				cout << "Courses have not been added yet! You can not view score of them." << endl;
			else {
				string* courseID = new string[numOf_id];
				loadCourseID(courseID, schoolyear, semester, path_txt);
				//check_CourseID_Csv(courseID, numOf_id, path);
				printCourseID(courseID, numOf_id);
				path_To_Txt = path;
				inputCourse(course, courseID, numOf_id, path, type);
				if (!type) return;
				delete[] courseID;
			}
			viewScoreboard(path_To_Txt, course);
		}
		else if (option == 0)
			return;
		cout << "-------------------\n";
		cout << "Press 1 to continue with viewing score\n";
		cout << "Press 0 to exit\n";
		cout << "-------------------\n";
		cout << "Please, press one key: ";
		cin >> option;
		cin.ignore(32767, '\n');
		schoolyear = "";
		semester = "";
		course = "";
	} while (option);
}

//Input function
void inputShoolYear(string& schoolyear, string& path, bool& type) {
	//cin.ignore(32767, '\n');
	cout << "*********SCHOOLYEAR\n";
	cout << "Please enter a school year according the format(yyyy-yyyy): ";
	getline(cin, schoolyear);
	string dir = path + schoolyear;
	try {
		if (isPathExist(dir)) {
			type = true;
			path = dir;
			cout << "Successfully done, please continue with the information below." << endl;
		}
		else
			throw (schoolyear);
	}
	catch (string _year) {
		cout << "The school year " << _year << " does not exist." << endl;
		cout << "Do you want to type again\n";
		cout << "1. Yes\n" << "Other. No\n";
		cout << "Choose one number: ";
		int opt;
		cin >> opt;
		cin.ignore();
		if (opt == 1) {
			//type = true;
			_year = "";
			inputShoolYear(_year, path, type);
		}
		else
			type = false;
	}
}



void inputSemester(string& semester, string& path, bool& type) {
	//cin.ignore(32767, '\n');
	cout << "\n*********SEMESTER\n";
	cout << "1. SPRING\n" << "2. SUMMER\n" << "3. AUTUMN\n";
	cout << "Please enter one of numbers above: ";
	int n;
	cin >> n;
	cin.ignore(32767, '\n');
	
	switch (n) {
	case 1:
		semester = "Spring";
		break;
	case 2:
		semester = "Summer";
		break;
	case 3:
		semester = "Autumn";
		break;
	default:
		break;
	}
	string dir = path + '/' + semester;

	try {
		if (isPathExist(dir)) {
			type = true;
			path = dir;
			cout << "Successfully done, please continue with the information below." << endl;
		}
		else
			throw (semester);
	}
	catch (string _semester) {
		cout << "The semester " << _semester << " does not exist." << endl;
		cout << "Do you want to type again\n";
		cout << "1. Yes\n" << "Other. No\n";
		cout << "Choose one number: ";
		int opt;
		cin >> opt;
		cin.ignore();
		if (opt == 1) {
			//type = true;
			_semester = "";
			inputSemester(_semester, path, type);
		}
		else
			type = false;
	}
}

void inputCourse(string& course_id, string* courseID, int numberof_id, string& path, bool& type) {
	//cin.ignore(32767, '\n');
	cout << "Which course do you want to choose? Please select one of numbers above and type here: ";
	int i;
	//getline(cin, course_id);
	cin >> i;
	cin.ignore(32767, '\n');

	if (i > 0 && i <= numberof_id) {
		string dir = path + '/' + courseID[i - 1] + '/' + courseID[i - 1] + ".csv";
		try {
			if (isPathExist(dir)) {
				type = true;
				path = dir;
				course_id = courseID[i - 1];
			}
			else
				throw (courseID[i - 1]);
		}
		catch (string _course_id) {
			cout << "The course " << _course_id << " has not been uploaded scores yet." << endl;
			cout << "Do you want to type again\n";
			cout << "1. Yes\n" << "Others. No\n";
			cout << "Choose one number: ";
			int opt;
			cin >> opt;
			cin.ignore();
			if (opt == 1) {
				//type = true;
				_course_id = "";
				inputCourse(_course_id, courseID, numberof_id, path, type);
			}
			else
				type = false;
		}
	}
	else
		inputCourse(course_id, courseID, numberof_id, path, type);
}

bool isPathExist(const string& path) {
	struct stat buffer;
	return (stat(path.c_str(), &buffer) == 0);
}

//Load courseID of courses in a semester
void loadCourseInfo(string* courseId, string schoolyear, string semester, string path) {
	ifstream in;
	in.open(path);

	string line1 = "", line2 = "", line3 = "", line4 = "";
	getline(in, line1, '\n');
	getline(in, line2, '\n');
	getline(in, line3, '\n');
	getline(in, line4, '\n');

	string id = "";
	int i = 0;
	while (!in.eof()) {
		getline(in, id);
		in.ignore();
		courseId[i] = id;
		i++;
	}
	in.close();
}

void printCourseID(string* id, int n) {
	cout << "\n*********COURSE\n";
	cout << "Here are courses in this semester\n";
	for (int i = 0; i < n; i++) {
		cout << id[i] << endl;
	}
}

int getNumberOf(string dir) {
	ifstream in;
	in.open(dir);
	string w;
	int n = 0;
	while (!in.eof()) {
		getline(in, w, '\n');
		in.ignore();
		n++;
	}
	in.close();
	return n;
}

int main() {
	string schoolyear = "", semester = "", course = "";
	staff_Views_Scoreboard(schoolyear, semester, course);
	return 0;
}

