#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <new>

// Native-observed deque access and file IO only: no fabricated full owner.
extern const char g_CardPlainPathAt00658150[];
class CardNameDequeF273 {
public:
    void push_back(char* const& value);
    char** back();
};
class CardListPlainF273 {
public:
    void ClearEntries();
    void LoadCharacterFile(const char* character);
};
#define ENTRIES (*reinterpret_cast<CardNameDequeF273*>(reinterpret_cast<unsigned char*>(this)+0x18))
void CardListPlainF273::LoadCharacterFile(const char* character)
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
                                {
                                    char* allocatedContent=reinterpret_cast<char*>(::operator new(size));
                                    content=allocatedContent;
                                }
                                ReadFile(file,content,size,&readBytes,0);
                                CloseHandle(file);
                                begin=0;
                                index=0;
                                while(index<size) {
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
#undef ENTRIES
