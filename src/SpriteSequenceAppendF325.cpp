#include "CommandListF283.hpp"

SpriteHistoryElementF325::SpriteHistoryElementF325()
{
}

void CommandListF283::AppendElement(short texture,float x,float y,SpriteQuad40CA80 quad,
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
    queue.push_back(local);
    if(static_cast<int>(queue.size()) > capacity)
        queue.pop_front();
}
