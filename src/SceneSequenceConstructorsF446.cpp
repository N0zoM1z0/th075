#include <windows.h>
#include <mmsystem.h>
// Two independently original-R036/R043 complete authored scene C++
// constructors; actual 24 vs 27 texture records and stage mode 40 vs 41
// are separately checked. C++ /GX EH, vtables and the imported WinMM
// timeGetTime call are compiled, not embedded native bytes.
// Only the physical 8-byte base, 80-byte texture allocation and real fields.
class SceneBaseF446 {
    void* originalConfiguration;
public: SceneBaseF446(); virtual ~SceneBaseF446();
};
class TextureManagerF446 {
    unsigned char observedAllocation[80];
public:TextureManagerF446();void AllocateSlots(int);void LoadArchive(const char*,const char*);
};
typedef char CheckTexture80F446[(sizeof(TextureManagerF446)==80)?1:-1];
extern const char g_OpeningPathAt00657CCC[];
extern const char g_OpeningRootAt00657CC4[];
extern const char g_StaffPathAt006582A0[];
extern const char g_StaffRootAt00658298[];
extern void BeforeStaffAt00407D70();
extern void AfterStaffAt00407CC0();
extern void SetStageAt00419CB0(int);
extern void ReloadStageAt00419DF0();
class OpeningSceneF446 : public SceneBaseF446 {
    TextureManagerF446* texture;
    unsigned int elapsed;
    unsigned int startTicks;
public:OpeningSceneF446();virtual ~OpeningSceneF446();
};
class StaffRollSceneF446 : public SceneBaseF446 {
    TextureManagerF446* texture;
    unsigned int elapsed;
    unsigned int startTicks;
public:StaffRollSceneF446();virtual ~StaffRollSceneF446();
};
OpeningSceneF446::OpeningSceneF446() {
    texture=new TextureManagerF446;
    texture->AllocateSlots(24);
    texture->LoadArchive(g_OpeningPathAt00657CCC,g_OpeningRootAt00657CC4);
    SetStageAt00419CB0(40);
    ReloadStageAt00419DF0();
    startTicks=timeGetTime();
    elapsed=timeGetTime()-startTicks;
}
StaffRollSceneF446::StaffRollSceneF446() {
    BeforeStaffAt00407D70();
    SetStageAt00419CB0(41);
    texture=new TextureManagerF446;
    texture->AllocateSlots(27);
    texture->LoadArchive(g_StaffPathAt006582A0,g_StaffRootAt00658298);
    startTicks=timeGetTime();
    elapsed=timeGetTime()-startTicks;
    AfterStaffAt00407CC0();
}
