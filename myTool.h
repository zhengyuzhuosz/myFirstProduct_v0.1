#pragma once
//此文件是只针对开发者的后台操作
#include <stdio.h>
#include <string>
using namespace std;

//用于备份日志文件，在更改日之前都先备份，防止日志丢失
int logCopy(const char* srcPath, const char* dstPath)
{
	//获取当前用户的用户名
	FILE* fp = NULL;
	char name[100] = { '0' };
	fp = popen("whoami", "r");
	if (fp == NULL)
	{
		printf("popen error!\n");
		return -1;
	}
	while (fgets(name, sizeof(name), fp) != NULL);
	pclose(fp);

	//创建用户名对应的文件目录
	string operate = "mkdir ";
	string operName = name;
	operate = operate + operName;	
	system((char*)operate.c_str());

	char filename[100] = { '0' };
	fp = popen("ls", "r");
	if (fp == NULL)
	{
		printf("popen error!\n");
		return -1;
	}
	while (fgets(filename, sizeof(filename), fp) != NULL);
	{
		if (isdigit(filename[0]))//if the filename is the log file
		{
			string operate = "cp ";
			operate = operate + filename + " ";
			operate = operate + name + "/";
			system((char*)operate.c_str());
		}
	}
	pclose(fp);


	return 0;
}