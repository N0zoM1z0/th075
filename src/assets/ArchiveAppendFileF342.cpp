#include "assets/DataArchive.hpp"
#include <string.h>

void DataArchiveF481::AppendReadableFile(const char* filename)
{
    HANDLE file=CreateFileA(filename, GENERIC_READ, 0,0,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,0);
    if (file==INVALID_HANDLE_VALUE) return;
    ArchiveWireEntryF250 entry;
    entry.sourceOffset=0;
    entry.sourceSize=GetFileSize(file,0);
    strcpy(reinterpret_cast<char*>(entry.filename), filename);
    CloseHandle(file);
    entries.push_back(entry);
}
