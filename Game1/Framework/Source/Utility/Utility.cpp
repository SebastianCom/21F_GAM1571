#include "CoreHeaders.h"

double GetSystemTime()
{
    unsigned __int64 freq;
    unsigned __int64 time;

    QueryPerformanceFrequency( (LARGE_INTEGER*)&freq );
    QueryPerformanceCounter( (LARGE_INTEGER*)&time );

    double timeseconds = (double)time / freq;

    return timeseconds;
}

double GetSystemTimeSinceGameStart()
{
    static double starttime = -1;

    if( starttime == -1 )
        starttime = GetSystemTime();

    return GetSystemTime() - starttime;
}