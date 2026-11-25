#include "battle/FighterCameraOffsetF162.hpp"
#include "battle/CameraUpdate4126C0.hpp"

// Ordinary float dereferences preserve the observed memory comparison operand.
// No original expression spelling or complete owner layout is inferred.
#define OPPONENT_Y opponent->y

void Fighter::AdjustCameraOffset(signed char alternate)
{
    signed char direction;
    if (alternate == 0) {
        direction = 1;
    } else {
        direction = -1;
    }

    if (field2CC == 0) {
        g_CameraHorizontalBiasAt006713EC = direction * -50;
        if (y > OPPONENT_Y) {
            g_CameraVerticalBiasAt0067140C = 0;
        } else {
            g_CameraVerticalBiasAt0067140C = -50;
        }
    } else {
        g_CameraHorizontalBiasAt006713EC = direction * 50;
        if (y > OPPONENT_Y) {
            g_CameraVerticalBiasAt0067140C = 0;
        } else {
            g_CameraVerticalBiasAt0067140C = 50;
        }
    }
}

#undef OPPONENT_Y
