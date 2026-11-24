#include "TextureManagerF198.hpp"
#include "ReplaySegmentedQueueF219.hpp"
// Complete original 260-byte R109 name-entry scene constructor.
// Actual VC7.1 /GX EH, native vtable, replay archive pathname and
// resource selection reader are generated from natural source.
// R109 original name-entry scene C++ constructor with real textures and
// game replay selection state. Only borrowed scene and archive ABI.
class SceneBaseF435 {
    void* config;
public: SceneBaseF435();virtual ~SceneBaseF435();
};
extern signed char g_ReplayNameModeAt006714CE;
extern char g_ReplayDataPathAt00657F84[];
extern char g_ReplayArchiveRootAt00657F7C[];
class NameEntryInitF435 : public SceneBaseF435 {
    TextureManagerF198* texture;  // +0x08
    unsigned char field00C;         // +0x0C
    short field00E;                 // +0x0E
    short field010;                 // +0x10
    short field012;                 // +0x12
    short field014;                 // +0x14
    int pathIndex;                  // +0x18
    char replayPath[MAX_PATH];       // +0x1C
public:NameEntryInitF435();virtual ~NameEntryInitF435();
};
NameEntryInitF435::NameEntryInitF435() {
    texture = new TextureManagerF198;
    texture->AllocateUnformattedSlots(3);
    texture->LoadDefault(g_ReplayDataPathAt00657F84,g_ReplayArchiveRootAt00657F7C);
    field00E=0;
    field010=0;
    field012=0;
    field014=0;
    if(g_ReplayNameModeAt006714CE<0) field00C=1;
    else field00C=0;
    pathIndex = g_ReplayRecords.FindAvailablePath(replayPath);
}
