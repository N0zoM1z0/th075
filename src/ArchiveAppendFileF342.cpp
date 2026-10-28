#include <windows.h>
#include <string.h>
// One genuine 108-byte archive wire record; private owner and node layouts are borrowed.
struct ArchiveWireEntryF342 {
    char filename[100];
    DWORD fileSize;
    DWORD fileOffset;
};
typedef char ArchiveWireEntrySize108F342[(sizeof(ArchiveWireEntryF342)==108)?1:-1];
class ArchiveEntryListF342 {
public:
    void AddEntry(const ArchiveWireEntryF342& record);
};
class DataArchiveF342 {
public:
    void AppendReadableFile(const char* filename);
};
#define ENTRIES (*reinterpret_cast<ArchiveEntryListF342*>(reinterpret_cast<unsigned char*>(this)+4))
void DataArchiveF342::AppendReadableFile(const char* filename) {
    HANDLE file=CreateFileA(filename, GENERIC_READ, 0,0,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,0);
    if (file==INVALID_HANDLE_VALUE) return;
    ArchiveWireEntryF342 entry;
    entry.fileOffset=0;
    entry.fileSize=GetFileSize(file,0);
    strcpy(entry.filename,filename);
    CloseHandle(file);
    ENTRIES.AddEntry(entry);
}
#undef ENTRIES
