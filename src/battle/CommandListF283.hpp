#pragma once

#include "graphics/SpriteQuad.hpp"
#include <list>

class TextureManagerF198;

struct SpriteHistoryElementF325 {
    SpriteHistoryElementF325();

    short texture;
    SpriteQuad40CA80 quad;
    float x, y;
    D3DVECTOR offset;
    DWORD tint;
    signed char blend;
};

class CommandListF283 {
    TextureManagerF198* texture;
    std::list<SpriteHistoryElementF325> queue;
    unsigned char mode;
    short capacity;
    unsigned int colorMask;

public:
    CommandListF283(TextureManagerF198* source);
    void Reset();
    void SetCapacityAt00410FC0(short maximumEntries);
    void SetSamplingMode(unsigned char value);
    void SetColorMask(unsigned int value);
    void AppendElement(short texture, float x, float y, SpriteQuad40CA80 quad,
                       D3DVECTOR offset, DWORD tint, signed char blend);
    void RemoveFrontIfPresent();
    void RenderElements();
};

typedef char SpriteHistoryElementSizeCheck[(sizeof(SpriteHistoryElementF325) == 164) ? 1 : -1];
typedef char CommandListSizeCheck[(sizeof(CommandListF283) == 24) ? 1 : -1];
