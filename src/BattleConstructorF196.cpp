#include <windows.h>
#include <mmsystem.h>
#include <d3d8.h>
#include "BattleScene.hpp"

// Source-compatible physical allocation carriers for this constructor only.
// The native 0x40AD80 callee and its nested vector/deque constructors
// independently anchor the offsets and allocation extents. These do NOT
// establish original C++ class names, container element types or the full
// semantic meaning of fields; do not reuse them as original owner layouts.
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
typedef char ValidateTextureAllocF196[(sizeof(TextureManagerAllocF196)==80)?1:-1];

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


BattleScene::BattleScene()
{
    field028 = timeGetTime();
    textures = 0;
    comboDisplays[0] = 0;
    comboDisplays[1] = 0;
    digitAtlas = 0;
    textures = new TextureManagerAllocF196();
    static_cast<TextureManagerAllocF196*>(textures)->AllocateUnformattedSlots(11);
    static_cast<TextureManagerAllocF196*>(textures)->LoadDefault(
        g_BattleTextureDataAt0065831C, g_BattleTextureRootAt00658314);
    digitAtlas = new DigitAtlas(
        static_cast<TextureManagerAllocF196*>(textures)->GetTexture(1),
        static_cast<TextureManagerAllocF196*>(textures)->GetTexture(8),
        static_cast<TextureManagerAllocF196*>(textures)->GetTexture(9));
    comboDisplays[0] =
        new ComboDisplay(static_cast<TextureManagerAllocF196*>(textures)->GetTexture(0), 1);
    comboDisplays[1] =
        new ComboDisplay(static_cast<TextureManagerAllocF196*>(textures)->GetTexture(0), -1);
    fighters[0] = static_cast<Fighter*>(g_CombatActorAAt00671418);
    fighters[1] = static_cast<Fighter*>(g_CombatActorBAt0067141C);
    field060 = 0;
    field08C = 0.0f;
    field094 = 0;
    field090 = -300.0f;
    field00C = 200;
    field01A = 0;
    field0A0 = 0;
    field0A1 = 0;
    field09C = 1.0f;
    g_FramePresentToggleAt0066C237 = 1;
    field05C = 0;
    field020 = 0;
    field024 = 0;
    field028 = timeGetTime();
    field01C = 0;
    g_SequenceStageAt00671632 = 0;
    if (g_CombatModeAt006714B4 == 3) {
        g_CombatTextAt0067143C->Configure(35.0f, 360.0f, 1);
        fighters[0]->noticeEnabled = 0;
        field08C = -200.0f;
        field018 = 7;
        if (g_FrameClockModeAt0066C238 == 2) {
            g_FrameClockModeAt0066C238 = 4;
            g_SequenceStageAt00671632 = 1;
        }
        if (g_FrameClockModeAt0066C238 == 1)
            g_FrameClockModeAt0066C238 = 3;
    } else {
        StateAudioF196::ResetScene(0, 0, 0, 0);
        field08C = 0.0f;
        field018 = 0;
    }
    field010 = 0;
    field014 = 0;
    field118 = 0;
    field10C = 0;
    field06C = 0;
    g_SequenceByteAt0066C239 = 255;
    g_SequenceByteAt0066C23A = 255;
    field110 = 0;
    field114 = 0;
    field05E = 0;
}
