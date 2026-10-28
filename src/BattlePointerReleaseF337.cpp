#include <windows.h>
#include <stdlib.h>
// Physical native 20-byte side-list ABI; real container methods are external.
class NativePointerListF337 {
public:
    unsigned int Size();
    void** At(unsigned int position);
    void Clear();
};
struct PointerQueueStateF337 { void* second; void* first; unsigned int i; };
typedef char CheckNativePointerState12F337[(sizeof(PointerQueueStateF337)==12)?1:-1];
class BattlePointerQueuesF337 {public: void ReleaseEntries();};
#define SIDE(n) (*reinterpret_cast<NativePointerListF337*>(reinterpret_cast<unsigned char*>(this)+0x14*(n)))
void BattlePointerQueuesF337::ReleaseEntries()
{
    PointerQueueStateF337 state;
    for(state.i=0; state.i<SIDE(0).Size(); ++state.i) {
        state.first=*SIDE(0).At(state.i);
        free(state.first);
    }
    SIDE(0).Clear();
    for(state.i=0; state.i<SIDE(1).Size(); ++state.i) {
        state.second=*SIDE(1).At(state.i);
        free(state.second);
    }
    SIDE(1).Clear();
}
#undef SIDE
