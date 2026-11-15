#include "TitleScene.hpp"
#include <windows.h>
#include <mmsystem.h>
#include <d3d8.h>

// Title-scene physical carriers: independently observed base8 and texture80.
// No nominal original class identities or full TitleScene size are assumed.
// The native 0x40AD80 callee and its nested vector/deque constructors
// independently anchor the offsets and allocation extents. These do NOT
// establish original C++ class names, container element types or the full
// semantic meaning of fields; do not reuse them as original owner layouts.
// SceneBase uses the actual vptr at +0 and initializes its global-count
// subobject at +4. The first distinct battle member starts at +8.
// R108 still leaves the base ctor's authored/generated origin unresolved.
// Component widths are drawn from the actual 0x40AD80 nested constructors:
// base 8, three 16-byte vector subregions, one 20-byte deque, trailing byte.
struct Vc7VectorStorageF197 {
    DWORD first, last, capacity, policy;
};
struct Vc7DequeStorageF197 {
    DWORD map, begin, end, count, policy;
};
class TextureManagerAllocF197 {
    DWORD unresolvedBaseWordAt0, stateAt4;
    Vc7VectorStorageF197 vectorA, vectorB, vectorC;
    Vc7DequeStorageF197 deque;
    unsigned char defaultTextureDepth;
public:
    TextureManagerAllocF197();
    void AllocateUnformattedSlots(int);
    void LoadDefault(const char*, const char*);
    IDirect3DTexture8* GetTexture(int);
};
typedef char ValidateTextureAllocF197[(sizeof(TextureManagerAllocF197)==80)?1:-1];
extern const char g_TitleTextureDataAt006582F0[];
extern const char g_TitleTextureRootAt006582E8[];
extern unsigned char g_TitleMenuSelectionAt00671630;
extern signed char g_ChosenPlayersAt006714C8[2];
extern unsigned char g_SequenceStageAt0067161D;

TitleScene::TitleScene()
{
    field010 = timeGetTime();
    field00C = timeGetTime() - field010;
    textures = new TextureManagerAllocF197();
    static_cast<TextureManagerAllocF197*>(textures)->AllocateUnformattedSlots(4);
    static_cast<TextureManagerAllocF197*>(textures)->LoadDefault(
        g_TitleTextureDataAt006582F0, g_TitleTextureRootAt006582E8);
    field014 = 0;
    field018 = 0;
    field020 = 255;
    field021 = 5;
    field022 = 5;
    field023 = 5;
    menuIndex = g_TitleMenuSelectionAt00671630;
    itemDelay[0] = 0;
    itemDelay[1] = 15;
    itemDelay[2] = 30;
    itemDelay[3] = 45;
    itemDelay[4] = 60;
    itemDelay[5] = 45;
    itemDelay[6] = 60;
    itemDelay[7] = 75;
    itemDelay[8] = 90;
    itemDelay[9] = 75;
    itemAlpha[0] = 0;
    itemAlpha[1] = 0;
    itemAlpha[2] = 0;
    itemAlpha[3] = 0;
    itemAlpha[4] = 0;
    itemAlpha[5] = 0;
    itemAlpha[6] = 0;
    itemAlpha[7] = 0;
    itemAlpha[8] = 0;
    itemAlpha[9] = 0;
    g_ChosenPlayersAt006714C8[0] = 0;
    g_ChosenPlayersAt006714C8[1] = 0;
    g_SequenceStageAt0067161D = 0;
    field01C = 0;
}
