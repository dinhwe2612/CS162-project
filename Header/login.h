#pragma once
#include <iostream>
#include <fstream>
#include <string.h>
#include <string>
#include <filesystem>

using namespace std;

string login();
int validateAccount (string id, string pass, bool isStaff, int attempt);
void changePassword (string id, string newpass, bool isStaff);