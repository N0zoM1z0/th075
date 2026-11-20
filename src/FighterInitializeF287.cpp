#include <windows.h>
#include <string.h>
#include <new>
#include <deque>
#include <stddef.h>
#include "EffectManagerLifetimeF161.hpp"
// Physical subobject boundaries established from the original member calls;
// do not infer unobserved internal fields of fighter or library containers.
class FighterBaseF287 { public: FighterBaseF287(); virtual void Reserved(); };
class FighterActorPropertiesF287 {
    unsigned char physicalBytes[0x194];
public: FighterActorPropertiesF287();
};
class FighterActorVectorF287 {
    unsigned char physicalBytes[0x2c];
public: FighterActorVectorF287(); ~FighterActorVectorF287();
};
class FighterInputF287 { unsigned char physicalBytes[0x84]; public: FighterInputF287(); ~FighterInputF287(); };
// The +0x518..+0x6CF input-state subobject starts with the native
// VC7.1 command deque, followed by the fighter's input/quote state.
class FighterInputStateF287 {
public:
    std::deque<unsigned char> inputHistory; // +0x00: Fighter+0x518
    signed char field52C;
    signed char field52D;
    signed char field52E;
    signed char field52F;
    signed char field530;
    signed char field531;
    signed char field532;
    unsigned char unknown533;
    void* field534;
    unsigned char fadeAlpha;
    unsigned char drawMode;
    signed char quoteLineCount;
    char quoteLines[2][200];
    signed char quoteBadges[2];
    unsigned char unknown6CD[3];

    FighterInputStateF287();
    ~FighterInputStateF287();
    void Initialize(unsigned int count,unsigned int param);
};
typedef char AssertInputStateF287[(
    offsetof(FighterInputStateF287, inputHistory) == 0x00 &&
    offsetof(FighterInputStateF287, field52C) == 0x14 &&
    offsetof(FighterInputStateF287, field534) == 0x1C &&
    offsetof(FighterInputStateF287, quoteLines) == 0x23 &&
    offsetof(FighterInputStateF287, quoteBadges) == 0x1B3 &&
    sizeof(FighterInputStateF287) == 0x1B8) ? 1 : -1];
class FighterSoundF287 {unsigned char physicalBytes[0x44];public: FighterSoundF287(); ~FighterSoundF287(); void Configure();};
class FighterScriptF287 { public: FighterScriptF287(); ~FighterScriptF287(); };

typedef char AssertPropsF287[(sizeof(FighterActorPropertiesF287)==0x194)?1:-1];
typedef char AssertVectorF287[(sizeof(FighterActorVectorF287)==0x2c)?1:-1];
typedef char AssertInputF287[(sizeof(FighterInputF287)==0x84)?1:-1];
typedef char AssertSoundF287[(sizeof(FighterSoundF287)==0x44)?1:-1];
class FighterInitF287 : public FighterBaseF287 {
    unsigned char observedBaseGameState[0x2d0];
    FighterActorPropertiesF287 properties;
    FighterActorVectorF287 actors;
    FighterInputF287 input;
    FighterInputStateF287 replay;
    FighterSoundF287 sounds;
    FighterScriptF287 scripts;
public:
    FighterInitF287();
    virtual ~FighterInitF287();
};
#define FIELD(type,off) (*reinterpret_cast<type*>(reinterpret_cast<unsigned char*>(this)+(off)))
FighterInitF287::FighterInitF287()
{
    sounds.Configure();
    unsigned int scratch[7];
    memset(scratch,0,28);
    replay.Initialize(90,0);
    FIELD(EffectManagerLifetimeF161*,0x2ec)=new EffectManagerLifetimeF161();
    FIELD(EffectManagerLifetimeF161*,0x2ec)->BindFighter(reinterpret_cast<Fighter*>(this));
    FIELD(void*,4)=0;
    FIELD(void*,0x534)=0;
    FIELD(void*,0x700)=0;
}
#undef FIELD
