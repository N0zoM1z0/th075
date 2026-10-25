#include "FighterVirtualActionsF159.hpp"
#include <deque>
#include <new>

// Deletion-only view of the observed no-destructor-work, unsized global
// release contract. Original pointee type/extent/destructor spelling stay
// unknown. Never construct or embed this view. No pointee size is consumed.
struct EffectReleaseViewF160 {
private:
    EffectReleaseViewF160();
};

// Complete vendor container/iterator types; these are not game-owner extents.
typedef std::deque<EffectReleaseViewF160*> EffectAddressDequeF160;
typedef char EffectAddressDequeSizeF160[(sizeof(EffectAddressDequeF160) == 20) ? 1 : -1];
typedef char EffectAddressIteratorSizeF160[(sizeof(EffectAddressDequeF160::iterator) == 8) ? 1 : -1];

void RoundResetEffectsF159::DeleteFourLists()
{
    EffectAddressDequeF160::iterator current;
    EffectAddressDequeF160::iterator last;
    for (int group = 0; group < 4; group++) {
        current = reinterpret_cast<EffectAddressDequeF160*>(
            reinterpret_cast<unsigned char*>(this) + 4)[group].begin();
        last = reinterpret_cast<EffectAddressDequeF160*>(
            reinterpret_cast<unsigned char*>(this) + 4)[group].end();
        for (; current != last; current++) {
            if (*current) {
                delete *current;
            }
        }
        reinterpret_cast<EffectAddressDequeF160*>(
            reinterpret_cast<unsigned char*>(this) + 4)[group].clear();
    }
}
