#include "PlayerState.hpp"
#include "BattleSessionState.hpp"
#include "GameSharedState.hpp"
#include "TextOverlay.hpp"
#include "CameraMotion.hpp"
#include "SpriteDraw40CA80.hpp"
#include "TextureManagerF198.hpp"
#include <windows.h>
#include <mmsystem.h>
#include <d3d8.h>
#include "BattleScene.hpp"

extern const char g_BattleTextureDataAt0065831C[];
extern const char g_BattleTextureRootAt00658314[];
namespace StateAudioF196 {
}


BattleScene::BattleScene()
{
    field028 = timeGetTime();
    textures = 0;
    comboDisplays[0] = 0;
    comboDisplays[1] = 0;
    digitAtlas = 0;
    textures = new TextureManagerF198();
    static_cast<TextureManagerF198*>(textures)->AllocateUnformattedSlots(11);
    static_cast<TextureManagerF198*>(textures)->LoadDefault(
        g_BattleTextureDataAt0065831C, g_BattleTextureRootAt00658314);
    digitAtlas = new DigitAtlasesF177(
        static_cast<TextureManagerF198*>(textures)->GetTexture(1),
        static_cast<TextureManagerF198*>(textures)->GetTexture(8),
        static_cast<TextureManagerF198*>(textures)->GetTexture(9));
    comboDisplays[0] =
        new ComboDisplay(static_cast<TextureManagerF198*>(textures)->GetTexture(0), 1);
    comboDisplays[1] =
        new ComboDisplay(static_cast<TextureManagerF198*>(textures)->GetTexture(0), -1);
    fighters[0] = g_BattleFightersAt00671418[0];
    fighters[1] = g_BattleFightersAt00671418[1];
    field060 = 0;
    field08C = 0.0f;
    field094 = 0;
    field090 = -300.0f;
    field00C = 200;
    field01A = 0;
    field0A0 = 0;
    field0A1 = 0;
    field09C = 1.0f;
    g_FramePresentToggle = 1;
    field05C = 0;
    field020 = 0;
    field024 = 0;
    field028 = timeGetTime();
    field01C = 0;
    g_InputCanCancelAt00671632 = 0;
    if (g_CombatMode == 3) {
        g_TextRenderer->ConfigureText(35.0f, 360.0f, 1);
        fighters[0]->noticeEnabled = 0;
        field08C = -200.0f;
        field018 = 7;
        if (g_ReplayModeAt0066C238 == 2) {
            g_ReplayModeAt0066C238 = 4;
            g_InputCanCancelAt00671632 = 1;
        }
        if (g_ReplayModeAt0066C238 == 1)
            g_ReplayModeAt0066C238 = 3;
    } else {
        CameraMotionOverrideF484::SetOverride(0, 0.0f, 0.0f, 0.0f);
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
