#include <windows.h>
#include <stdlib.h>
class FontReleaseF293 {
public:
 void ReleaseRasterResources();
};
#define F(type,off) (*reinterpret_cast<type*>(reinterpret_cast<unsigned char*>(this)+(off)))
void FontReleaseF293::ReleaseRasterResources()
{
 if (F(void*,0x14)) {
   void* oldBuffer=F(void*,0x14);
   free(oldBuffer);
   F(void*,0x14)=0;
 }
 DeleteObject(SelectObject(F(HDC,4),F(HGDIOBJ,0xc)));
 ReleaseDC(F(HWND,0),F(HDC,4));
 F(HGDIOBJ,0xc)=0;
 F(HDC,4)=0;
}
#undef F
