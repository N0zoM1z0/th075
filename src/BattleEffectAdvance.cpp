#include <deque>
#include <new>
#include "EffectManagerLifetimeF161.hpp"

typedef std::deque<Actor*> EffectDequeF137;
typedef char CheckedEffectDequeF137[(sizeof(EffectDequeF137) == 20) ? 1 : -1];
typedef char CheckedEffectIteratorF137[(sizeof(EffectDequeF137::iterator) == 8) ? 1 : -1];


void EffectManagerLifetimeF161::AdvanceAll()
{
    int layer;
    for (layer = 0; layer < 4; layer++) {
        int count = entries_[layer].size();
        for (int index = 0; index < count; index++) {
            entries_[layer][index]->Advance();
        }
        EffectDequeF137::iterator it = entries_[layer].begin();
        while (it != entries_[layer].end()) {
            if ((*it)->frameInfo == 0) {
                delete *it;
                it = entries_[layer].erase(it);
            } else {
                it++;
            }
        }
    }
}
