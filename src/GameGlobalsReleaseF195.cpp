#include "TextOverlay.hpp"
#include <windows.h>
#include "AudioControl.hpp"
#include "SoundBank.hpp"
#include "WindowOverlayF212.hpp"

// Other resource pointers remain borrowed opaque owners. The 8-byte
// WindowOverlayF212 texture owner is shared with its constructor/destructor.
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

extern unsigned int g_GameDefaultsUseCountAt00671614;
extern SceneCombatActorF195* g_CombatActorAAt00671418;
extern SceneCombatActorF195* g_CombatActorBAt0067141C;
extern SceneThirdOwnerF195* g_SceneOwnerAt00671424;
extern WindowOverlayF212* g_WindowOverlayAt006714C4;

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
        delete g_TextRenderer;
        delete g_WindowOverlayAt006714C4;
        delete g_SoundBank;
    }
}
