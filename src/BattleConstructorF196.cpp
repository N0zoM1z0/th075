#include <windows.h>
#include <mmsystem.h>
#include <d3d8.h>

// Source-compatible physical allocation carriers for this constructor only.
// The native 0x40AD80 callee and its nested vector/deque constructors
// independently anchor the offsets and allocation extents. These do NOT
// establish original C++ class names, container element types or the full
// semantic meaning of fields; do not reuse them as original owner layouts.
class GlobalCounterViewF196 {
public:
    GlobalCounterViewF196();
    ~GlobalCounterViewF196();
};
// SceneBase uses the actual vptr at +0 and initializes its global-count
// subobject at +4. The first distinct battle member starts at +8.
// R108 still leaves the base ctor's authored/generated origin unresolved.
class SceneBaseF196 {
public:
    SceneBaseF196();
    virtual ~SceneBaseF196();
private:
    GlobalCounterViewF196 globals;
};
// Component widths are drawn from the actual 0x40AD80 nested constructors:
// base 8, three 16-byte vector subregions, one 20-byte deque, trailing byte.
struct Vc7VectorStorageF196 {
    DWORD first, last, capacity, policy;
};
struct Vc7DequeStorageF196 {
    DWORD map, begin, end, count, policy;
};
class TextureManagerAllocF196 {
    DWORD unresolvedBaseWordAt0, stateAt4;
    Vc7VectorStorageF196 vectorA, vectorB, vectorC;
    Vc7DequeStorageF196 deque;
    unsigned char defaultTextureDepth;
public:
    TextureManagerAllocF196();
    void AllocateUnformattedSlots(int);
    void LoadDefault(const char*, const char*);
    IDirect3DTexture8* GetTexture(int);
};
typedef char ValidateSceneBaseF196[(sizeof(SceneBaseF196)==8)?1:-1];
typedef char ValidateTextureAllocF196[(sizeof(TextureManagerAllocF196)==80)?1:-1];
class DigitAtlasAllocF196 {
public:
    DigitAtlasAllocF196(IDirect3DTexture8*, IDirect3DTexture8*, IDirect3DTexture8*);
};
typedef char ValidateDigitAllocF196[(sizeof(DigitAtlasAllocF196)==1)?1:-1];
class ComboCounterAllocF196 {
    void *texture;
    short maxCombo, latestCount, previousCount;
    BYTE alpha;
    signed char side;
    short timer, secondaryTimer;
    float drawingOffset;
public:
    ComboCounterAllocF196(void* texture, signed char side);
};
typedef char ValidateComboAllocF196[(sizeof(ComboCounterAllocF196)==20)?1:-1];

class CombatTextConfiguratorF196 {
public:
    void Configure(float,float,int);
};
extern CombatTextConfiguratorF196* g_CombatTextAt0067143C;
extern void* g_CombatActorAAt00671418;
extern void* g_CombatActorBAt0067141C;
extern signed char g_CombatModeAt006714B4;
extern signed char g_FrameClockModeAt0066C238;
extern unsigned char g_FramePresentToggleAt0066C237;
extern unsigned char g_SequenceStageAt00671632;
extern unsigned char g_SequenceByteAt0066C239;
extern unsigned char g_SequenceByteAt0066C23A;
extern const char g_BattleTextureDataAt0065831C[];
extern const char g_BattleTextureRootAt00658314[];
namespace StateAudioF196 {
    void __cdecl ResetScene(int,int,int,int);
}

class BattleSceneF196 : public SceneBaseF196 {
public:
    BattleSceneF196();
    virtual ~BattleSceneF196();
};
#define FIELD(type,off) (*reinterpret_cast<type*>(reinterpret_cast<unsigned char*>(this)+(off)))
#define ACTOR_FIELD(type,actorOff,fieldOff) (*reinterpret_cast<type*>(reinterpret_cast<unsigned char*>(FIELD(void*,actorOff))+(fieldOff)))

