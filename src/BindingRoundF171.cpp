#include "BindingRoundF171.hpp"
#include "Input.hpp"
#include <string.h>

namespace Input { extern unsigned char g_JoystickCount; }

#define FIELD(type, offset) (*reinterpret_cast<type*>(reinterpret_cast<unsigned char*>(this) + (offset)))
#define OTHER(type, offset) (*reinterpret_cast<type*>(FIELD(unsigned char*, 0x2E8) + (offset)))
#define OTHER_ARRAY(type, offset, index) reinterpret_cast<type*>(FIELD(unsigned char*, 0x2E8) + (offset))[index]

void InputBindingsF171::SetBindings(const void* source)
{
    memcpy(reinterpret_cast<unsigned char*>(this) + 4, source, 40);
    if (FIELD(signed char, 4) >= Input::g_JoystickCount) {
        // Original CP932 message: パッドが見つかりません
        Input::ShowError("\x83\x70\x83\x62\x83\x68\x82\xaa\x8c\xa9\x82\xc2\x82\xa9\x82\xe8\x82\xdc\x82\xb9\x82\xf1");
        memset(reinterpret_cast<unsigned char*>(this) + 4, 0, 40);
        FIELD(signed char, 4) = -1;
    }
    memset(reinterpret_cast<unsigned char*>(this) + 0x2C, 0, 28);
}

void FighterBindingRoundF171::SetBindings(const void* source)
{
    reinterpret_cast<InputBindingsF171*>(reinterpret_cast<unsigned char*>(this) + 0x494)
        ->SetBindings(source);
}

void FighterBindingRoundF171::BindOpponent(void* opponent)
{
    FIELD(void*, 0x2E8) = opponent;
}

void FighterBindingRoundF171::RecordRoundFields(
    signed char index, short value, unsigned char first, unsigned char second,
    unsigned char third, unsigned int payloadA, unsigned int payloadB,
    unsigned int payloadC)
{
    if (OTHER(signed char, 0x39D) < index)
        OTHER(signed char, 0x39D) = index;
    if (index == 1) {
        OTHER(short, 0x33E) = value;
        OTHER(unsigned char, 0x32A) = first;
        OTHER(unsigned char, 0x384) = second;
        OTHER(unsigned char, 0x370) = third;
        OTHER(unsigned int, 0x3D0) = payloadA;
        OTHER(unsigned int, 0x400) = payloadB;
        OTHER(unsigned int, 0x430) = payloadC;
    }
    OTHER_ARRAY(short, 0x33E, index) = value;
    OTHER_ARRAY(unsigned char, 0x32A, index) = first;
    OTHER_ARRAY(unsigned char, 0x384, index) = second;
    OTHER_ARRAY(unsigned char, 0x370, index) = third;
    OTHER_ARRAY(unsigned int, 0x3D0, index) = payloadA;
    OTHER_ARRAY(unsigned int, 0x400, index) = payloadB;
    OTHER_ARRAY(unsigned int, 0x430, index) = payloadC;
    OTHER(signed char, 0x39E) = OTHER(signed char, 0x39D);
}

#undef OTHER_ARRAY
#undef OTHER
#undef FIELD
