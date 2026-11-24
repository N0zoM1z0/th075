#include "FontSurface.hpp"
bool FontSurface::IsDoubleByte(char lead) {
    if (static_cast<unsigned char>(lead) < 0x81) return false;
    if (static_cast<unsigned char>(lead) < 0xA0) return true;
    if (static_cast<unsigned char>(lead) < 0xE0) return false;
    if (static_cast<unsigned char>(lead) < 0xFF) return true;
    return false;
}
