#pragma once
#ifndef ScoreStruct_h
#define ScoreStruct_h
#include<iostream>
#include<fstream>
#include<iomanip>
#include<sstream>
#include<sys/stat.h>
#include<sys/types.h>
#include"StudentStruct.h"
#include"score.h"
#include<filesystem>
#ifdef _WIN32
    #include <direct.h>
#endif
using namespace std;

const string toSchoolYear = "Data/SchoolYear/";
const string toDataStudent = "Data/Student/"; 
#endif