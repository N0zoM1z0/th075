#include "EffectDispatchF162.hpp"
#include <deque>

typedef std::deque<DispatchingEffectF162*> DispatchDequeF162;
typedef char DispatchDequeSizeF162[(sizeof(DispatchDequeF162) == 20) ? 1 : -1];
typedef char DispatchIteratorSizeF162[(sizeof(DispatchDequeF162::iterator) == 8) ? 1 : -1];

#define EFFECTS(layer) (*reinterpret_cast<DispatchDequeF162*>(reinterpret_cast<unsigned char*>(this) + (layer) * 20 + 4))
#define EFFECT_FLAG(effect, offset) (*reinterpret_cast<unsigned char*>(reinterpret_cast<unsigned char*>(effect) + (offset)))

void EffectDispatchF162::DispatchSelected(signed char layer)
{
    DispatchDequeF162::iterator current = EFFECTS(layer).begin();
    DispatchDequeF162::iterator last = EFFECTS(layer).end();
    for (; current != last; current++) {
        if (EFFECT_FLAG(*current, 0x67)) {
            (*current)->DrawAlternate();
        } else {
            (*current)->DrawPrimary();
        }
    }
}

void EffectDispatchF162::DispatchAll()
{
    DispatchDequeF162::iterator current;
    DispatchDequeF162::iterator last;
    for (int layer = 0; layer < 4; layer++) {
        current = EFFECTS(layer).begin();
        last = EFFECTS(layer).end();
        for (; current != last; current++) {
            if (EFFECT_FLAG(*current, 0x68)) {
                (*current)->DrawOverlay();
            }
        }
    }
}

#undef EFFECT_FLAG
#undef EFFECTS
