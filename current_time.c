#include <time.h>
#include <stdio.h>

void logCurrentTimeStamp(FILE* fp_log)
{
    int hours, minutes, seconds, day, month, year;
    time_t now;    
    time(&now);
    struct tm* local = localtime(&now);
    hours = local->tm_hour;
    minutes = local->tm_min;
    seconds = local->tm_sec;
    day = local->tm_mday;
    month = local->tm_mon + 1;
    year = local->tm_year + 1900;    
    fprintf(fp_log, "%02d:%02d:%d %02d:%02d:%02d: ", month, day, year, hours, minutes, seconds);
}
