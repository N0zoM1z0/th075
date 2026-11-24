#include "ReplaySegmentedQueueF219.hpp"

template<>
void ReplayRecords::ReadSnapshotHeader()
{
    HANDLE file = CreateFileA(filePath,
                                GENERIC_READ,0,0,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,0);
    DWORD bytesRead;
    ReadFile(file,&fileHeader, sizeof(fileHeader),&bytesRead,0);
    CloseHandle(file);
}
