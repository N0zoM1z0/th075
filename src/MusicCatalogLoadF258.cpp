#include <windows.h>
#include <stdlib.h>
#include <string.h>
#include <new>

// The original scene is only accessed through observed field offsets.
// A complete owning MusicRoom type, archive layout, and record class
// are not assumed by this reconstructed C++ translation unit.
// Real source-level lifetimes and allocation transfers are kept separate:
// VC7.1 reuses distinct native stack slots for all four allocations and
// the final buffer release. This file owns no CRT/archive helper bodies.
class MusicArchiveF215 { public: HANDLE OpenEntry(const char* filename, DWORD* bytes); };
namespace ArchiveLookupF215 { MusicArchiveF215* __cdecl FindDirectory(const char* directory); }
extern const char g_MusicCatalogDirectoryAt00657C78[];
extern const char g_MusicCatalogFilenameAt00657C80[];
class MusicCatalogF215 {public: void LoadCatalog();};
#define FIELD(type,off) (*reinterpret_cast<type*>(reinterpret_cast<unsigned char*>(this)+(off)))
#define ENTRY(type,off) FIELD(type, 16*FIELD(signed char,0x3dc) + (off))
void MusicCatalogF215::LoadCatalog()
{
    HANDLE file;
    {
    unsigned int cursor;
    {
    unsigned char delta;
    {
    DWORD readBytes;
    {
    unsigned int begin;
    {
    DWORD fileBytes;
    file = ArchiveLookupF215::FindDirectory(g_MusicCatalogDirectoryAt00657C78)
           ->OpenEntry(g_MusicCatalogFilenameAt00657C80, &fileBytes);
    if (file == INVALID_HANDLE_VALUE) return;
    {
    char* buffer;
    {
    unsigned int last;
    {
    signed char column;
    {
    unsigned char key;
    {
    signed char quote;
    {
    unsigned int i;
    {
        char* allocated = reinterpret_cast<char*>(::operator new(fileBytes));
        buffer = allocated;
    }
    ReadFile(file,buffer,fileBytes,&readBytes,0);
    key=0x5c;
    delta=0x5a;
    for (i=0;i<fileBytes;++i) {
        buffer[i]=buffer[i]^key;
        key+=delta;
        delta+='=';
    }
    FIELD(signed char,0x3dc)=0;
    cursor=0;
    column=0;
    while (cursor<fileBytes) {
        if (buffer[cursor]=='"') {
            ++cursor;
            quote=1;
            begin=cursor;
        } else {
            quote=0;
            begin=cursor;
        }
        last=begin;
        while (buffer[cursor]!=',' && buffer[cursor]!='\n') {
            switch (quote) {
            case 0:
                ++last;
                break;
            case 1:
                if (buffer[cursor]=='"') quote=2;
                else ++last;
                break;
            }
            ++cursor;
        }
        switch (column) {
        case 0:
            while (begin!=last) {
                ENTRY(signed char,0x1c)=ENTRY(signed char,0x1c)*10-48+buffer[begin];
                ++begin;
            }
            break;
        case 1:
            {
            char* allocatedName = reinterpret_cast<char*>(::operator new(last-begin+1));
            ENTRY(char*,0x24)=allocatedName;
            }
            memcpy(ENTRY(char*,0x24),buffer+begin,last-begin);
            ENTRY(char*,0x24)[last-begin]=0;
            break;
        case 2:
            {
            char* allocatedTitle = reinterpret_cast<char*>(::operator new(last-begin+1));
            ENTRY(char*,0x20)=allocatedTitle;
            }
            memcpy(ENTRY(char*,0x20),buffer+begin,last-begin);
            ENTRY(char*,0x20)[last-begin]=0;
            break;
        case 3:
            {
            char* allocatedExtra = reinterpret_cast<char*>(::operator new(last-begin+1));
            ENTRY(char*,0x28)=allocatedExtra;
            }
            memcpy(ENTRY(char*,0x28),buffer+begin,last-begin);
            ENTRY(char*,0x28)[last-begin]=0;
            ++FIELD(signed char,0x3dc);
            break;
        }
        if (buffer[cursor]=='\n') column=0;
        else ++column;
        ++cursor;
    }
    {
        void* completedBuffer=buffer;
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
}
#undef ENTRY
#undef FIELD
