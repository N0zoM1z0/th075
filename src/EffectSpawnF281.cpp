#include <windows.h>
#include <new>
// Physical borrowed native vector/deque interface. Class identities and
// underlying library implementations are not proven by these calls.
class EffectConfigSlotsF281 {
public:
    void** At(int index);
};
class EffectObjectListF281 {
public:
    void push_back(void* const& item);
    void** back();
};
class EffectSpawnedF281 {
    unsigned char observedBytes[0x90];
public:
    EffectSpawnedF281(void* owner);
    virtual void Initialize();
    virtual void Start();
};
typedef char AssertEffectSizeF281[(sizeof(EffectSpawnedF281)==0x94)?1:-1];
// A virtual dispatch object exposes only the called methods; its actual
// allocation footprint is confirmed separately by original new(0x94).
class EffectOwnerF281 {
public:
    void SpawnConfiguredAuxObject(short pattern,DWORD x,DWORD y,
                                  unsigned char kind,signed char side,
                                  unsigned char flags,unsigned char mode,
                                  const DWORD* extra);
};
#define RAW reinterpret_cast<unsigned char*>(this)
#define CONFIG (reinterpret_cast<EffectConfigSlotsF281*>(RAW+0x78))
#define ITEMS (reinterpret_cast<EffectObjectListF281*>(RAW+0x14*side))
#define FIELD(type,off) (*reinterpret_cast<type*>(reinterpret_cast<unsigned char*>(*ITEMS->back())+(off)))
void EffectOwnerF281::SpawnConfiguredAuxObject(short pattern,DWORD x,DWORD y,
                                             unsigned char kind,signed char side,
                                             unsigned char flags,unsigned char mode,
                                             const DWORD* extra)
{
    if (!*CONFIG->At(pattern)) return;
    if (!pattern) return;
    if (side<0 || side>1) return;
    {
        void* empty=0;
        ITEMS->push_back(empty);
        *ITEMS->back()=new EffectSpawnedF281(this);
        FIELD(short,0x60)=pattern;
        FIELD(short,0x62)=0;
        FIELD(short,0x64)=0;
        FIELD(DWORD,0x44)=x;
        FIELD(DWORD,0x48)=y;
        FIELD(unsigned char,0x66)=kind;
        FIELD(unsigned char,0x67)=flags;
        FIELD(unsigned char,0x68)=mode;
        FIELD(unsigned char,0x40)=0;
        FIELD(DWORD,0x80)=extra[0];
        FIELD(DWORD,0x84)=extra[1];
        FIELD(DWORD,0x88)=extra[2];
        FIELD(DWORD,0x8c)=extra[3];
        static_cast<EffectSpawnedF281*>(*ITEMS->back())->Initialize();
        static_cast<EffectSpawnedF281*>(*ITEMS->back())->Start();
    }
}
#undef FIELD
#undef ITEMS
#undef CONFIG
#undef RAW
