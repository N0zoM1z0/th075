#include "ResultScene.hpp"
// Borrowed controller entries and observed 32-bit button-state globals.
// These pointer-only receiver declarations do not instantiate full owners.
class PollInputDeviceF245 {
public:
    void Update();
    unsigned char IsKeyDown(int key);
};
extern PollInputDeviceF245 g_ResultInputAt00671638;
extern PollInputDeviceF245 g_ResultInputAltAt00671680;
extern int g_ResultAcceptPrimaryAt0067166C;
extern int g_ResultAcceptSecondAt006716B4;
extern int g_ResultCancelPrimaryAt00671670;
extern int g_ResultCancelSecondAt006716B8;
extern int g_ResultChoicePrimaryAt00671674;
extern int g_ResultChoiceSecondAt006716BC;
extern int g_ResultSkipPrimaryAt00671678;
extern int g_ResultSkipSecondAt006716C0;
namespace InputProcessF245 {
    void First();
    void Second();
    void OpenSpecialMenu();
}
void ResultScene::PollInput()
{
    InputProcessF245::First();
    InputProcessF245::Second();
    field00C=0;
    field00D=0;
    g_ResultInputAt00671638.Update();
    g_ResultInputAltAt00671680.Update();
    if (g_ResultAcceptPrimaryAt0067166C==1 || g_ResultAcceptSecondAt006716B4==1)
        field00C=1;
    if (g_ResultCancelPrimaryAt00671670==1 || g_ResultCancelSecondAt006716B8==1)
        field00C=1;
    if (g_ResultChoicePrimaryAt00671674==1 || g_ResultChoiceSecondAt006716BC==1)
        field00C=1;
    if (g_ResultSkipPrimaryAt00671678==1 || g_ResultSkipSecondAt006716C0==1)
        field00C=1;
    if (g_ResultInputAt00671638.IsKeyDown(0x1c)) {
        if (g_ResultInputAt00671638.IsKeyDown(0x38) ||
            g_ResultInputAt00671638.IsKeyDown(0xb8))
            InputProcessF245::OpenSpecialMenu();
    }
}
