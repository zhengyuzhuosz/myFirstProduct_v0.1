#include "dataAnlyz.h"

DataAnlyz::DataAnlyz(const char* path)
{
    getLogData(path);
    anlyzGeneral();
    resShow();
}
int DataAnlyz::getLogData(const char* path)
{
    //��������ѡ����ļ���·��
    FILE* fp = fopen(path, "r");
    if (NULL == fp)
    {
        printf("failed to open dos.txt\n");
        return 1;
    }

    //���ж�ȡ�ļ�������act��time�ָ�,�浽vector���
    char nowLine[100];
    while (!feof(fp))
    {
        memset(nowLine, 0, sizeof(nowLine));
        fgets(nowLine, sizeof(nowLine) - 1, fp); // �����˻��з�  
        if (strlen(nowLine) > 5)//��ֹ�������
        {
            char act[20];
            char time[50];
            splitActMessage(act, time, nowLine);
            string strAct = act;
            string strTime = time;
            logDataAll.push_back(make_pair(strAct, strTime));
        }
    }
    fclose(fp);
}
int DataAnlyz::anlyzGeneral()
{
    for (int i = 0; i < logDataAll.size() - 1; i++)
    {
        //��ȡ��ǰ������ʱ�̣�����������һ��������ʱ����
        string actNow = logDataAll[i].first;
        string timeNow = logDataAll[i].second;
        string timeNext = logDataAll[i + 1].second;
        int tmDiff = timeDiff(str2tm((char*)timeNext.c_str()), str2tm((char*)timeNow.c_str()));
        //�������������
        map<string, actInfo>::iterator it_find;
        it_find = actInfoOut.find(actNow);
        if (it_find == actInfoOut.end())//���û�ҵ��������
        {
            actInfo actInfoTmp;
            actInfoTmp.tmAndInterval.push_back(make_pair(str2tm((char*)timeNow.c_str()), tmDiff));
            actInfoTmp.tmAll = tmDiff;
            actInfoTmp.count = 1;
            actInfoOut.insert(make_pair(actNow, actInfoTmp));
        }
        else//����ҵ��ˣ���ֻ���޸�actInfo
        {
            it_find->second.tmAndInterval.push_back(make_pair(str2tm((char*)timeNow.c_str()), tmDiff));
            it_find->second.tmAll += tmDiff;
            it_find->second.count++;
        }
    }
    return 0;
}
int DataAnlyz::resShow()
{
    for (auto iter = actInfoOut.begin(); iter != actInfoOut.end(); ++iter)
    {
        cout << "action:\t\t" << iter->first << endl;
        cout << "count:\t\t" << iter->second.count << endl;
        cout << "IntervalAll:\t" << iter->second.tmAll << endl;
        vector<pair<tm, int>> tmAndInterval = iter->second.tmAndInterval;
        for (int i = 0; i < tmAndInterval.size(); i++)
        {
            cout << "time: " << tm2str(tmAndInterval[i].first) << "\t" << "interval: " << tmAndInterval[i].second << endl;
        }
        cout << "--------------------------" << endl;
    }
    return 0;
}
int actNow(const char action)
{
    if (!isalpha(action))
        return -1;
    char actMessage[100];
    char tNow[MaxTimeChar];
    getTimeNow(tNow);

    switch (action)
    {
    case 's':
        snprintf(actMessage,
            100,
            "%05s=%s\n",
            "sleep",
            tNow
            );
        break;
    case 'w':
        snprintf(actMessage,
            100,
            "%05s=%s\n",
            "work",
            tNow
            );
        break;
    case 'p':
        snprintf(actMessage,
            100,
            "%05s=%s\n",
            "phone",
            tNow
            );
        break;
    }
    printf("%s", actMessage);

    char pathToday[100];
    getPathToday(pathToday);
    FILE* file = fopen(pathToday, "a");
    if (file == NULL)
    {
        printf("open error!\n");
        return 0;
    }
    fprintf(file, "%s\n", actMessage);
    fclose(file);
    return 0;
}
int getPathToday(char* pathToday)
{
    snprintf(
        pathToday,
        100,
        "%d.%d.%d.txt",
        getTimeYear(),
        getTimeMonth(),
        getTimeDay()
        );
    return 0;
}

////�������쵽����ʱ��Ϊֹ����Ϊ
//int analyzeNow()
//{
//    //��������ѡ����ļ���·��
//    char pathToday[100];
//    getPathToday(pathToday);
//    FILE* fp = fopen(pathToday, "r");
//    if (NULL == fp)
//    {
//        printf("failed to open dos.txt\n");
//        return 1;
//    }
//
//    //���ж�ȡ�ļ�������act��time�ָ�,�浽vector���
//    vector<pair<string, string>> actMessageAll;
//    char nowLine[100];
//    while (!feof(fp))
//    {
//        memset(nowLine, 0, sizeof(nowLine));
//        fgets(nowLine, sizeof(nowLine) - 1, fp); // �����˻��з�  
//        if (strlen(nowLine) > 5)//��ֹ�������
//        {
//            char act[20];
//            char time[50];
//            splitActMessage(act, time, nowLine);
//            string strAct = act;
//            string strTime = time;
//            actMessageAll.push_back(make_pair(strAct, strTime));
//        }
//    }
//
//    //ͳ�Ƹ�����������Ϣ
//    struct actInfo
//    {
//        vector<pair<tm, int>> tmAndInterval;//�洢ʱ���ʱ������ֵ�Ե�����
//        int tmAll;//�˶����ڽ������ʱ��
//        int count;//�˶����ڽ�����ܴ���
//    };
//    map<string, actInfo> actInfoAll;//�����Ͷ�Ӧ��Ϣ
//    for (int i = 0; i < actMessageAll.size() - 1; i++)
//    {
//        //��ȡ��ǰ������ʱ�̣�����������һ��������ʱ����
//        string actNow = actMessageAll[i].first;
//        string timeNow = actMessageAll[i].second;
//        string timeNext = actMessageAll[i + 1].second;
//        int tmDiff = timeDiff(str2tm((char*)timeNext.c_str()), str2tm((char*)timeNow.c_str()));
//        //�������������
//        map<string, actInfo>::iterator it_find;
//        it_find = actInfoAll.find(actNow);
//        if (it_find == actInfoAll.end())//���û�ҵ��������
//        {
//            actInfo actInfoTmp;
//            actInfoTmp.tmAndInterval.push_back(make_pair(str2tm((char*)timeNow.c_str()), tmDiff));
//            actInfoTmp.tmAll = tmDiff;
//            actInfoTmp.count = 1;
//            actInfoAll.insert(make_pair(actNow, actInfoTmp));
//        }
//        else//����ҵ��ˣ���ֻ���޸�actInfo
//        {
//            it_find->second.tmAndInterval.push_back(make_pair(str2tm((char*)timeNow.c_str()), tmDiff));
//            it_find->second.tmAll += tmDiff;
//            it_find->second.count++;
//        }
//    }
//    fclose(fp);
//    return 0;
//}


char* splitActMessage(char* strAct, char* strTime, const char* strSrc)
{
    if ((strAct == NULL) || (strSrc == NULL))
        return NULL;
    char* strDestCopy = strAct;

    while (1)
    {
        if (*strSrc == '=')
            break;
        *strAct = *strSrc;
        strAct++;
        strSrc++;
    }
    *strAct = '\0';
    strSrc++;
    while (1)
    {
        char tmp;
        tmp = *strTime = *strSrc;
        strTime++;
        strSrc++;
        if (tmp == '\0')
            break;
    }
    return strDestCopy;
}