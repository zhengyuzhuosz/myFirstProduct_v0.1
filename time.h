#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <time.h>
#include <stdio.h>
#include <string.h>
#define MaxTimeChar 100

int getTimeNow(char* input);

int getTimeYear();

int getTimeMonth();

int getTimeDay();

tm str2tm(const char* input);

int timeDiff(tm timeNext, tm timeNow);