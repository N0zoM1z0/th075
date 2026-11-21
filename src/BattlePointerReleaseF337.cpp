#include <windows.h>
#include <stddef.h>
#include <stdlib.h>
#include <deque>

// Each native side list is a 20-byte VC7.1 deque<void*> view. The original
// Size/At/Clear member bodies remain external; their observed +0x10 size
// access and void** At return agree with this backing container.
class NativePointerListF337 {
public:
    unsigned int Size();
    void** At(unsigned int position);
    void Clear();
private:
    std::deque<void*> entries;
};
typedef char NativePointerListSizeF337[
    (sizeof(NativePointerListF337) == 0x14) ? 1 : -1];

// The original receiver owns two adjacent side lists at +0 and +0x14.
// This is the observed 40-byte prefix, not a claim about later owner fields.
class BattlePointerQueuesF337 {
public:
    void ReleaseEntries();
    NativePointerListF337 first;
    NativePointerListF337 second;
};
typedef char BattlePointerQueuesSecondOffsetF337[
    (offsetof(BattlePointerQueuesF337, second) == 0x14) ? 1 : -1];
typedef char BattlePointerQueuesPrefixSizeF337[
    (sizeof(BattlePointerQueuesF337) == 0x28) ? 1 : -1];

struct PointerQueueStateF337 {
    void* second;
    void* first;
    unsigned int i;
};
typedef char CheckNativePointerState12F337[
    (sizeof(PointerQueueStateF337) == 12) ? 1 : -1];

void BattlePointerQueuesF337::ReleaseEntries()
{
    PointerQueueStateF337 state;
    for(state.i=0; state.i<first.Size(); ++state.i) {
        state.first=*first.At(state.i);
        free(state.first);
    }
    first.Clear();
    for(state.i=0; state.i<second.Size(); ++state.i) {
        state.second=*second.At(state.i);
        free(state.second);
    }
    second.Clear();
}
