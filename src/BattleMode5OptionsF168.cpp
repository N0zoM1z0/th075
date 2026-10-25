#include "BattleMode5OptionsF168.hpp"
#include "GameLeafHelpers.hpp"
#include "SelectionInput4388D0.hpp"

// Used caller-cleaned dword argument/EAX contract only. R163 retains unknown
// ownership and original int/long overload spelling for this complete wrapper.
int __cdecl Unknown438A60(int value);

#define FIELD(type, offset) (*reinterpret_cast<type*>(reinterpret_cast<unsigned char*>(this) + (offset)))
#define FIRST(type, offset) (*reinterpret_cast<type*>(FIELD(unsigned char*, 0x44) + (offset)))
#define SECOND(type, offset) (*reinterpret_cast<type*>(FIELD(unsigned char*, 0x48) + (offset)))

void BattleMode5OptionsF168::HandleMode5Options()
{
    if (FIELD(unsigned char, 0xA0) == 0)
        return;

    if (Unknown438A60(g_HeldInputAt00671664.counts[0]) == 1) {
        g_SoundBank->Play(39);
        signed char horizontal = *reinterpret_cast<signed char*>(&g_HeldInputAt00671664);
        switch (FIELD(signed char, 0x118)) {
        case 0:
            SECOND(signed char, 0x52C) = (SECOND(signed char, 0x52C) + 6 + horizontal) % 6;
            break;
        case 1:
            SECOND(signed char, 0x52D) = (SECOND(signed char, 0x52D) + 10 + horizontal) % 10;
            break;
        case 2:
            SECOND(signed char, 0x52F) = (SECOND(signed char, 0x52F) + 4 + horizontal) % 4;
            break;
        case 3:
            SECOND(signed char, 0x52E) = (SECOND(signed char, 0x52E) + 2 + horizontal) % 2;
            break;
        case 4:
            SECOND(signed char, 0x530) = (SECOND(signed char, 0x530) + 4 + horizontal) % 4;
            break;
        case 5:
            SECOND(signed char, 0x531) = (SECOND(signed char, 0x531) + 2 + horizontal) % 2;
            break;
        }
    }

    if (g_HeldInputAt00671664.counts[2] == 1) {
        switch (FIELD(signed char, 0x118)) {
        case 6:
            FIRST(short, 0x3A0) = 1;
            g_SoundBank->Play(45);
            break;
        case 7:
            FIELD(unsigned char, 0xA0) = 0;
            g_SoundBank->Play(45);
            break;
        case 8:
            FIELD(unsigned char, 0xA0) = 0;
            g_SoundBank->Play(45);
            FIELD(unsigned char, 0x18) = 6;
            break;
        }
    }
    if (g_HeldInputAt00671664.counts[3] == 1)
        FIELD(unsigned char, 0xA0) = 0;
    if (g_HeldInputAt00671664.counts[1] == 1 || g_HeldInputAt006716AC.counts[1] == 1) {
        g_SoundBank->Play(39);
        FIELD(signed char, 0x118) = (FIELD(signed char, 0x118) + 1) % 9;
    }
    if (g_HeldInputAt00671664.counts[1] == -1 || g_HeldInputAt006716AC.counts[1] == -1) {
        g_SoundBank->Play(39);
        FIELD(signed char, 0x118) = (FIELD(signed char, 0x118) + 8) % 9;
    }
    FIRST(signed char, 0x39D) = 2 - SECOND(signed char, 0x52C) / 3;
    FIRST(short, 0x398) = SECOND(signed char, 0x52C) % 3;
    FIRST(short, 0x39A) = SECOND(signed char, 0x52C) % 3;
}

#undef SECOND
#undef FIRST
#undef FIELD
