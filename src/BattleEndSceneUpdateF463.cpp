#include "Fighter.hpp"
#include "PlayerState.hpp"
#include "GameSharedState.hpp"
#include "AudioControl.hpp"
#include "Graphics.hpp"
// Entire original 152-byte battle end scene state policy, including the
// real fighter virtual action and mode-specific score return value.
class BattleEndSceneF463 {
public:
    virtual void V0();virtual void V4();virtual void AdvanceVisuals();
    unsigned short Update();
    void PollInput();
};
extern unsigned int g_BestResultScoreAt00671420;
unsigned short BattleEndSceneF463::Update() {
    PollInput();
    AdvanceVisuals();
    reinterpret_cast<Fighter*>(g_BattleFightersAt00671418[0])->AdvanceSequence();
    Graphics::Present();
    if (reinterpret_cast<Fighter*>(g_BattleFightersAt00671418[0])->field6EF) {
        if (g_StageAt0067161E==10) return 0x110B;
        MusicF204::PlayTrackByIndex(40);
        AudioControl407CA0::ScheduleFade(-10000,-300,1,1);
        if (g_BestResultScoreAt00671420 < reinterpret_cast<Fighter*>(g_BattleFightersAt00671418[0])->score) return 0x220A;
        return 0x1102;
    }
    return 8;
}
