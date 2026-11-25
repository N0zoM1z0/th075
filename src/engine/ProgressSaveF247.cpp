#include <windows.h>
#include "engine/GameProgress.hpp"
#include <stdlib.h>

extern const char g_ScoreFilenameAt006579A8[] = "score.dat";
void GameProgress::SaveScoreFile()
{
    HANDLE file=CreateFileA(g_ScoreFilenameAt006579A8,GENERIC_WRITE,0,0,CREATE_ALWAYS,FILE_ATTRIBUTE_NORMAL,0);
    if (file==INVALID_HANDLE_VALUE)
        return;
    {
        SetFilePointer(file,0,0,FILE_BEGIN);
        for (int i=0;i<256;++i) {
            if (rand()<4096)
                randomizedSaveTail[i]=rand()%256;
        }
        DWORD written;
        WriteFile(file,characters,sizeof(characters),&written,0);
        WriteFile(file,workingPlayerName,sizeof(workingPlayerName),&written,0);
        WriteFile(file,matchWinsByFighterPair,sizeof(matchWinsByFighterPair),&written,0);
        WriteFile(file,unlockBits,sizeof(unlockBits),&written,0);
        WriteFile(file,randomizedSaveTail,sizeof(randomizedSaveTail),&written,0);
        CloseHandle(file);
    }
}
