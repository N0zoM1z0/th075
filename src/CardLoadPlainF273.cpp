#include "ResultListScene.hpp"
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <new>

extern const char g_CardPlainPathAt00658150[] = "data\\character\\%s\\cardlist.txt";

void ResultListScene::LoadPlainCards(const char* character)
{
    HANDLE file;
    {
        DWORD readBytes;
        {
            unsigned int begin;
            {
                DWORD size;
                {
                    char* content;
                    {
                        unsigned int index;
                        {
                            char filename[260];
                            ClearEntries();
                            sprintf(filename,g_CardPlainPathAt00658150,character);
                            file=CreateFileA(filename,GENERIC_READ,0,0,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,0);
                            if(file==INVALID_HANDLE_VALUE) return;
                            size=GetFileSize(file,0);
                            {
                                char* appended;
                                content = new char[size];
                                ReadFile(file,content,size,&readBytes,0);
                                CloseHandle(file);
                                begin=0;
                                index=0;
                                while(index<size) {
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
