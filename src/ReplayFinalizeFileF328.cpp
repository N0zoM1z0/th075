#include <windows.h>
#include <new>
#include <stdlib.h>

// This method only borrows the physical existing replay handle and
// 60-byte record header; complete owner and archive formats remain unknown.
extern const char g_ReplayTemporaryFileAt00657904[];
struct NativeFinalizeWorkF328 {
    void* releasedData;
    void* allocation;
    char* data;
    DWORD written;
    char path[264];
};
typedef char CheckNativeFrame280F328[(sizeof(NativeFinalizeWorkF328)==280)?1:-1];
// The other three real 32-bit values follow the native security cookie:
// output at EBP-0xC, file size at EBP-0x8, actual loop index at EBP-0x4.
// This contains only used game state, no synthetic stack filler.
struct ActualFileStateF328 { HANDLE output; DWORD size; unsigned int i; };
typedef char CheckActualFileState12F328[(sizeof(ActualFileStateF328)==12)?1:-1];
class ReplayFinalizeF218 {
public:
    void FinalizeFile();
    void MakeArchivePath(char* output);
};
#define FIELD(type,off) (*reinterpret_cast<type*>(reinterpret_cast<unsigned char*>(this)+(off)))
void ReplayFinalizeF218::FinalizeFile()
{
    NativeFinalizeWorkF328 state;
    ActualFileStateF328 io;
    MakeArchivePath(state.path);
    io.output = CreateFileA(state.path,GENERIC_WRITE,0,0,CREATE_ALWAYS,FILE_ATTRIBUTE_NORMAL,0);
    WriteFile(io.output,reinterpret_cast<unsigned char*>(this)+0x108,0x3c,&state.written,0);
    CloseHandle(FIELD(HANDLE,0));
    FIELD(HANDLE,0) = CreateFileA(g_ReplayTemporaryFileAt00657904,
                     GENERIC_READ,0,0,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,0);
    io.size=GetFileSize(FIELD(HANDLE,0),0);
    state.allocation = ::operator new(io.size);
    state.data = static_cast<char*>(state.allocation);
    for (io.i=0;io.i<io.size;++io.i) {
        ReadFile(FIELD(HANDLE,0),state.data,1,&state.written,0);
        WriteFile(io.output,state.data,1,&state.written,0);
    }
    state.releasedData = state.data;
    free(state.releasedData);
    CloseHandle(FIELD(HANDLE,0));
    FIELD(HANDLE,0) = 0;
    CloseHandle(io.output);
}
#undef FIELD
