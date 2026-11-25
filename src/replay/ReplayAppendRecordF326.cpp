#include "replay/ReplayRecords.hpp"

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
    WriteFile(fileHandle, &recordHeader.secondaryFighter, 1, &writtenBytes, 0);
    WriteFile(fileHandle, &recordHeader.secondaryFirstSpellCard, 1, &writtenBytes, 0);
    WriteFile(fileHandle, &recordHeader.secondarySecondSpellCard, 1, &writtenBytes, 0);
    WriteFile(fileHandle, &recordHeader.secondaryPalette, 1, &writtenBytes, 0);
    WriteFile(fileHandle, &recordHeader.secondaryAutoGuard, 1, &writtenBytes, 0);
    WriteFile(fileHandle, &recordHeader.secondaryDamageSetting, 1, &writtenBytes, 0);
    WriteFile(fileHandle, &recordHeader.stage, 1, &writtenBytes, 0);
    WriteFile(fileHandle, &recordHeader.startingHealth, 2, &writtenBytes, 0);
    WriteFile(fileHandle, &recordHeader.remainingLives, 1, &writtenBytes, 0);
    WriteFile(fileHandle, &recordHeader.startingScore, 4, &writtenBytes, 0);
    byteInput = frameInputBits.begin();
    byteDataEnd = frameInputBits.end();
    recordEntries = frameInputBits.size();
    WriteFile(fileHandle, &recordEntries, 4, &writtenBytes, 0);
    for (; byteInput != byteDataEnd; byteInput++)
        WriteFile(fileHandle, &*byteInput, 1, &writtenBytes, 0);
    wordIt = randomSamplesAndAiTimers.begin();
    wordSentinel = randomSamplesAndAiTimers.end();
    recordEntries = randomSamplesAndAiTimers.size();
    WriteFile(fileHandle, &recordEntries, 4, &writtenBytes, 0);
    for (; wordIt != wordSentinel; wordIt++)
        WriteFile(fileHandle, &*wordIt, 2, &writtenBytes, 0);
    byteInput = aiCommandsAndGuardChoices.begin();
    byteDataEnd = aiCommandsAndGuardChoices.end();
    recordEntries = aiCommandsAndGuardChoices.size();
    WriteFile(fileHandle, &recordEntries, 4, &writtenBytes, 0);
    for (; byteInput != byteDataEnd; byteInput++)
        WriteFile(fileHandle, &*byteInput, 1, &writtenBytes, 0);
    dwordHead = timedBattleCommands.begin();
    frameEnd = timedBattleCommands.end();
    recordEntries = timedBattleCommands.size();
    WriteFile(fileHandle, &recordEntries, 4, &writtenBytes, 0);
    for (; dwordHead != frameEnd; dwordHead++)
        WriteFile(fileHandle, &*dwordHead, 4, &writtenBytes, 0);
    ClearFourQueues();
    ++fileHeader.recordCount;
}
