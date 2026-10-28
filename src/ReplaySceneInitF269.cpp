#include <windows.h>

// Only physical scene-base boundary, game globals and observed file/texture
// interfaces are represented. No complete private scene ABI is assumed.
class ReplayBaseF269 {
    void* configuration;
public:
    ReplayBaseF269();
    virtual ~ReplayBaseF269();
};
class ReplayTextureF269 {
    unsigned char actualBytes[80];
public:
    ReplayTextureF269();
    void AllocateSlots(int slots);
    void LoadDefault(const char* file,const char* directory);
};
typedef char AssertReplayTextureF269[(sizeof(ReplayTextureF269)==80)?1:-1];
class ProgressRecordsF269 {
public:
    void SetSelection(signed char player,signed char difficulty);
    void* GetSelectedRecordAddress();
    unsigned char InsertRankedScore(int selectedFighterValue);
    void StoreWorkingScore(unsigned char value);
};
class ReplaySavePathsF269 {
public:
    int FindAvailablePath(char* filename);
};
extern ProgressRecordsF269 g_ProgressRecordsAt006718F8;
extern ReplaySavePathsF269 g_ReplaySavePathsAt00671750;
extern unsigned char g_CurrentFighterAt006714C8;
extern unsigned char g_CurrentDifficultyAt006714D0;
extern unsigned char* g_SelectedFighterAt00671418;
extern const char g_ReplaySceneRootAt00657F44[];
extern const char g_ReplaySceneFileAt00657F4C[];
class ReplaySceneInitF269 : public ReplayBaseF269 {
    ReplayTextureF269* texture;
public:
    ReplaySceneInitF269();
    virtual ~ReplaySceneInitF269();
};
#define FIELD(type,off) (*reinterpret_cast<type*>(reinterpret_cast<unsigned char*>(this)+(off)))
ReplaySceneInitF269::ReplaySceneInitF269()
{
    texture=new ReplayTextureF269();
    texture->AllocateSlots(3);
    texture->LoadDefault(g_ReplaySceneFileAt00657F4C,g_ReplaySceneRootAt00657F44);
    FIELD(short,0x10)=0;
    FIELD(short,0x12)=0;
    FIELD(short,0x14)=0;
    g_ProgressRecordsAt006718F8.SetSelection(g_CurrentFighterAt006714C8,g_CurrentDifficultyAt006714D0);
    FIELD(void*,0x0c)=g_ProgressRecordsAt006718F8.GetSelectedRecordAddress();
    FIELD(unsigned char,0x120)=reinterpret_cast<ProgressRecordsF269*>(FIELD(void*,0x0c))->InsertRankedScore(
        *reinterpret_cast<int*>(g_SelectedFighterAt00671418+0x2d0));
    g_ProgressRecordsAt006718F8.StoreWorkingScore(FIELD(unsigned char,0x120));
    FIELD(int,0x18)=g_ReplaySavePathsAt00671750.FindAvailablePath(
        reinterpret_cast<char*>(this)+0x1c);
}
#undef FIELD
