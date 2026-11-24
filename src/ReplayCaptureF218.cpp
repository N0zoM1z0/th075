#include "ReplaySegmentedQueueF219.hpp"
#include <time.h>
extern const char g_ReplayTempAt006578C4[];
extern const char g_ReplayErrorCaptionAt006578D8[];
extern const char g_ReplayErrorTextAt006578E0[];
template<>
void ReplayRecords::BeginCapture()
{
    time_t stamp;
    time(&stamp);
    tm* calendar=localtime(&stamp);
    fileHeader.day = calendar->tm_mday;
    fileHeader.month = calendar->tm_mon+1;
    fileHeader.recordCount = 0;
    fileHeader.recordOffsets[0] = 0;
    for (int index=0; index<8; ++index)
        fileHeader.playerName[index]=100;
    ClearFourQueues();
    if (fileHandle)
        CloseHandle(fileHandle);
    fileHandle = CreateFileA(g_ReplayTempAt006578C4,
                GENERIC_READ|GENERIC_WRITE,0,0,CREATE_ALWAYS,FILE_ATTRIBUTE_NORMAL,0);
    if (fileHandle==INVALID_HANDLE_VALUE)
        MessageBoxA(0,g_ReplayErrorTextAt006578E0,
                    g_ReplayErrorCaptionAt006578D8,0);
}
