#include <windows.h>
#include <mmsystem.h>
// Complete original R043 208-byte StaffRoll scene advancement.
// The source-scope of stage actions AND fighter result branch is the
// outside-window condition. Unlike old F450/F451/F486/F487 probes,
// this reproduces the genuine native unsigned JA at 0x3E and single
// native JAE at 0x4A to the time-reset block at 0xB6, without jumps.
// Complete original game staff-roll scene advancement / ending score policy.
// Borrowed native stage, time and fighter score ABIs only.
extern unsigned int g_StaffRollPhaseAt0067166C;
extern void* g_StaffRollFighterAt00671418;
extern signed char g_StaffRollCompletionAt00671623;
extern signed char g_ReplayNameModeAt006714CE;
extern unsigned int g_StaffRollBestScoreAt00671420;
extern void SetStageAt00419CB0(int);
extern void __cdecl ConfigureStaffViewportAt00407E60(int,int,int,int);
extern void BeforeStaffAdvanceAt004028F0();
class StaffRollAdvanceF450 {
public:
    virtual void V00();
    virtual void V04();
    virtual void AdvanceVirtual();
    unsigned short Advance();
    void UpdateStaffControls();
    void TickStaffTime();
};
#define FIELD(T,o) (*reinterpret_cast<T*>(reinterpret_cast<unsigned char*>(this)+(o)))
unsigned short StaffRollAdvanceF450::Advance() {
    UpdateStaffControls();
    AdvanceVirtual();
    BeforeStaffAdvanceAt004028F0();
    TickStaffTime();
    if (g_StaffRollPhaseAt0067166C==1) {
        if (FIELD(unsigned int,0xC)>0x14C08 || FIELD(unsigned int,0xC)<0x13880) {
            SetStageAt00419CB0(40);
            ConfigureStaffViewportAt00407E60(-10000,-160,1,1);
            if (g_StaffRollFighterAt00671418) {
            if (g_StaffRollCompletionAt00671623<3) g_ReplayNameModeAt006714CE=0;
            else g_ReplayNameModeAt006714CE=-1;
            if (*reinterpret_cast<unsigned int*>(reinterpret_cast<unsigned char*>(g_StaffRollFighterAt00671418)+0x2D0)>g_StaffRollBestScoreAt00671420)
                return 0x110A;
            return 0x1107;
        }
            return 0x1102;
        }
    }
    FIELD(unsigned int,0xC)=timeGetTime()-FIELD(unsigned int,0x10);
    return 0xB;
}
#undef FIELD
