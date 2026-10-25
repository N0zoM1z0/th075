#include <deque>
#include <new>
#include "BattleEffectAdvance.hpp"

typedef std::deque<AdvancingEffectF137*> EffectDequeF137;
typedef char CheckedEffectDequeF137[(sizeof(EffectDequeF137) == 20) ? 1 : -1];
typedef char CheckedEffectIteratorF137[(sizeof(EffectDequeF137::iterator) == 8) ? 1 : -1];

#define EFFECTS(index) (*reinterpret_cast<EffectDequeF137*>(reinterpret_cast<unsigned char*>(this) + (index) * 20 + 4))
#define EFFECT_FIELD(type, object, offset) (*reinterpret_cast<type*>(reinterpret_cast<unsigned char*>(object) + (offset)))

void BattleEffectAdvanceF137::AdvanceAll()
{
    int layer;
    for (layer = 0; layer < 4; layer++) {
        int count = EFFECTS(layer).size();
        for (int index = 0; index < count; index++) {
            EFFECTS(layer)[index]->Advance();
        }
        EffectDequeF137::iterator it = EFFECTS(layer).begin();
        while (it != EFFECTS(layer).end()) {
            if (EFFECT_FIELD(int, *it, 0x74) == 0) {
                delete *it;
                it = EFFECTS(layer).erase(it);
            } else {
                it++;
            }
        }
    }
}

#undef EFFECT_FIELD
#undef EFFECTS
