#include "ResultListScene.hpp"
#include "ArchiveCatalog.hpp"
#include "DataArchive.hpp"
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <new>

extern const char g_CardEncodedPatternAt00658170[] = "data\\character\\%s\\cardlist.dat";

void ResultListScene::LoadEncodedCards(const char* character,const char* directory)
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
    file=ResourceLookupF217::FindByName(directory)->SeekNamedEntryWithSize(filename,&fileBytes);
    if(file==INVALID_HANDLE_VALUE) return;
    {
    unsigned int i;
    {
    char* appended;
    content = new char[fileBytes];
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
            records.push_back(0);
            records.back() = new char[index - begin + 1];
            appended=records.back();
            memcpy(appended,content+begin,index-begin);
            appended[index-begin-1]=0;
            begin=index+1;
        }
        ++index;
    }
    delete[] content;
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
