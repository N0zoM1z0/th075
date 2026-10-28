#include <windows.h>
// The physical progress record is only accessed via the original byte offsets;
// this source does not assert its complete original type or ownership.
extern const char g_ScoreFilenameAt006579B4[];
class ScoreLoadF248 {public: void LoadScoreFile();};
#define RAW reinterpret_cast<unsigned char*>(this)
void ScoreLoadF248::LoadScoreFile()
{
    HANDLE file=CreateFileA(g_ScoreFilenameAt006579B4,GENERIC_READ,0,0,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,0);
    if (file==INVALID_HANDLE_VALUE) return;
    {
    DWORD read;
    DWORD size=GetFileSize(file,0);
    if (size<=0x11170) {
        SetFilePointer(file,0,0,FILE_BEGIN);
        ReadFile(file,RAW,0xef60,&read,0);
        ReadFile(file,RAW+0x16a94,8,&read,0);
        for (int outer=0;outer<10;++outer) {
            for (int inner=0;inner<10;++inner) {
                ReadFile(file,RAW+0x16710+outer*60+inner*4,4,&read,0);
            }
        }
        ReadFile(file,RAW+0x16a9c,40,&read,0);
        ReadFile(file,RAW+0x16ac6,256,&read,0);
    } else {
        ReadFile(file,RAW,0x16710,&read,0);
        ReadFile(file,RAW+0x16a94,8,&read,0);
        ReadFile(file,RAW+0x16710,900,&read,0);
        ReadFile(file,RAW+0x16a9c,40,&read,0);
        ReadFile(file,RAW+0x16ac6,256,&read,0);
    }
    CloseHandle(file);
    }
}
#undef RAW
