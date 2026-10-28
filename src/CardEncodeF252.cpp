#include <windows.h>
#include <stdio.h>

// Observed CardList file converter: original scene ownership is borrowed,
// no complete class or record layout is inferred.
extern const char g_CardSourceTextPatternAt00658190[];
extern const char g_CardEncodedPatternAt006581B0[];
class CardEncoderF252 {
public:
    void EncodeCharacterFile(const char* character);
};
void CardEncoderF252::EncodeCharacterFile(const char* character)
{
    HANDLE file;
    DWORD bytesRead;
    {
    DWORD fileBytes;
    {
    char* content;
    {
    char filepath[260];
    sprintf(filepath,g_CardSourceTextPatternAt00658190,character);
    file=CreateFileA(filepath,GENERIC_READ,0,0,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,0);
    if (file==INVALID_HANDLE_VALUE) return;
    fileBytes=GetFileSize(file,0);
    content=new char[fileBytes];

    ReadFile(file,content,fileBytes,&bytesRead,0);
    CloseHandle(file);
    sprintf(filepath,g_CardEncodedPatternAt006581B0,character);
    file=CreateFileA(filepath,GENERIC_WRITE,0,0,CREATE_ALWAYS,FILE_ATTRIBUTE_NORMAL,0);
    if (file!=INVALID_HANDLE_VALUE) {
        unsigned char delta;
        {
          unsigned char key=0x60;
          delta=0x61;
          for (unsigned int index=0;index<fileBytes;++index) {
            content[index]=content[index]^key;
            key+=delta;
            delta+=0x41;
        }
        }
        WriteFile(file,content,fileBytes,&bytesRead,0);
        CloseHandle(file);
    }
    }
    delete[] content;
    }
    }
}
