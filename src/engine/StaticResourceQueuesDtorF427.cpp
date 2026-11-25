#include "replay/ReplaySegmentedQueueF219.hpp"

template<>
ReplayRecords::~ReplayRecordsLayoutF219()
{
    ClearFourQueues();
    if (fileHandle) {
        CloseHandle(fileHandle);
        fileHandle = 0;
    }
}
