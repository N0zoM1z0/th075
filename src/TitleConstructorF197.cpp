#include <windows.h>
#include <mmsystem.h>
#include <d3d8.h>

// Title-scene physical carriers: independently observed base8 and texture80.
// No nominal original class identities or full TitleScene size are assumed.
// The native 0x40AD80 callee and its nested vector/deque constructors
// independently anchor the offsets and allocation extents. These do NOT
// establish original C++ class names, container element types or the full
// semantic meaning of fields; do not reuse them as original owner layouts.
class GlobalCounterViewF197 {
public:
    GlobalCounterViewF197();
    ~GlobalCounterViewF197();
};
// SceneBase uses the actual vptr at +0 and initializes its global-count
// subobject at +4. The first distinct battle member starts at +8.
// R108 still leaves the base ctor's authored/generated origin unresolved.
class SceneBaseF197 {
public:
    SceneBaseF197();
    virtual ~SceneBaseF197();
private:
    GlobalCounterViewF197 globals;
};
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
typedef char ValidateSceneBaseF197[(sizeof(SceneBaseF197)==8)?1:-1];
typedef char ValidateTextureAllocF197[(sizeof(TextureManagerAllocF197)==80)?1:-1];
extern const char g_TitleTextureDataAt006582F0[];
extern const char g_TitleTextureRootAt006582E8[];
extern unsigned char g_TitleMenuSelectionAt00671630;
extern signed char g_ChosenPlayersAt006714C8[2];
extern unsigned char g_SequenceStageAt0067161D;

class TitleSceneF197 : public SceneBaseF197 {
public:
    TitleSceneF197();
    virtual ~TitleSceneF197();
};
#define FIELD(type,off) (*reinterpret_cast<type*>(reinterpret_cast<unsigned char*>(this) + (off)))
TitleSceneF197::TitleSceneF197()
{
    FIELD(DWORD, 0x10) = timeGetTime();
    FIELD(DWORD, 0x0c) = timeGetTime() - FIELD(DWORD, 0x10);
    FIELD(TextureManagerAllocF197*, 0x08) = new TextureManagerAllocF197();
    FIELD(TextureManagerAllocF197*, 0x08)->AllocateUnformattedSlots(4);
    FIELD(TextureManagerAllocF197*, 0x08)->LoadDefault(
        g_TitleTextureDataAt006582F0, g_TitleTextureRootAt006582E8);
    FIELD(DWORD, 0x14) = 0;
    FIELD(DWORD, 0x18) = 0;
    FIELD(BYTE, 0x20) = 255;
    FIELD(BYTE, 0x21) = 5;
    FIELD(BYTE, 0x22) = 5;
    FIELD(BYTE, 0x23) = 5;
    FIELD(BYTE, 0x38) = g_TitleMenuSelectionAt00671630;
    FIELD(BYTE, 0x2e) = 0;
    FIELD(BYTE, 0x2f) = 15;
    FIELD(BYTE, 0x30) = 30;
    FIELD(BYTE, 0x31) = 45;
    FIELD(BYTE, 0x32) = 60;
    FIELD(BYTE, 0x33) = 45;
    FIELD(BYTE, 0x34) = 60;
    FIELD(BYTE, 0x35) = 75;
    FIELD(BYTE, 0x36) = 90;
    FIELD(BYTE, 0x37) = 75;
    FIELD(BYTE, 0x24) = 0;
    FIELD(BYTE, 0x25) = 0;
    FIELD(BYTE, 0x26) = 0;
    FIELD(BYTE, 0x27) = 0;
    FIELD(BYTE, 0x28) = 0;
    FIELD(BYTE, 0x29) = 0;
    FIELD(BYTE, 0x2a) = 0;
    FIELD(BYTE, 0x2b) = 0;
    FIELD(BYTE, 0x2c) = 0;
    FIELD(BYTE, 0x2d) = 0;
    g_ChosenPlayersAt006714C8[0] = 0;
    g_ChosenPlayersAt006714C8[1] = 0;
    g_SequenceStageAt0067161D = 0;
    FIELD(DWORD, 0x1c) = 0;
}
#undef FIELD
