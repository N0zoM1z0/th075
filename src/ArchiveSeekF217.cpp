#include <windows.h>
#include <string.h>
// The original archive list and four-byte iterators are borrowed interfaces.
// Their underlying node/container storage is not defined or instantiated.
class ArchiveIteratorF217 {
    void* element;
public:
    bool operator!=(const ArchiveIteratorF217& other) const;
    bool operator==(const ArchiveIteratorF217& other) const;
    char* Entry();
    ArchiveIteratorF217 operator++(int);
};
typedef char VerifyArchiveIterator4F217[(sizeof(ArchiveIteratorF217)==4)?1:-1];
class ArchiveEntryListF217 {
public:
    ArchiveIteratorF217 Begin();
    ArchiveIteratorF217 End();
};
class ArchiveSeekF217 {
public:
    HANDLE SeekNamedEntryWithSize(const char* entryName, DWORD* size);
};
#define ENTRIES (*reinterpret_cast<ArchiveEntryListF217*>(reinterpret_cast<unsigned char*>(this)+4))
#define FILE_FIELD (*reinterpret_cast<HANDLE*>(this))
HANDLE ArchiveSeekF217::SeekNamedEntryWithSize(const char* entryName, DWORD* size)
{
    ArchiveIteratorF217 current=ENTRIES.Begin();
    ArchiveIteratorF217 last=ENTRIES.End();
    while (current != last) {
        if (!strcmp(current.Entry(),entryName))
            break;
        current++;
    }
    if (current == last)
        return INVALID_HANDLE_VALUE;
    SetFilePointer(FILE_FIELD,
        *reinterpret_cast<DWORD*>(current.Entry()+0x68),0,FILE_BEGIN);
    *size = *reinterpret_cast<DWORD*>(current.Entry()+0x64);
    return FILE_FIELD;
}
#undef FILE_FIELD
#undef ENTRIES
