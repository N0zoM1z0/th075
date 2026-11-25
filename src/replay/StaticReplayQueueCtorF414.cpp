#include "replay/ReplaySegmentedQueueF219.hpp"

template<>
ReplayRecords::ReplayRecordsLayoutF219()
{
    fileHandle = 0;
}

ReplayRecords g_ReplayRecords;
