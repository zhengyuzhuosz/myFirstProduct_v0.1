#pragma once
#include <time.h>
#include <stdio.h>
#include <string.h>
#include <string>
using namespace std;
#define MaxTimeChar 100

int getTimeNow(char* input);

int getTimeYear();

int getTimeMonth();

int getTimeDay();

tm str2tm(const char* input);

string tm2str(tm input);

int timeDiff(tm timeNext, tm timeNow);