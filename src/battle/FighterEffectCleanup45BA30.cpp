#include "characters/CharacterObject.hpp"
#include "battle/EffectManagerLifetimeF161.hpp"
#include <deque>
#include <new>

// The same four native std::deque<CharacterObject*> members that Spawn writes are
// traversed and cleared here. The trivial object destructor preserves the
// original unsized deallocation of each effect pointer.
typedef std::deque<CharacterObject*> EffectAddressDequeF160;
typedef char EffectAddressDequeSizeF160[(sizeof(EffectAddressDequeF160) == 20) ? 1 : -1];
typedef char EffectAddressIteratorSizeF160[(sizeof(EffectAddressDequeF160::iterator) == 8) ? 1 : -1];

void EffectManagerLifetimeF161::DeleteFourLists()
{
    EffectAddressDequeF160::iterator current;
    EffectAddressDequeF160::iterator last;
    for (int group = 0; group < 4; group++) {
        current = entries_[group].begin();
        last = entries_[group].end();
        for (; current != last; current++) {
            if (*current) {
                delete *current;
            }
        }
        entries_[group].clear();
    }
}
