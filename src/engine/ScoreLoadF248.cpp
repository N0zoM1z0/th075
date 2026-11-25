#include <windows.h>
#include "engine/GameProgress.hpp"
extern const char g_ScoreFilenameAt006579B4[] = "score.dat";
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
        ReadFile(file,workingPlayerName,sizeof(workingPlayerName),&read,0);
        for (int outer=0;outer<10;++outer) {
            for (int inner=0;inner<10;++inner) {
                ReadFile(file,&matchWinsByFighterPair[outer][inner],4,&read,0);
            }
        }
        ReadFile(file,unlockBits,sizeof(unlockBits),&read,0);
        ReadFile(file,randomizedSaveTail,sizeof(randomizedSaveTail),&read,0);
    } else {
        ReadFile(file,characters,sizeof(characters),&read,0);
        ReadFile(file,workingPlayerName,sizeof(workingPlayerName),&read,0);
        ReadFile(file,matchWinsByFighterPair,sizeof(matchWinsByFighterPair),&read,0);
        ReadFile(file,unlockBits,sizeof(unlockBits),&read,0);
        ReadFile(file,randomizedSaveTail,sizeof(randomizedSaveTail),&read,0);
    }
    CloseHandle(file);
    }
}
