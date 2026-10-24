#include "SpriteTransform40FBB0.hpp"
#include <cstring>

#define FIELD(type, offset) (*reinterpret_cast<type*>(reinterpret_cast<unsigned char*>(this) + (offset)))

void SpriteTransform40FBB0::ResetNodeTransform(float x, float y, float z) {
    FIELD(unsigned char, 0x40) = 1;
    FIELD(float, 0x34) = x;
    FIELD(float, 0x38) = y;
    FIELD(float, 0x3C) = z;
    std::memset(reinterpret_cast<unsigned char*>(this) + 0x10, 0, 0x24);
    FIELD(float, 0x1C) = 1.0f;
    FIELD(float, 0x20) = 1.0f;
    FIELD(float, 0x24) = 1.0f;
    FIELD(unsigned char, 0x11) = 255;
    FIELD(unsigned char, 0x12) = 255;
    FIELD(unsigned char, 0x13) = 255;
    FIELD(unsigned char, 0x14) = 255;
    FIELD(short, 0x16) = 0;
    FIELD(short, 0x18) = 0;
    FIELD(short, 0x1A) = 0;
    FIELD(unsigned char, 0x10) = 0;
}

#undef FIELD
