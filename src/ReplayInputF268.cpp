#include <windows.h>

// The complete replay-scene and shared input-frame private layouts remain
// unproven; this caller uses only target-observed physical state fields.
class ReplayInputFrameF268 {
public:
    void Poll();
    bool IsHeld(int button);
};
extern ReplayInputFrameF268 g_ReplayInputPrimaryAt00671638;
extern ReplayInputFrameF268 g_ReplayInputSecondaryAt00671680;
extern int g_ReplayPrimaryVerticalAt00671668;
extern int g_ReplaySecondaryVerticalAt006716B0;
extern int g_ReplayPrimaryHorizontalAt00671664;
extern int g_ReplaySecondaryHorizontalAt006716AC;
extern int g_ReplayPrimaryConfirmAt0067166C;
extern int g_ReplaySecondaryConfirmAt006716B4;
extern int g_ReplayPrimaryCancelAt00671670;
extern int g_ReplaySecondaryCancelAt006716B8;
namespace ReplayInputServiceF268 {
    void __cdecl BeginFrame();
    void __cdecl EndFrame();
    void __cdecl ToggleWindowMode();
}
class ReplayInputPollF268 {
public:
    void PollInput();
};
#define FIELD(type,off) (*reinterpret_cast<type*>(reinterpret_cast<unsigned char*>(this)+(off)))
void ReplayInputPollF268::PollInput()
{
    ReplayInputServiceF268::BeginFrame();
    ReplayInputServiceF268::EndFrame();
    FIELD(signed char,0x4d)=0;
    FIELD(signed char,0x4e)=0;
    FIELD(signed char,0x4f)=0;
    FIELD(signed char,0x50)=0;
    g_ReplayInputPrimaryAt00671638.Poll();
    g_ReplayInputSecondaryAt00671680.Poll();
    if (g_ReplayPrimaryVerticalAt00671668==1 || g_ReplaySecondaryVerticalAt006716B0==1)
        FIELD(signed char,0x4e)=1;
    if (g_ReplayPrimaryVerticalAt00671668==-1 || g_ReplaySecondaryVerticalAt006716B0==-1)
        FIELD(signed char,0x4e)=-1;
    if (g_ReplayPrimaryHorizontalAt00671664==1 || g_ReplaySecondaryHorizontalAt006716AC==1)
        FIELD(signed char,0x4d)=1;
    if (g_ReplayPrimaryHorizontalAt00671664==-1 || g_ReplaySecondaryHorizontalAt006716AC==-1)
        FIELD(signed char,0x4d)=-1;
    if (g_ReplayPrimaryConfirmAt0067166C==1 || g_ReplaySecondaryConfirmAt006716B4==1)
        FIELD(signed char,0x4f)=1;
    if (g_ReplayPrimaryCancelAt00671670==1 || g_ReplaySecondaryCancelAt006716B8==1)
        FIELD(signed char,0x50)=1;
    if (g_ReplayInputPrimaryAt00671638.IsHeld(1))
        FIELD(signed char,0x50)=1;
    if (g_ReplayInputPrimaryAt00671638.IsHeld(0x1c)) {
        if (g_ReplayInputPrimaryAt00671638.IsHeld(0x38) || g_ReplayInputPrimaryAt00671638.IsHeld(0xb8))
            ReplayInputServiceF268::ToggleWindowMode();
    }
}
#undef FIELD
