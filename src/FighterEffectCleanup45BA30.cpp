#include "EffectManagerLifetimeF161.hpp"
#include <deque>
#include <new>

// Deletion-only view of the observed no-destructor-work, unsized global
// release contract. Original pointee type/extent/destructor spelling stay
// unknown. Never construct or embed this view. No pointee size is consumed.
struct EffectReleaseViewF160 {
private:
    EffectReleaseViewF160();
};

// The manager constructor/destructor expose four std::deque<void*> members.
// The native cleanup's iterator/dereference/clear symbols are instead the
// EffectReleaseViewF160* instantiations. This pointer-only overlay preserves
// those observed helper ABIs over the same 20-byte vendor deque layout; it
// does not recover the actual effect pointee type or its destructor.
typedef std::deque<EffectReleaseViewF160*> EffectAddressDequeF160;
typedef char EffectAddressDequeSizeF160[(sizeof(EffectAddressDequeF160) == 20) ? 1 : -1];
typedef char EffectAddressIteratorSizeF160[(sizeof(EffectAddressDequeF160::iterator) == 8) ? 1 : -1];

void EffectManagerLifetimeF161::DeleteFourLists()
{
    EffectAddressDequeF160::iterator current;
    EffectAddressDequeF160::iterator last;
    for (int group = 0; group < 4; group++) {
        current = reinterpret_cast<EffectAddressDequeF160*>(entries_)[group].begin();
        last = reinterpret_cast<EffectAddressDequeF160*>(entries_)[group].end();
        for (; current != last; current++) {
            if (*current) {
                delete *current;
            }
        }
        reinterpret_cast<EffectAddressDequeF160*>(entries_)[group].clear();
    }
}
