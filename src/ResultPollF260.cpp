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
public:
    // Observed fields; meanings not yet known.
    unsigned char unknown000[0x1BF - 0x000];
    signed char field1BF;
    signed char field1C0;
    signed char field1C1;
    signed char field1C2;
};
void ResultScenePollF260::PollInput()
{
    ResultInputServiceF260::BeginFrame();
    ResultInputServiceF260::EndFrame();
    field1BF=0;
    field1C0=0;
    field1C1=0;
    field1C2=0;
    g_ResultInputPrimaryAt00671638.Poll();
    g_ResultInputSecondaryAt00671680.Poll();
    if (g_ResultPrimaryVerticalAt00671668==1 || g_ResultSecondaryVerticalAt006716B0==1)
        field1C0=1;
    if (g_ResultPrimaryVerticalAt00671668==-1 || g_ResultSecondaryVerticalAt006716B0==-1)
        field1C0=-1;
    if (g_ResultPrimaryHorizontalAt00671664==1 || g_ResultSecondaryHorizontalAt006716AC==1)
        field1BF=1;
    if (g_ResultPrimaryHorizontalAt00671664==-1 || g_ResultSecondaryHorizontalAt006716AC==-1)
        field1BF=-1;
    if (g_ResultPrimaryConfirmAt0067166C==1 || g_ResultSecondaryConfirmAt006716B4==1)
        field1C1=1;
    if (g_ResultPrimaryCancelAt00671670==1 || g_ResultSecondaryCancelAt006716B8==1)
        field1C2=1;
    if (g_ResultInputPrimaryAt00671638.IsHeld(1))
        field1C2=1;
    if (g_ResultInputPrimaryAt00671638.IsHeld(0x1c)) {
        if (g_ResultInputPrimaryAt00671638.IsHeld(0x38) || g_ResultInputPrimaryAt00671638.IsHeld(0xb8))
            ResultInputServiceF260::ToggleWindowMode();
    }
}
