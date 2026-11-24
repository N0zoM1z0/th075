#include "BattleResultState.hpp"
#include "SequenceScenes.hpp"
#include "PlayerState.hpp"
#include "BattleSessionState.hpp"
#include "SelectionInput4388D0.hpp"
#include "AudioControl.hpp"
#include "Graphics.hpp"
#include <windows.h>
#include <mmsystem.h>
#include "Fighter.hpp"
// Complete original R043 208-byte StaffRoll scene advancement.
// The source-scope of stage actions AND fighter result branch is the
// outside-window condition. Unlike old F450/F451/F486/F487 probes,
// this reproduces the genuine native unsigned JA at 0x3E and single
// native JAE at 0x4A to the time-reset block at 0xB6, without jumps.
// Complete original game staff-roll scene advancement / ending score policy.
// Borrowed native stage, time and fighter score ABIs only.
unsigned short StaffRollScene::Update() {
    PollSkipInput();
    Render();
    Graphics::Present();
    AdvanceHookAt00438CF0();
    if (static_cast<unsigned int>(g_InputMappings[0].held.counts[2])==1) {
        if (elapsed>0x14C08 || elapsed<0x13880) {
            MusicF204::PlayTrackByIndex(40);
            AudioControl407CA0::ScheduleFade(-10000,-160,1,1);
            if (g_BattleFightersAt00671418[0]) {
            if (g_ContinueCountAt00671623<3) g_StateReturnFlag=0;
            else g_StateReturnFlag=-1;
            if (g_BattleFightersAt00671418[0]->score>g_StateScoreThreshold)
                return 0x110A;
            return 0x1107;
        }
            return 0x1102;
        }
    }
    elapsed=timeGetTime()-startTicks;
    return 0xB;
}

void StaffRollScene::AdvanceHookAt00438CF0()
{
}
