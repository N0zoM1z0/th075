#include <windows.h>
#include <string.h>
// Borrowed four-byte archive iterators; do not assert the private list layout.
class ArchiveIteratorF340 {
    void* element;
public:
    bool operator!=(const ArchiveIteratorF340& other) const;
    bool operator==(const ArchiveIteratorF340& other) const;
    char* Entry();
    ArchiveIteratorF340 operator++(int);
};
typedef char VerifyArchiveIterator4F340[(sizeof(ArchiveIteratorF340)==4)?1:-1];
class ArchiveEntryListF340 {
public:
    ArchiveIteratorF340 Begin();
    ArchiveIteratorF340 End();
};
class ArchiveContextF340 {
public:
    HANDLE SeekNamedEntry(const char* name);
};
#define ENTRIES (*reinterpret_cast<ArchiveEntryListF340*>(reinterpret_cast<unsigned char*>(this)+4))
#define FILE_FIELD (*reinterpret_cast<HANDLE*>(this))
HANDLE ArchiveContextF340::SeekNamedEntry(const char* name)
{
    ArchiveIteratorF340 current=ENTRIES.Begin();
    ArchiveIteratorF340 last=ENTRIES.End();
    while (current != last) {
        if (!strcmp(current.Entry(),name)) break;
        current++;
    }
    if (current == last) return INVALID_HANDLE_VALUE;
    SetFilePointer(FILE_FIELD, *reinterpret_cast<DWORD*>(current.Entry()+104), 0, FILE_BEGIN);
    return FILE_FIELD;
}
#undef ENTRIES
#undef FILE_FIELD
