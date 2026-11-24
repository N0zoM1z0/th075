#include "ReplaySegmentedQueueF219.hpp"
#include <stdio.h>
#include <io.h>
extern const char g_ReplayPathFormatAt00657918[];
template<>
int ReplayRecords::FindAvailablePath(char* path)
{
    int candidate;
    for (candidate=0; candidate<1000; ++candidate) {
        sprintf(path,g_ReplayPathFormatAt00657918,candidate);
        if (_access(path,0)==-1)
            break;
    }
    return candidate;
}
