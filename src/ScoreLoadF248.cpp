#include <windows.h>
#include "GameProgress.hpp"
extern const char g_ScoreFilenameAt006579B4[];
void GameProgress::LoadScoreFile()
{
    HANDLE file=CreateFileA(g_ScoreFilenameAt006579B4,GENERIC_READ,0,0,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,0);
    if (file==INVALID_HANDLE_VALUE) return;
    {
    DWORD read;
    DWORD size=GetFileSize(file,0);
    if (size<=0x11170) {
        SetFilePointer(file,0,0,FILE_BEGIN);
        ReadFile(file,characters,0xef60,&read,0);
        ReadFile(file,field16A94,sizeof(field16A94),&read,0);
        for (int outer=0;outer<10;++outer) {
            for (int inner=0;inner<10;++inner) {
                ReadFile(file,&modeCounts[outer][inner],4,&read,0);
            }
        }
        ReadFile(file,unlockBits,sizeof(unlockBits),&read,0);
        ReadFile(file,field16AC6,sizeof(field16AC6),&read,0);
    } else {
        ReadFile(file,characters,sizeof(characters),&read,0);
        ReadFile(file,field16A94,sizeof(field16A94),&read,0);
        ReadFile(file,modeCounts,sizeof(modeCounts),&read,0);
        ReadFile(file,unlockBits,sizeof(unlockBits),&read,0);
        ReadFile(file,field16AC6,sizeof(field16AC6),&read,0);
    }
    CloseHandle(file);
    }
}
