#include "FighterMode5DirectionF167.hpp"


void FighterMode5DirectionF167::ApplyMode5Direction()
{
    switch (field530) {
    case 0:
        field4E0 = 0;
        break;
    case 1:
        field4E0 = 1;
        break;
    case 2:
        field4E0 = -1;
        break;
    case 3:
        OnDirectionPolicy();
        return;
    }
    if (field531 > 0) {
        if (field044 < 620.0f)
            field4DC = 1;
        if (field044 > 660.0f)
            field4DC = -1;
    } else {
        field4DC = 0;
    }
}
