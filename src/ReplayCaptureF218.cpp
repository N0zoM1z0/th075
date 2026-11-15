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
public:
    // Observed fields; meanings not yet known.
    HANDLE field000;
    unsigned char unknown004[0x110 - 0x004];
    unsigned char field110;
    unsigned char field111;
    unsigned char unknown112[0x116 - 0x112];
    unsigned char field116;
    unsigned char unknown117[0x11C - 0x117];
    unsigned long field11C;
};
#define FIELD(type,off) (*reinterpret_cast<type*>(reinterpret_cast<unsigned char*>(this)+(off)))
void ReplayCaptureF218::BeginCapture()
{
    time_t stamp;
    time(&stamp);
    tm* calendar=localtime(&stamp);
    field111 = calendar->tm_mday;
    field110 = calendar->tm_mon+1;
    field116 = 0;
    field11C = 0;
    for (int index=0; index<8; ++index)
        FIELD(unsigned char,0x108+index)=100;
    ClearQueues();
    if (field000)
        CloseHandle(field000);
    field000 = CreateFileA(g_ReplayTempAt006578C4,
                GENERIC_READ|GENERIC_WRITE,0,0,CREATE_ALWAYS,FILE_ATTRIBUTE_NORMAL,0);
    if (field000==INVALID_HANDLE_VALUE)
        MessageBoxA(0,g_ReplayErrorTextAt006578E0,
                    g_ReplayErrorCaptionAt006578D8,0);
}
#undef FIELD
