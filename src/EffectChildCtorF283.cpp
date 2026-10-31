#include "FighterAnimationPhaseBorrowedF1024.hpp"
// Native-observed auxiliary effect base construction and physical fields.
// This source only represents the 116-byte child ctor, not the parent ABI.
class BaseAuxEffectF283 {
public:
    BaseAuxEffectF283();
    virtual void Start();
};
class EffectChildCtorF283 : public BaseAuxEffectF283 {
public:
    EffectChildCtorF283(void* owner);
    void Reset();
};
#define FIELD(type,off) (*reinterpret_cast<type*>(reinterpret_cast<unsigned char*>(this)+(off)))
EffectChildCtorF283::EffectChildCtorF283(void* owner)
{
    FIELD(void*,0x90)=owner;
    FIELD(void*,0x7c)=reinterpret_cast<unsigned char*>(FIELD(void*,0x90))+0x78;
    FIELD(void*,0x4)=reinterpret_cast<unsigned char*>(FIELD(void*,0x90))+0x28;
    FIELD(short,0x60)=0;
    F1024_PHASE(this).stageAt62=0;
    F1024_PHASE(this).frameAt64=0;
    Reset();
}
#undef FIELD
