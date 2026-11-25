#pragma once

#include <windows.h>
#include <list>
#include <stddef.h>

struct ArchiveIndexEntry
{
    char filename[100];
    DWORD dataSize;
    DWORD dataOffset;
};

// Index bytes after the 16-bit entry count use an evolving byte mask.
namespace ArchiveIndexCipher {
enum Value {
    InitialKey = 100,
    InitialStep = 100,
    StepIncrement = 77,
};
}

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
    HANDLE archiveHandle;
    std::list<ArchiveIndexEntry> entries;
};

typedef char ArchiveLayoutSizes[
    sizeof(ArchiveIndexEntry) == 108 && sizeof(DataArchiveF481) == 16 ? 1 : -1];

typedef char ArchiveIndexOffsets[
    offsetof(ArchiveIndexEntry, dataSize) == 100 &&
    offsetof(ArchiveIndexEntry, dataOffset) == 104 ? 1 : -1];
