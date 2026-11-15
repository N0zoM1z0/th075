#include "SpriteTransform40FBB0.hpp"
#include <cstring>


void SpriteTransform40FBB0::ResetNodeTransform(float x, float y, float z) {
    field040 = 1;
    field034 = x;
    field038 = y;
    field03C = z;
    std::memset(reinterpret_cast<unsigned char*>(this) + 0x10, 0, 0x24);
    field01C = 1.0f;
    field020 = 1.0f;
    field024 = 1.0f;
    field011 = 255;
    field012 = 255;
    field013 = 255;
    field014 = 255;
    field016 = 0;
    field018 = 0;
    field01A = 0;
    field010 = 0;
}
