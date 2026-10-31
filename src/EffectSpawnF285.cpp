#include "FighterAnimationPhaseBorrowedF1024.hpp"
#include <windows.h>
#include <new>
// Physical borrowed native vector/deque interface. Class identities and
// underlying library implementations are not proven by these calls.
class EffectConfigSlotsF285 {
public:
    void** At(int index);
};
class EffectObjectListF285 {
public:
    void push_back(void* const& item);
    void** back();
};
class EffectSpawnedF285 {
    unsigned char observedBytes[0x90];
public:
    EffectSpawnedF285(void* owner);
    virtual void Initialize();
    virtual void Start();
};
typedef char AssertEffectSizeF285[(sizeof(EffectSpawnedF285)==0x94)?1:-1];
// A virtual dispatch object exposes only the called methods; its actual
// allocation footprint is confirmed separately by original new(0x94).
class EffectOwnerF285 {
public:
    void SpawnAuxObject(short pattern,DWORD x,DWORD y,
                                  unsigned char kind,signed char side,
                                  unsigned char flags,unsigned char mode);
};
#define RAW reinterpret_cast<unsigned char*>(this)
#define CONFIG (reinterpret_cast<EffectConfigSlotsF285*>(RAW+0x78))
#define ITEMS (reinterpret_cast<EffectObjectListF285*>(RAW+0x14*side))
#define FIELD(type,off) (*reinterpret_cast<type*>(reinterpret_cast<unsigned char*>(*ITEMS->back())+(off)))
void EffectOwnerF285::SpawnAuxObject(short pattern,DWORD x,DWORD y,
                                             unsigned char kind,signed char side,
                                             unsigned char flags,unsigned char mode)
{
    if (!*CONFIG->At(pattern)) return;
    if (!pattern) return;
    if (side<0 || side>1) return;
    {
        void* empty=0;
        ITEMS->push_back(empty);
        *ITEMS->back()=new EffectSpawnedF285(this);
        FIELD(short,0x60)=pattern;
        F1024_PHASE(*ITEMS->back()).stageAt62=0;
        F1024_PHASE(*ITEMS->back()).frameAt64=0;
        FIELD(DWORD,0x44)=x;
        FIELD(DWORD,0x48)=y;
        FIELD(unsigned char,0x66)=kind;
        FIELD(unsigned char,0x67)=flags;
        FIELD(unsigned char,0x68)=mode;
        FIELD(unsigned char,0x40)=0;
        static_cast<EffectSpawnedF285*>(*ITEMS->back())->Initialize();
        static_cast<EffectSpawnedF285*>(*ITEMS->back())->Start();
    }
}
#undef FIELD
#undef ITEMS
#undef CONFIG
#undef RAW
