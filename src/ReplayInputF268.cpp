#include "SelectionInput4388D0.hpp"
#include "GraphicsDevice.hpp"
#include "InputJoystick.hpp"
#include <windows.h>

// The complete replay-scene and shared input-frame private layouts remain
// unproven; this caller uses only target-observed physical state fields.
class ReplayInputPollF268 {
public:
    void PollInput();
public:
    // Observed fields; meanings not yet known.
    unsigned char unknown000[0x04D - 0x000];
    signed char field04D;
    signed char field04E;
    signed char field04F;
    signed char field050;
};
void ReplayInputPollF268::PollInput()
{
    Input::PollKeyboard();
    Input::PollJoysticks();
    field04D=0;
    field04E=0;
    field04F=0;
    field050=0;
    g_InputMappings[0].UpdateHeldCounts();
    g_InputMappings[1].UpdateHeldCounts();
    if (g_InputMappings[0].held.counts[1]==1 || g_InputMappings[1].held.counts[1]==1)
        field04E=1;
    if (g_InputMappings[0].held.counts[1]==-1 || g_InputMappings[1].held.counts[1]==-1)
        field04E=-1;
    if (g_InputMappings[0].held.counts[0]==1 || g_InputMappings[1].held.counts[0]==1)
        field04D=1;
    if (g_InputMappings[0].held.counts[0]==-1 || g_InputMappings[1].held.counts[0]==-1)
        field04D=-1;
    if (g_InputMappings[0].held.counts[2]==1 || g_InputMappings[1].held.counts[2]==1)
        field04F=1;
    if (g_InputMappings[0].held.counts[3]==1 || g_InputMappings[1].held.counts[3]==1)
        field050=1;
    if (g_InputMappings[0].IsKeyDown(1))
        field050=1;
    if (g_InputMappings[0].IsKeyDown(0x1c)) {
        if (g_InputMappings[0].IsKeyDown(0x38) || g_InputMappings[0].IsKeyDown(0xb8))
            Graphics::ToggleWindowMode();
    }
}
