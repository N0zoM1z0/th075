#pragma once
#include <stddef.h>

// Call-only view of the drawing subobject observed at TimedSpriteF181+0x18.
// Its complete owner extent and unrelated state remain intentionally unknown.
class TimedSpriteDrawingF181 {
public:
    void SetDepthMode(int);
    void SetBlendMode(int);
    void DrawQuad(int, const class SpriteQuad40CA80&, const struct tagRECT*, unsigned long);
};
typedef char TimedSpriteDrawingViewSizeF181[(sizeof(TimedSpriteDrawingF181) == 1) ? 1 : -1];

// Borrowed partial owner view. Never instantiate or embed this partial owner.
class TimedSpriteF181 {
public:
    void RenderTimedSprite();
    unsigned char unknown000[0x18];
    TimedSpriteDrawingF181 drawing;
    unsigned char unknown019[0x68 - 0x19];
    int field068;
};
typedef char TimedSpriteDrawingOffsetF181[(offsetof(TimedSpriteF181, drawing) == 0x18) ? 1 : -1];
typedef char TimedSpriteField068OffsetF181[(offsetof(TimedSpriteF181, field068) == 0x68) ? 1 : -1];