BattleSceneF196::BattleSceneF196()
{
    FIELD(DWORD, 0x28) = timeGetTime();
    FIELD(void*, 0x08) = 0;
    FIELD(void*, 0x50) = 0;
    FIELD(void*, 0x54) = 0;
    FIELD(void*, 0x4c) = 0;
    FIELD(TextureManagerAllocF196*, 0x08) = new TextureManagerAllocF196();
    FIELD(TextureManagerAllocF196*, 0x08)->AllocateUnformattedSlots(11);
    FIELD(TextureManagerAllocF196*, 0x08)->LoadDefault(
        g_BattleTextureDataAt0065831C, g_BattleTextureRootAt00658314);
    FIELD(DigitAtlasAllocF196*, 0x4c) = new DigitAtlasAllocF196(
        FIELD(TextureManagerAllocF196*, 0x08)->GetTexture(1),
        FIELD(TextureManagerAllocF196*, 0x08)->GetTexture(8),
        FIELD(TextureManagerAllocF196*, 0x08)->GetTexture(9));
    FIELD(ComboCounterAllocF196*, 0x50) =
        new ComboCounterAllocF196(FIELD(TextureManagerAllocF196*, 0x08)->GetTexture(0), 1);
    FIELD(ComboCounterAllocF196*, 0x54) =
        new ComboCounterAllocF196(FIELD(TextureManagerAllocF196*, 0x08)->GetTexture(0), -1);
    FIELD(void*, 0x44) = g_CombatActorAAt00671418;
    FIELD(void*, 0x48) = g_CombatActorBAt0067141C;
    FIELD(DWORD, 0x60) = 0;
    FIELD(DWORD, 0x8c) = 0;
    FIELD(DWORD, 0x94) = 0;
    FIELD(float, 0x90) = -300.0f;
    FIELD(DWORD, 0x0c) = 200;
    FIELD(short, 0x1a) = 0;
    FIELD(BYTE, 0xa0) = 0;
    FIELD(BYTE, 0xa1) = 0;
    FIELD(float, 0x9c) = 1.0f;
    g_FramePresentToggleAt0066C237 = 1;
    FIELD(BYTE, 0x5c) = 0;
    FIELD(DWORD, 0x20) = 0;
    FIELD(DWORD, 0x24) = 0;
    FIELD(DWORD, 0x28) = timeGetTime();
    FIELD(BYTE, 0x1c) = 0;
    g_SequenceStageAt00671632 = 0;
    if (g_CombatModeAt006714B4 == 3) {
        g_CombatTextAt0067143C->Configure(35.0f, 360.0f, 1);
        ACTOR_FIELD(BYTE,0x44,0x6ee) = 0;
        FIELD(float, 0x8c) = -200.0f;
        FIELD(BYTE, 0x18) = 7;
        if (g_FrameClockModeAt0066C238 == 2) {
            g_FrameClockModeAt0066C238 = 4;
            g_SequenceStageAt00671632 = 1;
        }
        if (g_FrameClockModeAt0066C238 == 1)
            g_FrameClockModeAt0066C238 = 3;
    } else {
        StateAudioF196::ResetScene(0, 0, 0, 0);
        FIELD(DWORD, 0x8c) = 0;
        FIELD(BYTE, 0x18) = 0;
    }
    FIELD(DWORD, 0x10) = 0;
    FIELD(DWORD, 0x14) = 0;
    FIELD(BYTE, 0x118) = 0;
    FIELD(DWORD, 0x10c) = 0;
    FIELD(DWORD, 0x6c) = 0;
    g_SequenceByteAt0066C239 = 255;
    g_SequenceByteAt0066C23A = 255;
    FIELD(DWORD, 0x110) = 0;
    FIELD(DWORD, 0x114) = 0;
    FIELD(BYTE, 0x5e) = 0;
}
#undef ACTOR_FIELD
#undef FIELD
