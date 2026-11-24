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
extern void* g_StaffRollFighterAt00671418;
extern signed char g_StaffRollCompletionAt00671623;
extern signed char g_ReplayNameModeAt006714CE;
extern unsigned int g_StaffRollBestScoreAt00671420;
class StaffRollAdvanceF450 {
public:
    virtual void V00();
    virtual void V04();
    virtual void AdvanceVirtual();
    unsigned short Advance();
    void UpdateStaffControls();
    void AdvanceHookAt00438CF0();
public:
    // Observed fields; meanings not yet known.
    unsigned char unknown004[0x00C - 0x004];
    unsigned int field00C;
    unsigned int field010;
};
unsigned short StaffRollAdvanceF450::Advance() {
    UpdateStaffControls();
    AdvanceVirtual();
    Graphics::Present();
    AdvanceHookAt00438CF0();
    if (static_cast<unsigned int>(g_InputMappings[0].held.counts[2])==1) {
        if (field00C>0x14C08 || field00C<0x13880) {
            MusicF204::PlayTrackByIndex(40);
            AudioControl407CA0::ScheduleFade(-10000,-160,1,1);
            if (g_StaffRollFighterAt00671418) {
            if (g_StaffRollCompletionAt00671623<3) g_ReplayNameModeAt006714CE=0;
            else g_ReplayNameModeAt006714CE=-1;
            if (static_cast<Fighter*>(g_StaffRollFighterAt00671418)->score>g_StaffRollBestScoreAt00671420)
                return 0x110A;
            return 0x1107;
        }
            return 0x1102;
        }
    }
    field00C=timeGetTime()-field010;
    return 0xB;
}

void StaffRollAdvanceF450::AdvanceHookAt00438CF0()
{
}
