#include "EffectDispatchF162.hpp"
#include <deque>

typedef std::deque<DispatchingEffectF162*> DispatchDequeF162;
typedef char DispatchDequeSizeF162[(sizeof(DispatchDequeF162) == 20) ? 1 : -1];
typedef char DispatchIteratorSizeF162[(sizeof(DispatchDequeF162::iterator) == 8) ? 1 : -1];


void EffectDispatchF162::DispatchSelected(signed char layer)
{
    DispatchDequeF162::iterator current = entries_[layer].begin();
    DispatchDequeF162::iterator last = entries_[layer].end();
    for (; current != last; current++) {
        if ((*current)->field067) {
            (*current)->RenderNode();
        } else {
            (*current)->Render();
        }
    }
}

void EffectDispatchF162::DispatchAll()
{
    DispatchDequeF162::iterator current;
    DispatchDequeF162::iterator last;
    for (int layer = 0; layer < 4; layer++) {
        current = entries_[layer].begin();
        last = entries_[layer].end();
        for (; current != last; current++) {
            if ((*current)->field068) {
                (*current)->RenderMirroredNode();
            }
        }
    }
}
