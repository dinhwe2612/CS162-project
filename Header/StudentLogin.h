#pragma once
#include <iostream> 
#include <string.h>
#include <fstream>

using namespace std;

// return NULL string if account is not found
string ValidateAccount(string &StudentID, string &password, ifstream &accountFile);
void InputLogin();
void changePassword();
void Logout();