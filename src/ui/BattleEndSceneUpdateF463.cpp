#include "engine/SceneTransition.hpp"
#include "battle/BattleResultState.hpp"
#include "ui/BattleEndScene.hpp"
#include "battle/Fighter.hpp"
#include "battle/PlayerState.hpp"
#include "engine/GameSharedState.hpp"
#include "audio/AudioControl.hpp"
#include "graphics/Graphics.hpp"
// Entire original 152-byte battle end scene state policy, including the
// real fighter virtual action and mode-specific score return value.
unsigned short BattleEndScene::Update() {
    PollInput();
    Render();
    g_BattleFightersAt00671418[0]->AdvanceSequence();
    Graphics::Present();
    if (g_BattleFightersAt00671418[0]->field6EF) {
        if (g_StageAt0067161E==10) return SceneTransition::WhiteIn | SceneTransition::WhiteOut | SceneId::Credits;
        MusicF204::PlayTrackByIndex(40);
        AudioControl407CA0::ScheduleFade(-10000,-300,1,1);
        if (g_StateScoreThreshold < g_BattleFightersAt00671418[0]->score) return SceneTransition::BlackIn | SceneTransition::BlackOut | SceneId::ScoreNameEntry;
        return SceneTransition::WhiteIn | SceneTransition::WhiteOut | SceneId::Title;
    }
    return 8;
}
