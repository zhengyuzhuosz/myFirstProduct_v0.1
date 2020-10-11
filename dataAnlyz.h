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
	vector<pair<tm, int>> tmAndInterval;//�洢ʱ���ʱ������ֵ�Ե�����
	int tmAll;//�˶����ڽ������ʱ��
	int count;//�˶����ڽ�����ܴ���
};

class DataAnlyz {
public:
	DataAnlyz(const char* path);

	//int setDataPath();

	int getLogData(const char* path);

	int anlyzGeneral();

	int resShow();

	vector<pair<string, string>> logDataAll;

	map<string, actInfo> actInfoOut;//�����Ͷ�Ӧ��Ϣ
};

//int actNow(const char action);
////�������������
//int analyzeNow();
////����ǰһ�������
//int anlyzDayLast();
////�������ܵ�����
//int anlyzWeekNow();
////�������µ�����
//int anlyzMonNow();
////������һ�������
//int anlyzDay(const char* path);
////������һ�ܵ�����
//int anlyzWeek(const char* path);
////������һ�µ�����
//int anlyzMon(const char* path);

int getPathToday(char* pathToday);

char* splitActMessage(char* strAct, char* strTime, const char* strSrc);
