#include "replay/ReplaySegmentedQueueF219.hpp"

template<>
void ReplayRecords::AppendRecord()
{
    if (!fileHandle)
        return;
    ReplayByteQueue::iterator byteInput, byteDataEnd;
    ReplayWordQueue::iterator wordIt, wordSentinel;
    ReplayDwordQueue::iterator dwordHead, frameEnd;
    DWORD writtenBytes;
    unsigned int recordEntries;
    fileHeader.recordOffsets[fileHeader.recordCount] = SetFilePointer(fileHandle, 0, 0, FILE_CURRENT);
    WriteFile(fileHandle, &header.field144, 1, &writtenBytes, 0);
    WriteFile(fileHandle, &header.field145, 1, &writtenBytes, 0);
    WriteFile(fileHandle, &header.field146, 1, &writtenBytes, 0);
    WriteFile(fileHandle, &header.field147, 1, &writtenBytes, 0);
    WriteFile(fileHandle, &header.field148, 1, &writtenBytes, 0);
    WriteFile(fileHandle, &header.field149, 1, &writtenBytes, 0);
    WriteFile(fileHandle, &header.field14A, 1, &writtenBytes, 0);
    WriteFile(fileHandle, &header.field14C, 2, &writtenBytes, 0);
    WriteFile(fileHandle, &header.field14E, 1, &writtenBytes, 0);
    WriteFile(fileHandle, &header.field150, 4, &writtenBytes, 0);
    byteInput = byteInputs.begin();
    byteDataEnd = byteInputs.end();
    recordEntries = byteInputs.size();
    WriteFile(fileHandle, &recordEntries, 4, &writtenBytes, 0);
    for (; byteInput != byteDataEnd; byteInput++)
        WriteFile(fileHandle, &*byteInput, 1, &writtenBytes, 0);
    wordIt = wordInputs.begin();
    wordSentinel = wordInputs.end();
    recordEntries = wordInputs.size();
    WriteFile(fileHandle, &recordEntries, 4, &writtenBytes, 0);
    for (; wordIt != wordSentinel; wordIt++)
        WriteFile(fileHandle, &*wordIt, 2, &writtenBytes, 0);
    byteInput = secondaryInputs.begin();
    byteDataEnd = secondaryInputs.end();
    recordEntries = secondaryInputs.size();
    WriteFile(fileHandle, &recordEntries, 4, &writtenBytes, 0);
    for (; byteInput != byteDataEnd; byteInput++)
        WriteFile(fileHandle, &*byteInput, 1, &writtenBytes, 0);
    dwordHead = dwordInputs.begin();
    frameEnd = dwordInputs.end();
    recordEntries = dwordInputs.size();
    WriteFile(fileHandle, &recordEntries, 4, &writtenBytes, 0);
    for (; dwordHead != frameEnd; dwordHead++)
        WriteFile(fileHandle, &*dwordHead, 4, &writtenBytes, 0);
    ClearFourQueues();
    ++fileHeader.recordCount;
}
