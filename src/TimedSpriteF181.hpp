#pragma once
#include <stddef.h>

#include "TextureManagerF198.hpp"

// Borrowed partial owner view. Never instantiate or embed this partial owner.
class TimedSpriteF181 {
public:
    void RenderTimedSprite();
    unsigned char unknown000[0x18];
    TextureManagerF198 drawing;
    int field068;
};
typedef char TimedSpriteDrawingOffsetF181[(offsetof(TimedSpriteF181, drawing) == 0x18) ? 1 : -1];
typedef char TimedSpriteField068OffsetF181[(offsetof(TimedSpriteF181, field068) == 0x68) ? 1 : -1];
