#include <windows.h>
#include <time.h>
// Borrowed replay this-pointer, byte header and original external message
// strings. No complete replay object or data resource ownership is asserted.
extern const char g_ReplayTempAt006578C4[];
extern const char g_ReplayErrorCaptionAt006578D8[];
extern const char g_ReplayErrorTextAt006578E0[];
class ReplayCaptureF218 {
public:
    void BeginCapture();
    void ClearQueues();
};
#define FIELD(type,off) (*reinterpret_cast<type*>(reinterpret_cast<unsigned char*>(this)+(off)))
void ReplayCaptureF218::BeginCapture()
{
    time_t stamp;
    time(&stamp);
    tm* calendar=localtime(&stamp);
    FIELD(unsigned char,0x111) = calendar->tm_mday;
    FIELD(unsigned char,0x110) = calendar->tm_mon+1;
    FIELD(unsigned char,0x116) = 0;
    FIELD(DWORD,0x11c) = 0;
    for (int index=0; index<8; ++index)
        FIELD(unsigned char,0x108+index)=100;
    ClearQueues();
    if (FIELD(HANDLE,0))
        CloseHandle(FIELD(HANDLE,0));
    FIELD(HANDLE,0) = CreateFileA(g_ReplayTempAt006578C4,
                GENERIC_READ|GENERIC_WRITE,0,0,CREATE_ALWAYS,FILE_ATTRIBUTE_NORMAL,0);
    if (FIELD(HANDLE,0)==INVALID_HANDLE_VALUE)
        MessageBoxA(0,g_ReplayErrorTextAt006578E0,
                    g_ReplayErrorCaptionAt006578D8,0);
}
#undef FIELD
