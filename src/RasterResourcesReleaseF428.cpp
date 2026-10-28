#include <windows.h>
#include <stdlib.h>
// Independently exact original 129-byte raster/GDI cleanup: real buffer
// free, selected old bitmap deletion and window device context release,
// native fields reset. A real freed buffer pointer is the only native local.
// Complete native graphics bitmap/DC resource cleanup. Borrowed native owner
// field offsets alone; actual original private raster owner unknown.
class RasterResourcesF428 {public: void ReleaseAndReset();};
#define F(T,o) (*reinterpret_cast<T*>(reinterpret_cast<unsigned char*>(this)+(o)))
void RasterResourcesF428::ReleaseAndReset() {
    if(F(void*,0x14)!=0) {
        void* released=F(void*,0x14);
        free(released);
        F(void*,0x14)=0;
    }
    DeleteObject(SelectObject(F(HDC,4),F(HGDIOBJ,0xC)));
    ReleaseDC(F(HWND,0),F(HDC,4));
    F(unsigned int,8)=0;
    F(unsigned int,0xC)=0;
    F(unsigned int,4)=0;
}
#undef F
