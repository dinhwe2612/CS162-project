#pragma once
#ifndef login_h
#define login_h

#include <iostream>
#include <fstream>
#include <string.h>
#include <string>
#include <filesystem>

using namespace std;

string login();
int validateAccount (string id, string pass, bool isStaff);
void changePassword (string id, string newpass, bool isStaff);

#endif