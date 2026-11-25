#include "graphics/FontSurface.hpp"
void FontSurface::SelectFont()
{
    TEXTMETRICA nativeMetrics;
    deviceContext=GetDC(window);
    previouslySelectedFont=SelectObject(deviceContext,font);
    GetTextMetricsA(deviceContext,&nativeMetrics);
    ascent=nativeMetrics.tmAscent;
}
