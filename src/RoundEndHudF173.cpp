#include "RoundEndHudF173.hpp"
#include "CameraUpdate4126C0.hpp"

#define FIELD(type, offset) (*reinterpret_cast<type*>(reinterpret_cast<unsigned char*>(this) + (offset)))
#define FIRST(type, offset) (*reinterpret_cast<type*>(FIELD(unsigned char*, 0x44) + (offset)))
#define SECOND(type, offset) (*reinterpret_cast<type*>(FIELD(unsigned char*, 0x48) + (offset)))
#define MODE_VALUES reinterpret_cast<int (*)[15]>(reinterpret_cast<unsigned char*>(this) + 0x16710)

void RoundEndF173::EnterRoundEnd()
{
    if (FIRST(short, 0x324) <= 0 || SECOND(short, 0x324) <= 0) {
        FIRST(short, 0x3A0) = 0;
        SECOND(short, 0x3A0) = 0;
        FIRST(unsigned char, 0x39C) = 0;
        SECOND(unsigned char, 0x39C) = 0;
        FIELD(short, 0x1A) = 60;
        if (FIRST(short, 0x324) <= 0) {
            if (SECOND(short, 0x324) <= 0) {
                FIRST(signed char, 0x39D) = 1;
                SECOND(signed char, 0x39D) = 1;
                FIELD(unsigned char, 0x18) = 2;
                FIRST(unsigned char, 0x3CF) = 0;
                SECOND(unsigned char, 0x3CF) = 0;
                FIRST(unsigned char, 0x3CE) = 1;
                SECOND(unsigned char, 0x3CE) = 1;
                FIELD(int, 0xC) = 300;
            } else {
                FIRST(signed char, 0x39D)--;
                FIRST(unsigned char, 0x3CF) = 0;
                FIRST(unsigned char, 0x3CE) = 1;
                SECOND(unsigned char, 0x3CE) = 0;
                FIELD(short, 0x1A) = 60;
                if (FIRST(signed char, 0x39D) != 0) {
                    FIRST(short, 0x326) = 10000;
                    FIRST(short, 0x324) = 10000;
                    FIELD(unsigned char, 0x18) = 2;
                    FIELD(int, 0xC) = 300;
                } else {
                    FIELD(unsigned char, 0x5D) = 1;
                    FIELD(unsigned char, 0x18) = 3;
                    FIELD(int, 0xC) = 180;
                }
            }
        } else if (SECOND(short, 0x324) <= 0) {
            SECOND(signed char, 0x39D)--;
            SECOND(unsigned char, 0x3CF) = 0;
            FIRST(unsigned char, 0x3CE) = 0;
            SECOND(unsigned char, 0x3CE) = 1;
            if (SECOND(signed char, 0x39D) != 0) {
                SECOND(short, 0x326) = 10000;
                SECOND(short, 0x324) = 10000;
                FIELD(unsigned char, 0x18) = 2;
                FIELD(int, 0xC) = 300;
            } else {
                FIELD(unsigned char, 0x5D) = 0;
                FIELD(unsigned char, 0x18) = 3;
                FIELD(int, 0xC) = 180;
            }
        }
    }
}

void ModeCounterF173::IncrementModeCounter(signed char category, signed char key)
{
    MODE_VALUES[category][key]++;
}

ComboCounterF173::ComboCounterF173(void* texture, signed char side)
{
    FIELD(void*, 0) = texture;
    FIELD(signed char, 0xB) = side;
    FIELD(unsigned char, 0xA) = 0;
    FIELD(short, 4) = 0;
    FIELD(float, 0x10) = -200.0f;
}

void ComboCounterF173::UpdateComboCounter(short count, short value, short extra)
{
    if (count > FIELD(short, 4) || count == 1) {
        FIELD(unsigned char, 0xA) = 255;
        FIELD(short, 4) = count;
        FIELD(short, 6) = value;
        FIELD(short, 8) = extra;
        FIELD(short, 0xC) = 60;
        if (FIELD(short, 4) == 2) {
            FIELD(short, 0xE) = 90;
            FIELD(float, 0x10) = -CameraSineAt0040D940(
                float(FIELD(short, 0xE)) * 0.01745328866f) * 200.0f;
        }
    }
}

#undef MODE_VALUES
#undef SECOND
#undef FIRST
#undef FIELD
