#include "GameProgress.hpp"
#include "TextureManagerF198.hpp"
#include <windows.h>

// Only physical scene-base boundary, game globals and observed file/texture
// interfaces are represented. No complete private scene ABI is assumed.
class ReplayBaseF269 {
    void* configuration;
public:
    ReplayBaseF269();
    virtual ~ReplayBaseF269();
};
class ReplaySavePathsF269 {
public:
    int FindAvailablePath(char* filename);
};
extern ReplaySavePathsF269 g_ReplaySavePathsAt00671750;
extern unsigned char g_CurrentFighterAt006714C8;
extern unsigned char g_CurrentDifficultyAt006714D0;
extern unsigned char* g_SelectedFighterAt00671418;
extern const char g_ReplaySceneRootAt00657F44[];
extern const char g_ReplaySceneFileAt00657F4C[];
class ReplaySceneInitF269 : public ReplayBaseF269 {
    TextureManagerF198* texture;
public:
    ReplaySceneInitF269();
    virtual ~ReplaySceneInitF269();
};
#define FIELD(type,off) (*reinterpret_cast<type*>(reinterpret_cast<unsigned char*>(this)+(off)))
ReplaySceneInitF269::ReplaySceneInitF269()
{
    texture=new TextureManagerF198();
    texture->AllocateUnformattedSlots(3);
    texture->LoadDefault(g_ReplaySceneFileAt00657F4C,g_ReplaySceneRootAt00657F44);
    FIELD(short,0x10)=0;
    FIELD(short,0x12)=0;
    FIELD(short,0x14)=0;
    g_GameProgress.SetSelection(g_CurrentFighterAt006714C8,g_CurrentDifficultyAt006714D0);
    FIELD(void*,0x0c)=g_GameProgress.GetSelectedRecordAddress();
    FIELD(unsigned char,0x120)=static_cast<ProgressDifficulty*>(FIELD(void*,0x0c))->InsertRankedScore(
        *reinterpret_cast<int*>(g_SelectedFighterAt00671418+0x2d0));
    g_GameProgress.StoreWorkingEightBytes(FIELD(unsigned char,0x120));
    FIELD(int,0x18)=g_ReplaySavePathsAt00671750.FindAvailablePath(
        reinterpret_cast<char*>(this)+0x1c);
}
#undef FIELD
