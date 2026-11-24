#include "Fighter.hpp"
#include "PlayerState.hpp"
#include "TextOverlay.hpp"
#include "GameDefaultsF193.hpp"
#include <windows.h>
#include "AudioControl.hpp"
#include "SoundBank.hpp"
#include "WindowOverlayF212.hpp"

// Other resource pointers remain borrowed opaque owners. The 8-byte
// WindowOverlayF212 texture owner is shared with its constructor/destructor.
class SceneThirdOwnerF195 {
public:
    virtual ~SceneThirdOwnerF195();
};

extern unsigned int g_GameDefaultsUseCountAt00671614;
extern SceneThirdOwnerF195* g_SceneOwnerAt00671424;

GameDefaultsF193::~GameDefaultsF193()
{
    --g_GameDefaultsUseCountAt00671614;
    if (g_GameDefaultsUseCountAt00671614 == 0) {
        if (g_BattleFightersAt00671418[0]) delete reinterpret_cast<Fighter*>(g_BattleFightersAt00671418[0]);
        if (g_BattleFightersAt00671418[1]) delete reinterpret_cast<Fighter*>(g_BattleFightersAt00671418[1]);
        if (g_SceneOwnerAt00671424) delete g_SceneOwnerAt00671424;
        g_BattleFightersAt00671418[0] = 0;
        g_BattleFightersAt00671418[1] = 0;
        g_SceneOwnerAt00671424 = 0;
        AudioControl407CA0::ClearPlayback();
        delete g_TextRenderer;
        delete g_WindowOverlayAt006714C4;
        delete g_SoundBank;
    }
}
