#include "FontSurface.hpp"
#include <stdlib.h>

void FontSurface::ReleaseRasterResources()
{
 if (glyphBitmap) {
   void* oldBuffer=glyphBitmap;
   free(oldBuffer);
   glyphBitmap=0;
 }
 DeleteObject(SelectObject(deviceContext,previouslySelectedFont));
 ReleaseDC(window,deviceContext);
 previouslySelectedFont=0;
 deviceContext=0;
}
