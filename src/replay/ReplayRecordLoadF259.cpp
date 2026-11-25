#include "replay/ReplayRecords.hpp"

template<>
void ReplayRecords::LoadRecord(signed char slot)
{
    unsigned int i;
    {
    unsigned int dwordItem;
    {
    // The file contains an unsigned 16-bit word. Insertion into the signed
    // 16-bit collection materializes an actual compiler temporary (EBP-1E).
    unsigned short rawWord;
    {
    unsigned int entries;
    {
    HANDLE handle;
    {
    unsigned char item;
    {
    DWORD bytesRead;
    {
    handle = CreateFileA(filePath, GENERIC_READ,0,0,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,0);
    entries = 0;
    SetFilePointer(handle, fileHeader.recordOffsets[slot] + 0x3c, 0, FILE_BEGIN);
    ReadFile(handle,&recordHeader.secondaryFighter,1,&bytesRead,0);
    ReadFile(handle,&recordHeader.secondaryFirstSpellCard,1,&bytesRead,0);
    ReadFile(handle,&recordHeader.secondarySecondSpellCard,1,&bytesRead,0);
    ReadFile(handle,&recordHeader.secondaryPalette,1,&bytesRead,0);
    ReadFile(handle,&recordHeader.secondaryAutoGuard,1,&bytesRead,0);
    ReadFile(handle,&recordHeader.secondaryDamageSetting,1,&bytesRead,0);
    ReadFile(handle,&recordHeader.stage,1,&bytesRead,0);
    ReadFile(handle,&recordHeader.startingHealth,2,&bytesRead,0);
    ReadFile(handle,&recordHeader.remainingLives,1,&bytesRead,0);
    ReadFile(handle,&recordHeader.startingScore,4,&bytesRead,0);
    ReadFile(handle,&entries,4,&bytesRead,0);
    frameInputBits.clear();
    for (i=0;i<entries;++i) {
        ReadFile(handle,&item,1,&bytesRead,0);
        frameInputBits.push_back(item);
    }
    ReadFile(handle,&entries,4,&bytesRead,0);
    randomSamplesAndAiTimers.clear();
    for (i=0;i<entries;++i) {
        ReadFile(handle,&rawWord,2,&bytesRead,0);
        randomSamplesAndAiTimers.push_back(static_cast<short>(rawWord));
    }
    ReadFile(handle,&entries,4,&bytesRead,0);
    aiCommandsAndGuardChoices.clear();
    for (i=0;i<entries;++i) {
        ReadFile(handle,&item,1,&bytesRead,0);
        aiCommandsAndGuardChoices.push_back(item);
    }
    ReadFile(handle,&entries,4,&bytesRead,0);
    timedBattleCommands.clear();
    for (i=0;i<entries;++i) {
        ReadFile(handle,&dwordItem,4,&bytesRead,0);
        timedBattleCommands.push_back(dwordItem);
    }
    CloseHandle(handle);
    }
    }
    }
    }
    }
    }
    }
}
