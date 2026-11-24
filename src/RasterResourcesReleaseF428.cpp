#include "FontSurface.hpp"
#include <stdlib.h>

FontSurface::~FontSurface() {
    if(glyphBitmap!=0) {
        void* released=glyphBitmap;
        free(released);
        glyphBitmap=0;
    }
    DeleteObject(SelectObject(deviceContext,previouslySelectedFont));
    ReleaseDC(window,deviceContext);
    font=0;
    previouslySelectedFont=0;
    deviceContext=0;
}
