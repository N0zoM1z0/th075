#include "BindingRoundF171.hpp"
#include "Input.hpp"
#include <string.h>

namespace Input { extern unsigned char g_JoystickCount; }


void InputBindingsF171::SetBindings(const void* source)
{
    memcpy(&device, source, 40);
    if (device >= Input::g_JoystickCount) {
        // Original CP932 message: パッドが見つかりません
        Input::ShowError("\x83\x70\x83\x62\x83\x68\x82\xaa\x8c\xa9\x82\xc2\x82\xa9\x82\xe8\x82\xdc\x82\xb9\x82\xf1");
        memset(&device, 0, 40);
        device = -1;
    }
    memset(&state, 0, 28);
}

void Fighter::SetBindings(const void* source)
{
    inputBindings.SetBindings(source);
}

void Fighter::BindOpponent(void* other)
{
    opponent = static_cast<Fighter*>(other);
}

void Fighter::RecordRoundFields(
    signed char index, short value, unsigned char first, unsigned char second,
    unsigned char third, unsigned int payloadA, unsigned int payloadB,
    unsigned int payloadC)
{
    if (opponent->field39D < index)
        opponent->field39D = index;
    if (index == 1) {
        opponent->healthLimits[0] = value;
        opponent->field32A[0] = first;
        opponent->field384[0] = second;
        opponent->field370[0] = static_cast<signed char>(third);
        opponent->field3D0[0] = payloadA;
        opponent->field400[0] = payloadB;
        opponent->field430[0] = payloadC;
    }
    opponent->healthLimits[index] = value;
    opponent->field32A[index] = first;
    opponent->field384[index] = second;
    opponent->field370[index] = third;
    opponent->field3D0[index] = payloadA;
    opponent->field400[index] = payloadB;
    opponent->field430[index] = payloadC;
    opponent->field39E = opponent->field39D;
}
