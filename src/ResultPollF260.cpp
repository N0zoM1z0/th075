#include <windows.h>

// Only borrowed physical input interfaces are exposed: the original
// input frames, scene layout, and notification types remain unproven.
class ResultInputFrameF260 {
public:
    void Poll();
    bool IsHeld(int button);
};
extern ResultInputFrameF260 g_ResultInputPrimaryAt00671638;
extern ResultInputFrameF260 g_ResultInputSecondaryAt00671680;
extern int g_ResultPrimaryVerticalAt00671668;
extern int g_ResultSecondaryVerticalAt006716B0;
extern int g_ResultPrimaryHorizontalAt00671664;
extern int g_ResultSecondaryHorizontalAt006716AC;
extern int g_ResultPrimaryConfirmAt0067166C;
extern int g_ResultSecondaryConfirmAt006716B4;
extern int g_ResultPrimaryCancelAt00671670;
extern int g_ResultSecondaryCancelAt006716B8;
namespace ResultInputServiceF260 {
    void __cdecl BeginFrame();
    void __cdecl EndFrame();
    void __cdecl ToggleWindowMode();
}
class ResultScenePollF260 {
public:
    void PollInput();
};
#define FIELD(type,off) (*reinterpret_cast<type*>(reinterpret_cast<unsigned char*>(this)+(off)))
void ResultScenePollF260::PollInput()
{
    ResultInputServiceF260::BeginFrame();
    ResultInputServiceF260::EndFrame();
    FIELD(signed char,0x1bf)=0;
    FIELD(signed char,0x1c0)=0;
    FIELD(signed char,0x1c1)=0;
    FIELD(signed char,0x1c2)=0;
    g_ResultInputPrimaryAt00671638.Poll();
    g_ResultInputSecondaryAt00671680.Poll();
    if (g_ResultPrimaryVerticalAt00671668==1 || g_ResultSecondaryVerticalAt006716B0==1)
        FIELD(signed char,0x1c0)=1;
    if (g_ResultPrimaryVerticalAt00671668==-1 || g_ResultSecondaryVerticalAt006716B0==-1)
        FIELD(signed char,0x1c0)=-1;
    if (g_ResultPrimaryHorizontalAt00671664==1 || g_ResultSecondaryHorizontalAt006716AC==1)
        FIELD(signed char,0x1bf)=1;
    if (g_ResultPrimaryHorizontalAt00671664==-1 || g_ResultSecondaryHorizontalAt006716AC==-1)
        FIELD(signed char,0x1bf)=-1;
    if (g_ResultPrimaryConfirmAt0067166C==1 || g_ResultSecondaryConfirmAt006716B4==1)
        FIELD(signed char,0x1c1)=1;
    if (g_ResultPrimaryCancelAt00671670==1 || g_ResultSecondaryCancelAt006716B8==1)
        FIELD(signed char,0x1c2)=1;
    if (g_ResultInputPrimaryAt00671638.IsHeld(1))
        FIELD(signed char,0x1c2)=1;
    if (g_ResultInputPrimaryAt00671638.IsHeld(0x1c)) {
        if (g_ResultInputPrimaryAt00671638.IsHeld(0x38) || g_ResultInputPrimaryAt00671638.IsHeld(0xb8))
            ResultInputServiceF260::ToggleWindowMode();
    }
}
#undef FIELD
