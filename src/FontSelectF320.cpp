#include <windows.h>
// Native call boundary and four actually observed GDI state fields only.
// This does not assert a complete original FontSurface private layout.
class FontSelectF320 {public: void SelectFont();public:
    // Observed fields; meanings not yet known.
    HWND field000;
    HDC field004;
    HGDIOBJ field008;
    HGDIOBJ field00C;
    unsigned char unknown010[0x02C - 0x010];
    LONG field02C;
};
void FontSelectF320::SelectFont()
{
    TEXTMETRICA nativeMetrics;
    field004=GetDC(field000);
    field00C=SelectObject(field004,field008);
    GetTextMetricsA(field004,&nativeMetrics);
    field02C=nativeMetrics.tmAscent;
}
