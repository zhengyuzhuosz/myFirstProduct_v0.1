#pragma once
//���ļ���ֻ��Կ����ߵĺ�̨����
#include <stdio.h>
#include <string>
using namespace std;

//���ڱ�����־�ļ����ڸ�����֮ǰ���ȱ��ݣ���ֹ��־��ʧ
int logCopy(const char* srcPath, const char* dstPath)
{
	//��ȡ��ǰ�û����û���
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

	//�����û�����Ӧ���ļ�Ŀ¼
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