#include "mytime.h"

int getTimeNow(char* input)
{
    time_t now = time(NULL);
    struct tm* w = NULL;
    time(&now);
    localtime_s(w,&now);
    char timeNow[MaxTimeChar];
    snprintf(timeNow, MaxTimeChar,
        "%04d.%02d.%02d %02d:%02d:%02d\n",
        w->tm_year + 1900,
        w->tm_mon + 1,
        w->tm_mday,
        w->tm_hour,
        w->tm_min,
        w->tm_sec);
    strncpy_s(input, MaxTimeChar, timeNow, MaxTimeChar);
    return 0;
}
int getTimeYear()
{
    time_t now = time(nullptr);
    struct tm w;
    time(&now);
    localtime_s(&w, &now);
    return w.tm_year + 1900;
}
int getTimeMonth()
{
    time_t now = time(nullptr);
    struct tm w;
    time(&now);
    localtime_s(&w, &now);
    return w.tm_mon + 1;
}
int getTimeDay()
{
    time_t now = time(nullptr);
    struct tm w;
    time(&now);
    localtime_s(&w, &now);
    return w.tm_mday;
}

tm str2tm(const char* input)
{
    struct tm time = { 0 };
    int year, month, day, hour, min, sec;
    const char* tmp = input;
    while (1)
    {
        if (*tmp == '.')
        {
            sscanf_s(input,
                "%04d.%02d.%02d %02d:%02d:%02d\n",
                &year,
                &month,
                &day,
                &hour,
                &min,
                &sec
                );
            break;
        }
        if (*tmp == '/')
        {
            sscanf_s(input,
                "%04d/%02d/%02d %02d:%02d:%02d\n",
                &year,
                &month,
                &day,
                &hour,
                &min,
                &sec
                );
            break;
        }
        tmp++;
    }
    time.tm_year = year - 1900;
    time.tm_mon = month - 1;
    time.tm_mday = day;
    time.tm_hour = hour;
    time.tm_min = min;
    time.tm_sec = sec;
    return time;
}
string tm2str(tm input)
{
    char timeChar[100];
    snprintf(timeChar, MaxTimeChar,
        "%04d.%02d.%02d %02d:%02d:%02d",
        input.tm_year + 1900,
        input.tm_mon + 1,
        input.tm_mday,
        input.tm_hour,
        input.tm_min,
        input.tm_sec);
    string output = timeChar;
    return output;
}
//返回值的基本单位为分钟,time1大,time2小
int timeDiff(tm timeNext, tm timeNow)
{
    int yearDiff = timeNext.tm_year - timeNow.tm_year;
    int monthDiff = timeNext.tm_mon - timeNow.tm_mon;
    int dayDiff = timeNext.tm_mday - timeNow.tm_mday;
    int hourDiff = timeNext.tm_hour - timeNow.tm_hour;
    int minDiff = timeNext.tm_min - timeNow.tm_min;
    int tmDiff = yearDiff * 365 * 24 * 60 + monthDiff * 30 * 24 * 60 + dayDiff * 24 * 60 + hourDiff * 60 + minDiff;
    return tmDiff;
}