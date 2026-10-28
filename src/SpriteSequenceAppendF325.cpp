#include "SpriteDraw40CA80.hpp"
#include <windows.h>
// Only the physically observed 164-byte element and 20-byte list receiver.
// The original list allocator/element private definitions remain borrowed.
struct SpriteHistoryElementF325 {
    short texture;
    SpriteQuad40CA80 quad;
    float x, y;
    D3DVECTOR offset;
    DWORD tint;
    signed char blend;
    SpriteHistoryElementF325();
};
typedef char CheckSpriteHistory164F325[(sizeof(SpriteHistoryElementF325)==164)?1:-1];
class SpriteHistoryListF325 {
public:
    void Append(const SpriteHistoryElementF325& value);
    int Size();
    void RemoveFront();
};
class SpriteSequenceF325 {
public:
    void AppendElement(short texture,float x,float y,SpriteQuad40CA80 quad,
                       D3DVECTOR offset,DWORD tint,signed char blend);
};
#define F(type,offset) (*reinterpret_cast<type*>(reinterpret_cast<unsigned char*>(this)+(offset)))
void SpriteSequenceF325::AppendElement(short texture,float x,float y,SpriteQuad40CA80 quad,
                                      D3DVECTOR offset,DWORD tint,signed char blend)
{
    SpriteHistoryElementF325 local;
    local.texture=texture;
    local.quad=quad;
    local.offset=offset;
    local.blend=blend;
    local.x=x;
    local.y=y;
    local.tint=tint;
    reinterpret_cast<SpriteHistoryListF325*>(reinterpret_cast<unsigned char*>(this)+4)->Append(local);
    if(reinterpret_cast<SpriteHistoryListF325*>(reinterpret_cast<unsigned char*>(this)+4)->Size()>F(short,0x12))
        reinterpret_cast<SpriteHistoryListF325*>(reinterpret_cast<unsigned char*>(this)+4)->RemoveFront();
}
#undef F
