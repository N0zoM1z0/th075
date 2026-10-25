#include "FighterCameraOffsetF162.hpp"
#include "CameraUpdate4126C0.hpp"

#define FIELD(type, offset) (*reinterpret_cast<type*>(reinterpret_cast<unsigned char*>(this) + (offset)))
// Ordinary float dereferences preserve the observed memory comparison operand.
// No original expression spelling or complete owner layout is inferred.
#define FLOAT(offset) *reinterpret_cast<float*>(reinterpret_cast<unsigned char*>(this) + (offset))
#define OPPONENT_Y *reinterpret_cast<float*>(reinterpret_cast<unsigned char*>(FIELD(void*, 0x2E8)) + 0x48)

void FighterCameraOffsetF162::AdjustCameraOffset(signed char alternate)
{
    signed char direction;
    if (alternate == 0) {
        direction = 1;
    } else {
        direction = -1;
    }

    if (FIELD(signed char, 0x2CC) == 0) {
        g_CameraHorizontalBiasAt006713EC = direction * -50;
        if (FLOAT(0x48) > OPPONENT_Y) {
            g_CameraVerticalBiasAt0067140C = 0;
        } else {
            g_CameraVerticalBiasAt0067140C = -50;
        }
    } else {
        g_CameraHorizontalBiasAt006713EC = direction * 50;
        if (FLOAT(0x48) > OPPONENT_Y) {
            g_CameraVerticalBiasAt0067140C = 0;
        } else {
            g_CameraVerticalBiasAt0067140C = 50;
        }
    }
}

#undef OPPONENT_Y
#undef FLOAT
#undef FIELD
