#include <windows.h>

// Borrowed views of native replay-record collections. The complete original
// record and deque owner classes are unknown; only observed fields and
// the function-local ABI are asserted here.
// Nested real local lifetimes preserve VC7.1 stack locations without
// introducing synthetic storage.
class ReplayByteListF216 {
public:
    void Clear();
    void Push(const char* item);
};
class ReplayWordListF216 {
public:
    void Clear();
    void Push(const short& item);
};
class ReplayDwordListF216 {
public:
    void Clear();
    void Push(const unsigned int* item);
};
class ReplayRecordsF216 {
public:
    void LoadRecord(signed char slot);
};
#define AT(type,off) (*reinterpret_cast<type*>(reinterpret_cast<unsigned char*>(this)+(off)))
#define LIST(type,off) (*reinterpret_cast<type*>(reinterpret_cast<unsigned char*>(this)+(off)))
void ReplayRecordsF216::LoadRecord(signed char slot)
{
    unsigned int i;
    {
    unsigned int dwordItem;
    {
    // The file contains an unsigned 16-bit word. Insertion into the signed
    // 16-bit collection materializes an actual compiler temporary (EBP-1E).
    unsigned short rawWord;
    {
    unsigned int entries;
    {
    HANDLE handle;
    {
    char item;
    {
    DWORD bytesRead;
    {
    handle = CreateFileA(reinterpret_cast<const char*>(this)+4, GENERIC_READ,0,0,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,0);
    entries = 0;
    SetFilePointer(handle, AT(int,0x11c + 4*slot) + 0x3c, 0, FILE_BEGIN);
    ReadFile(handle,&AT(BYTE,0x144),1,&bytesRead,0);
    ReadFile(handle,&AT(BYTE,0x145),1,&bytesRead,0);
    ReadFile(handle,&AT(BYTE,0x146),1,&bytesRead,0);
    ReadFile(handle,&AT(BYTE,0x147),1,&bytesRead,0);
    ReadFile(handle,&AT(BYTE,0x148),1,&bytesRead,0);
    ReadFile(handle,&AT(BYTE,0x149),1,&bytesRead,0);
    ReadFile(handle,&AT(BYTE,0x14a),1,&bytesRead,0);
    ReadFile(handle,&AT(short,0x14c),2,&bytesRead,0);
    ReadFile(handle,&AT(BYTE,0x14e),1,&bytesRead,0);
    ReadFile(handle,&AT(unsigned int,0x150),4,&bytesRead,0);
    ReadFile(handle,&entries,4,&bytesRead,0);
    LIST(ReplayByteListF216,0x154).Clear();
    for (i=0;i<entries;++i) {
        ReadFile(handle,&item,1,&bytesRead,0);
        LIST(ReplayByteListF216,0x154).Push(&item);
    }
    ReadFile(handle,&entries,4,&bytesRead,0);
    LIST(ReplayWordListF216,0x168).Clear();
    for (i=0;i<entries;++i) {
        ReadFile(handle,&rawWord,2,&bytesRead,0);
        LIST(ReplayWordListF216,0x168).Push(static_cast<short>(rawWord));
    }
    ReadFile(handle,&entries,4,&bytesRead,0);
    LIST(ReplayByteListF216,0x17c).Clear();
    for (i=0;i<entries;++i) {
        ReadFile(handle,&item,1,&bytesRead,0);
        LIST(ReplayByteListF216,0x17c).Push(&item);
    }
    ReadFile(handle,&entries,4,&bytesRead,0);
    LIST(ReplayDwordListF216,0x190).Clear();
    for (i=0;i<entries;++i) {
        ReadFile(handle,&dwordItem,4,&bytesRead,0);
        LIST(ReplayDwordListF216,0x190).Push(&dwordItem);
    }
    CloseHandle(handle);
    }
    }
    }
    }
    }
    }
    }
}
#undef LIST
#undef AT
