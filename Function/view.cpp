#include <iostream>
#include <filesystem>
#include <fstream>

using namespace std;

bool checkDirectory(const filesystem::path& path) {
    if (!filesystem::exists(path)) {
        // path does not exist
        return false;
    }

    if (!filesystem::is_directory(path)) {
        // path is not a directory
        return false;
    }

    return true;
}

string getPath (string s, string name = "", string schoolYear = "") {
    if (s.compare("Class") == 0)
        return "../Data/" + schoolYear + "/Classes/" + name;
    else if (s.compare("Student") == 0)
        return "../Data/Students/" + name + ".txt";
    else
        return "";
}

bool viewClasses(string schoolYear) {
    const filesystem::path path = getPath("Class", "", schoolYear);
    if (!checkDirectory(path))
        return false;
    
    for (const auto & entry : filesystem::directory_iterator(path)) {
        if (entry.is_regular_file()) {
            cout << entry.path().stem().string() << endl;
        }
    }
    
    return true;
}

bool viewStudentInClass (string Class, string schoolYear) {
    const filesystem::path path = getPath("Class", Class + ".txt", schoolYear);
    if (!filesystem::exists(path)) {
        // file does not exist
        return false;
    }
    ifstream fin;
    fin.open(path);
    while (!fin.eof()) {
        string studentID;
        fin.ignore();
        fin >> studentID;
        fin.ignore(1000, '\n');
        fin.ignore();
        ifstream fi;
        fi.open(getPath("Student", studentID));
        while (!fi.eof()) {
            string s;

            getline(fi, s, '\n');
            if (s.compare("0") == 0)
                cout << "Male" << endl;
            else if (s.compare("1") == 0)
                cout << "Female" << endl;
            else if (s.compare("2") == 0)
                cout << "Other" << endl;
            else
                cout << s << endl;
        }
        fi.close();
    }
    fin.close();
    return true;
}

int main() {
    string schoolYear = "2022-2023";
    if (!viewClasses(schoolYear))
        cout << "The school year has not been created yet, or the database has been corrupted.";
    if (!viewStudentInClass("22TT2", schoolYear))
        cout << "Class does not exist";
    return 0;
}
