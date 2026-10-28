#include <windows.h>
#include <stdlib.h>

// The existing ProgressRecords receiver is a pointer-only view of the actual
// native record. Its full layout remains unknown and is not instantiated.
extern const char g_ScoreFilenameAt006579A8[];
class ProgressSaveF247 {public: void SaveScoreFile();};
#define RAW reinterpret_cast<unsigned char*>(this)
void ProgressSaveF247::SaveScoreFile()
{
    HANDLE file=CreateFileA(g_ScoreFilenameAt006579A8,GENERIC_WRITE,0,0,CREATE_ALWAYS,FILE_ATTRIBUTE_NORMAL,0);
    if (file==INVALID_HANDLE_VALUE)
        return;
    {
        SetFilePointer(file,0,0,FILE_BEGIN);
        for (int i=0;i<256;++i) {
            if (rand()<4096)
                RAW[0x16ac6+i]=rand()%256;
        }
        DWORD written;
        WriteFile(file,RAW,0x16710,&written,0);
        WriteFile(file,RAW+0x16a94,8,&written,0);
        WriteFile(file,RAW+0x16710,900,&written,0);
        WriteFile(file,RAW+0x16a9c,40,&written,0);
        WriteFile(file,RAW+0x16ac6,256,&written,0);
        CloseHandle(file);
    }
}
#undef RAW
