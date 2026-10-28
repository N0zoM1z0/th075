#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <new>

// Borrowed native game call interfaces; full scene and archive layouts
// are deliberately not inferred from this controller.
class CardArchiveF272 {public: HANDLE OpenEntry(const char* filename,DWORD* fileBytes);};
namespace CardArchiveLookupF272 {CardArchiveF272* __cdecl FindDirectory(const char* directory);}
class CardNameDequeF272 {public: void push_back(char* const& value); char** back();};
extern const char g_CardEncodedPatternAt00658170[];
class CardListEncodedF272 {public: void ClearEntries(); void LoadEncodedCharacterFile(const char*,const char*);};
#define ENTRIES (*reinterpret_cast<CardNameDequeF272*>(reinterpret_cast<unsigned char*>(this)+0x18))
void CardListEncodedF272::LoadEncodedCharacterFile(const char* character,const char* directory)
{
    HANDLE file;
    {
    unsigned char delta;
    {
    DWORD readBytes;
    {
    unsigned int begin;
    {
    DWORD fileBytes;
    {
    char* content;
    {
    unsigned int index;
    {
    unsigned char key;
    {
    char filename[260];
    ClearEntries();
    sprintf(filename,g_CardEncodedPatternAt00658170,character);
    file=CardArchiveLookupF272::FindDirectory(directory)->OpenEntry(filename,&fileBytes);
    if(file==INVALID_HANDLE_VALUE) return;
    {
    unsigned int i;
    {
    char* appended;
    {
    char* allocatedContent=reinterpret_cast<char*>(::operator new(fileBytes));
    content=allocatedContent;
    }
    ReadFile(file,content,fileBytes,&readBytes,0);
    key=0x60;
    delta=0x61;
    for(i=0;i<fileBytes;++i) {
        content[i]=content[i]^key;
        key+=delta;
        delta+='A';
    }
    begin=0;
    index=0;
    while(index<fileBytes) {
        if(content[index]=='\n') {
            char* empty=0;
            ENTRIES.push_back(empty);
            {
            char* allocatedName=reinterpret_cast<char*>(::operator new(index-begin+1));
            *ENTRIES.back()=allocatedName;
            }
            appended=*ENTRIES.back();
            memcpy(appended,content+begin,index-begin);
            appended[index-begin-1]=0;
            begin=index+1;
        }
        ++index;
    }
    {
       void* completedBuffer=content;
       free(completedBuffer);
    }
    }
    }
    }
    }
    }
    }
    }
    }
}
}
}
#undef ENTRIES
