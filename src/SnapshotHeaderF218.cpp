#include <windows.h>
// Borrowed file snapshot header receiver. Its only accessed original
// fields are filepath+4 and 60-byte record header+0x108.
class SnapshotHeaderF218 {
public:
    void ReadSnapshotHeader();
};
#define FIELD(type,offset) (*reinterpret_cast<type*>(reinterpret_cast<unsigned char*>(this)+(offset)))
void SnapshotHeaderF218::ReadSnapshotHeader()
{
    HANDLE file = CreateFileA(reinterpret_cast<const char*>(this)+4,
                                GENERIC_READ,0,0,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,0);
    DWORD bytesRead;
    ReadFile(file,reinterpret_cast<unsigned char*>(this)+0x108,0x3c,&bytesRead,0);
    CloseHandle(file);
}
#undef FIELD
