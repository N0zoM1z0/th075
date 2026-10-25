#include "FighterMode5DirectionF167.hpp"

#define FIELD(type, offset) (*reinterpret_cast<type*>(reinterpret_cast<unsigned char*>(this) + (offset)))
#define FLOAT(offset) *reinterpret_cast<float*>(reinterpret_cast<unsigned char*>(this) + (offset))

void FighterMode5DirectionF167::ApplyMode5Direction()
{
    switch (FIELD(signed char, 0x530)) {
    case 0:
        FIELD(int, 0x4E0) = 0;
        break;
    case 1:
        FIELD(int, 0x4E0) = 1;
        break;
    case 2:
        FIELD(int, 0x4E0) = -1;
        break;
    case 3:
        OnDirectionPolicy();
        return;
    }
    if (FIELD(signed char, 0x531) > 0) {
        if (FLOAT(0x44) < 620.0f)
            FIELD(int, 0x4DC) = 1;
        if (FLOAT(0x44) > 660.0f)
            FIELD(int, 0x4DC) = -1;
    } else {
        FIELD(int, 0x4DC) = 0;
    }
}

#undef FLOAT
#undef FIELD
