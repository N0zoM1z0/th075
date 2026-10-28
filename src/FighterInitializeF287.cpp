#include <windows.h>
#include <string.h>
#include <new>
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
class FighterDequeF287 {
    unsigned char physicalBytes[0x1b8];
public:
    FighterDequeF287(); ~FighterDequeF287(); void Initialize(unsigned int count,unsigned int param);
};
class FighterSoundF287 {unsigned char physicalBytes[0x44];public: FighterSoundF287(); ~FighterSoundF287(); void Configure();};
class FighterScriptF287 { public: FighterScriptF287(); ~FighterScriptF287(); };
class FighterSpecialF287 {
    unsigned char observedBytes[0x54];
public: FighterSpecialF287(); void Initialize(void* fighter);
};
typedef char AssertPropsF287[(sizeof(FighterActorPropertiesF287)==0x194)?1:-1];
typedef char AssertVectorF287[(sizeof(FighterActorVectorF287)==0x2c)?1:-1];
typedef char AssertInputF287[(sizeof(FighterInputF287)==0x84)?1:-1];
typedef char AssertDequeF287[(sizeof(FighterDequeF287)==0x1b8)?1:-1];
typedef char AssertSoundF287[(sizeof(FighterSoundF287)==0x44)?1:-1];
class FighterInitF287 : public FighterBaseF287 {
    unsigned char observedBaseGameState[0x2d0];
    FighterActorPropertiesF287 properties;
    FighterActorVectorF287 actors;
    FighterInputF287 input;
    FighterDequeF287 replay;
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
    FIELD(FighterSpecialF287*,0x2ec)=new FighterSpecialF287();
    FIELD(FighterSpecialF287*,0x2ec)->Initialize(this);
    FIELD(void*,4)=0;
    FIELD(void*,0x534)=0;
    FIELD(void*,0x700)=0;
}
#undef FIELD
