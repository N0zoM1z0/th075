#include "BattleResultState.hpp"
#include "BattleEndScene.hpp"
#include "Fighter.hpp"
#include "PlayerState.hpp"
#include "GameSharedState.hpp"
#include "AudioControl.hpp"
#include "Graphics.hpp"
// Entire original 152-byte battle end scene state policy, including the
// real fighter virtual action and mode-specific score return value.
unsigned short BattleEndScene::Update() {
    PollInput();
    Render();
    g_BattleFightersAt00671418[0]->AdvanceSequence();
    Graphics::Present();
    if (g_BattleFightersAt00671418[0]->field6EF) {
        if (g_StageAt0067161E==10) return 0x110B;
        MusicF204::PlayTrackByIndex(40);
        AudioControl407CA0::ScheduleFade(-10000,-300,1,1);
        if (g_StateScoreThreshold < g_BattleFightersAt00671418[0]->score) return 0x220A;
        return 0x1102;
    }
    return 8;
}
