#include "dataAnlyz.h"

DataAnlyz::DataAnlyz(const char* path)
{
    getLogData(path);
    anlyzGeneral();
    resShow();
}
int DataAnlyz::getLogData(const char* path)
{
    //根据日期选择打开文件的路径
    FILE* fp = fopen(path, "r");
    if (NULL == fp)
    {
        printf("failed to open dos.txt\n");
        return 1;
    }

    //按行读取文件，并将act与time分割,存到vector里边
    char nowLine[100];
    while (!feof(fp))
    {
        memset(nowLine, 0, sizeof(nowLine));
        fgets(nowLine, sizeof(nowLine) - 1, fp); // 包含了换行符  
        if (strlen(nowLine) > 5)//防止处理空行
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
        //读取当前动作的时刻，计算其与下一个动作的时间间隔
        string actNow = logDataAll[i].first;
        string timeNow = logDataAll[i].second;
        string timeNext = logDataAll[i + 1].second;
        int tmDiff = timeDiff(str2tm((char*)timeNext.c_str()), str2tm((char*)timeNow.c_str()));
        //将分析结果插入
        map<string, actInfo>::iterator it_find;
        it_find = actInfoOut.find(actNow);
        if (it_find == actInfoOut.end())//如果没找到，则插入
        {
            actInfo actInfoTmp;
            actInfoTmp.tmAndInterval.push_back(make_pair(str2tm((char*)timeNow.c_str()), tmDiff));
            actInfoTmp.tmAll = tmDiff;
            actInfoTmp.count = 1;
            actInfoOut.insert(make_pair(actNow, actInfoTmp));
        }
        else//如果找到了，则只用修改actInfo
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

////分析今天到现在时间为止的行为
//int analyzeNow()
//{
//    //根据日期选择打开文件的路径
//    char pathToday[100];
//    getPathToday(pathToday);
//    FILE* fp = fopen(pathToday, "r");
//    if (NULL == fp)
//    {
//        printf("failed to open dos.txt\n");
//        return 1;
//    }
//
//    //按行读取文件，并将act与time分割,存到vector里边
//    vector<pair<string, string>> actMessageAll;
//    char nowLine[100];
//    while (!feof(fp))
//    {
//        memset(nowLine, 0, sizeof(nowLine));
//        fgets(nowLine, sizeof(nowLine) - 1, fp); // 包含了换行符  
//        if (strlen(nowLine) > 5)//防止处理空行
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
//    //统计各个动作的信息
//    struct actInfo
//    {
//        vector<pair<tm, int>> tmAndInterval;//存储时间和时间间隔键值对的容器
//        int tmAll;//此动作在今天的总时长
//        int count;//此动作在今天的总次数
//    };
//    map<string, actInfo> actInfoAll;//动作和对应信息
//    for (int i = 0; i < actMessageAll.size() - 1; i++)
//    {
//        //读取当前动作的时刻，计算其与下一个动作的时间间隔
//        string actNow = actMessageAll[i].first;
//        string timeNow = actMessageAll[i].second;
//        string timeNext = actMessageAll[i + 1].second;
//        int tmDiff = timeDiff(str2tm((char*)timeNext.c_str()), str2tm((char*)timeNow.c_str()));
//        //将分析结果插入
//        map<string, actInfo>::iterator it_find;
//        it_find = actInfoAll.find(actNow);
//        if (it_find == actInfoAll.end())//如果没找到，则插入
//        {
//            actInfo actInfoTmp;
//            actInfoTmp.tmAndInterval.push_back(make_pair(str2tm((char*)timeNow.c_str()), tmDiff));
//            actInfoTmp.tmAll = tmDiff;
//            actInfoTmp.count = 1;
//            actInfoAll.insert(make_pair(actNow, actInfoTmp));
//        }
//        else//如果找到了，则只用修改actInfo
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