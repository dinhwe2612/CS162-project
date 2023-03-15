#include <iostream>
#include <fstream>
#include <string.h>

using namespace std;

// maximum amount of attempts allowed before the account is locked
const int MAXATTEMPT = 5;

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
    fin.open("..\\Data\\account-locked.txt");
    // uncomment below for MacOS/Linux
    // fin.open("../Data/account-locked.txt");
    while (!fin.eof()) {
        string lockid;
        fin >> lockid;
        if (userid.compare(lockid) == 0) {
            cout << "Your account has been locked due to excessive incorrect log in attempts. Contact your school's system administrator to unlock.";
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
        fout.open("..\\Data\\account-locked.txt", std::ios_base::app);
        // uncomment below for MacOS/Linux
        // fout.open("../Data/account-locked.txt", std::ios_base::app);
        fout << userid << endl;
        cout << "Your account has been locked due to excessive incorrect log in attempts. Contact your school's system administrator to unlock.";
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
        fin.open("..\\Data\\account-staff.txt");
        // uncomment below for MacOS/Linux
        // fin.open("../Data/account-staff.txt");
    else
        fin.open("..\\Data\\account-student.txt");
        // uncomment below for MacOS/Linux
        // fin.open("../Data/account-student.txt");

    string pass = checkValidity(fin, userid);
    fin.close();
    if (pass.compare("") == 0) {
        cout << "Invalid account ID. Please try again." << endl;
        return login();
    }

    // check if the account has been locked due to excessive incorrect log in attempts
    if (isLock(fin, userid))
        return "";

    // handle password retry
    if (passwordRetry(pass, userpass, userid))
        return userid;
    else
        return "";
}
