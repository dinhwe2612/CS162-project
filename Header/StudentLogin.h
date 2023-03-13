#pragma once
#include <iostream> 
#include <string.h>
#include <fstream>

using namespace std;

// return '\0' string if account is not found
string validateAccount(string &StudentID, string &password, ifstream &accountFile);
void inputLogin();
void changePassword();
void logout();