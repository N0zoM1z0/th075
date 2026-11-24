#pragma once

#include <windows.h>
#include <list>

struct ArchiveWireEntryF250
{
    unsigned char filename[100];
    DWORD sourceSize;
    DWORD sourceOffset;
};

class DataArchiveF481
{
public:
    DataArchiveF481();
    ~DataArchiveF481();
    void OpenAndReadIndex(const char* filename);
    HANDLE SeekNamedEntry(const char* name);
    HANDLE SeekNamedEntryWithSize(const char* name, DWORD* size);
    void AppendReadableFile(const char* filename);
    void Write(const char* filename);

private:
    HANDLE originalHandle;
    std::list<ArchiveWireEntryF250> entries;
};

typedef char ArchiveLayoutSizes[
    sizeof(ArchiveWireEntryF250) == 108 && sizeof(DataArchiveF481) == 16 ? 1 : -1];
