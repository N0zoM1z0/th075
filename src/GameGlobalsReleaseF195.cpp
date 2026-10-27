#include <windows.h>

// Borrowed owner pointers only: no complete heap object layouts or
// allocations are asserted by this file.
class SceneCombatActorF195 {
public:
    virtual void Slot0();
    virtual void Slot1();
    virtual void Slot2();
    virtual void Slot3();
    virtual void Slot4();
    virtual ~SceneCombatActorF195();
};
class SceneThirdOwnerF195 {
public:
    virtual ~SceneThirdOwnerF195();
};
class SceneResourceOwnerAF195 { public: ~SceneResourceOwnerAF195(); };
class SceneResourceOwnerBF195 { public: ~SceneResourceOwnerBF195(); };
class SceneResourceOwnerCF195 { public: ~SceneResourceOwnerCF195(); };

extern unsigned int g_GameDefaultsUseCountAt00671614;
extern SceneCombatActorF195* g_CombatActorAAt00671418;
extern SceneCombatActorF195* g_CombatActorBAt0067141C;
extern SceneThirdOwnerF195* g_SceneOwnerAt00671424;
extern SceneResourceOwnerAF195* g_ResourceOwnerAAt0067143C;
extern SceneResourceOwnerBF195* g_ResourceOwnerBAt006714C4;
extern SceneResourceOwnerCF195* g_ResourceOwnerCAt00671618;
namespace AudioControl407CA0 { void __cdecl ClearPlayback(); }

class GameGlobalsReleaseF195 {
public:
    void Release();
};
void GameGlobalsReleaseF195::Release()
{
    --g_GameDefaultsUseCountAt00671614;
    if (g_GameDefaultsUseCountAt00671614 == 0) {
        if (g_CombatActorAAt00671418) delete g_CombatActorAAt00671418;
        if (g_CombatActorBAt0067141C) delete g_CombatActorBAt0067141C;
        if (g_SceneOwnerAt00671424) delete g_SceneOwnerAt00671424;
        g_CombatActorAAt00671418 = 0;
        g_CombatActorBAt0067141C = 0;
        g_SceneOwnerAt00671424 = 0;
        AudioControl407CA0::ClearPlayback();
        delete g_ResourceOwnerAAt0067143C;
        delete g_ResourceOwnerBAt006714C4;
        delete g_ResourceOwnerCAt00671618;
    }
}
