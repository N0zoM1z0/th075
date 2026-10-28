#include <windows.h>
// Native call boundary and four actually observed GDI state fields only.
// This does not assert a complete original FontSurface private layout.
class FontSelectF320 {public: void SelectFont();};
#define FIELD(type,off) (*reinterpret_cast<type*>(reinterpret_cast<unsigned char*>(this)+(off)))
void FontSelectF320::SelectFont()
{
    TEXTMETRICA nativeMetrics;
    FIELD(HDC,4)=GetDC(FIELD(HWND,0));
    FIELD(HGDIOBJ,0xC)=SelectObject(FIELD(HDC,4),FIELD(HGDIOBJ,8));
    GetTextMetricsA(FIELD(HDC,4),&nativeMetrics);
    FIELD(LONG,0x2C)=nativeMetrics.tmAscent;
}
#undef FIELD
