#include "SelectionInput4388D0.hpp"
#include "SoundBank.hpp"
#include "ScriptResource4205F0.hpp"

// Physical, independently x86-observed fighter member boundaries and
// original game/VC7 call interfaces. Opaque member spans are purely
// positional: they do not claim original private class member semantics.
class FighterAuxChildF284 {public: void ClearBeforeDelete(); ~FighterAuxChildF284();};
class FighterCommandF284 {public: ~FighterCommandF284();};
class FighterSpecialF284 {public: ~FighterSpecialF284();};
class FighterTextureF284 {public: ~FighterTextureF284();};
class FighterVectorF284 {
    unsigned char physicalExtent[0x2c];
public:
    unsigned int size() const;
    FighterAuxChildF284** At(unsigned int index);
    void Clear();
    ~FighterVectorF284();
};
class FighterDequeF284 {
    unsigned char physicalExtent[0x1b8];
public:
    void Clear();
    ~FighterDequeF284();
};
class FighterResourceReleaseF284 {
public:
    virtual ~FighterResourceReleaseF284();
private:
    unsigned char observedFighterHeaderAndState[0x464];
    FighterVectorF284 actors;
    InputMapping4388D0 input;
    unsigned char remainingFighterState4DC[0x3C];
    FighterDequeF284 replay;
    SoundBank sounds;
    unsigned char remainingFighterState6E4[0x30];
    ScriptResource4205F0 scripts;
};
typedef char AssertFighterActorsF284[(sizeof(FighterVectorF284)==0x2c)?1:-1];
typedef char AssertFighterDequeF284[(sizeof(FighterDequeF284)==0x1b8)?1:-1];
#define FIELD(type,off) (*reinterpret_cast<type*>(reinterpret_cast<unsigned char*>(this)+(off)))
FighterResourceReleaseF284::~FighterResourceReleaseF284()
{
    for (unsigned int index=0;index<actors.size();++index) {
        if (*actors.At(index)) {
            (*actors.At(index))->ClearBeforeDelete();
            delete *actors.At(index);
        }
    }
    actors.Clear();
    replay.Clear();
    delete FIELD(FighterCommandF284*,0x480);
    delete FIELD(FighterSpecialF284*,0x2ec);
    if (FIELD(FighterTextureF284*,0x4)) delete FIELD(FighterTextureF284*,0x4);
    if (FIELD(FighterTextureF284*,0x534)) delete FIELD(FighterTextureF284*,0x534);
    if (FIELD(FighterTextureF284*,0x700)) delete FIELD(FighterTextureF284*,0x700);
}
#undef FIELD
