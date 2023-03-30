#include <iostream>
#include <fstream>
#include <string.h>
#include <filesystem>

using namespace std;

// maximum amount of attempts allowed before the account is locked
const int MAXATTEMPT = 5;
const string ACCOUNTSTAFF = "../Data/Login/account-staff.txt";
const string ACCOUNTSTUDENT = "../Data/Login/account-student.txt";
const string ACCOUNTLOCKED = "../Data/Login/account-locked.txt";
const string ACCOUNTDIR = "../Data/Login/";

void prompt(string &userid, string &userpass, char &ans) {
    cout << "Account ID: ";
    cin >> userid;
    cout << "Password: ";
    cin >> userpass;
    cout << "Are you a staff? (y/n): ";
    cin >> ans;
    while (!(ans == 'y' || ans == 'Y' || ans == 'n' || ans == 'N')) {
        cout << "Invalid answer. Please try again." << endl;
        cout << "Are you a staff? (y/n): ";
        cin >> ans;
    }
}

// return password if the account id is valid
string checkValidity (ifstream &fin, string userid) {
    bool valid = false;
    string id, pass;
    while (!fin.eof()) {
        fin >> id >> pass;
        if (id.compare(userid) == 0) {
            valid = true;
            break;
        }
    }
    if (!valid)
        pass = "";
    return pass;
}

// check if the account has been locked. The locked accounts are written in Data/account-locked.txt
bool isLock(ifstream &fin, string userid) {
    fin.open(ACCOUNTLOCKED);
    while (!fin.eof()) {
        string lockid;
        fin >> lockid;
        if (userid.compare(lockid) == 0) {
            fin.close();
            return true;
        }
    }
    fin.close();
    return false;
}

// ask for password again if the user input incorrectly. 
// If the number of attempt exceed MAXATTEMPT, lock the account by appending it to account-locked.txt
bool passwordRetry(string pass, string userpass, string userid) {
    int attempt = 0;
    while (pass != userpass && attempt < MAXATTEMPT) {
        cout << "Incorrect password. Please try again." << endl;
        cout << "Password: ";
        cin >> userpass;
        ++attempt;
    }
    if (attempt == MAXATTEMPT) {
        ofstream fout;
        fout.open(ACCOUNTLOCKED, std::ios_base::app);
        fout << userid << endl;
        return false;
    }
    else {
        cout << "Log in successfully!";
        return true;
    }
        
}

// universal login function, used for both student and staff.
// logged in successfully: return the id of student/staff if user to a valid account;
// ask again multiple times if user input incorrect password.
// return string "" if exceed maximum log in attempts or the account ad has been locked.
string login() {
    string userid, userpass;
    char ans;
    prompt(userid, userpass, ans);

    // check for account validity and get password
    ifstream fin;
    if (ans == 'y' || ans == 'Y')
        fin.open(ACCOUNTSTAFF);
    else
        fin.open(ACCOUNTSTUDENT);

    string pass = checkValidity(fin, userid);
    fin.close();
    if (pass.compare("") == 0) {
        cout << "Invalid account ID. Please try again." << endl;
        return login();
    }

    // check if the account has been locked due to excessive incorrect log in attempts
    if (isLock(fin, userid)) {
        cout << "Your account has been locked due to excessive incorrect log in attempts. Contact your school's system administrator to unlock.";
        return "";
    }

    // handle password retry
    if (passwordRetry(pass, userpass, userid))
        return userid;
    else
        return "";
}

bool CreateDirectory(const string& dirName) {
    std::error_code err;
    if (!filesystem::create_directories(dirName, err)) {
        if (filesystem::exists(dirName))
            return true;    // the folder probably already existed

        cout << "CreateDirectory: FAILED to create " << dirName << ", error: " << err.message().c_str() << endl;
        return false;
    }
    return true;
}

// return 1 if login successfully
// return -1 if wrong password
// return -2 if invalid account
// return -3 if account locked
// return 0 if login failed due to problems with directory
// this function should be used with in loop in the caller function.
// to lock an account if the number of attempt exceed MAXATTEMPT,
// the caller function should declare a int variable for counting,
// starting from 0, increment it whenever this function return -1
// and pass it again into this function as a parameter. 
// by default attempt = 0.
int loginUI (string id, string pass, bool isStaff, int attempt) {
    ifstream fin;
    if (isStaff)
        fin.open(ACCOUNTSTAFF);
    else
        fin.open(ACCOUNTSTUDENT);
    if (!fin.is_open()) {
        if (!CreateDirectory(ACCOUNTDIR))
            return 0;
        if (isStaff)
            fin.open(ACCOUNTSTAFF);
        else
            fin.open(ACCOUNTSTUDENT);
        return -2;
    }

    string password = checkValidity(fin, id);
    fin.close();
    if (password.compare("") == 0)
        return -2;
    
    if (isLock(fin, id))
        return -3;
    
    if (pass.compare(password) == 0)
        return 1;
    else
        return -1;
}

int main() {
    login();
}