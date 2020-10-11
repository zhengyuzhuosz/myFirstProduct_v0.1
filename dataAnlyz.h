#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <ctype.h>
#include <vector>
#include <string>
#include <map>
#include <utility>
#include "mytime.h"
#include <iostream>

using namespace std;

struct actInfo
{
	vector<pair<tm, int>> tmAndInterval;//存储时间和时间间隔键值对的容器
	int tmAll;//此动作在今天的总时长
	int count;//此动作在今天的总次数
};

class DataAnlyz {
public:
	DataAnlyz(const char* path);

	//int setDataPath();

	int getLogData(const char* path);

	int anlyzGeneral();

	int resShow();

	vector<pair<string, string>> logDataAll;

	map<string, actInfo> actInfoOut;//动作和对应信息
};

//int actNow(const char action);
////分析当天的数据
//int analyzeNow();
////分析前一天的数据
//int anlyzDayLast();
////分析当周的数据
//int anlyzWeekNow();
////分析当月的数据
//int anlyzMonNow();
////分析任一天的数据
//int anlyzDay(const char* path);
////分析任一周的数据
//int anlyzWeek(const char* path);
////分析任一月的数据
//int anlyzMon(const char* path);

int getPathToday(char* pathToday);

char* splitActMessage(char* strAct, char* strTime, const char* strSrc);
