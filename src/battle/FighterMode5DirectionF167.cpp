#include "battle/Fighter.hpp"


void Fighter::ApplyMode5Direction()
{
    switch (field530) {
    case 0:
        inputY = 0;
        break;
    case 1:
        inputY = 1;
        break;
    case 2:
        inputY = -1;
        break;
    case 3:
        ChooseAction();
        return;
    }
    if (field531 > 0) {
        if (x < 620.0f)
            inputX = 1;
        if (x > 660.0f)
            inputX = -1;
    } else {
        inputX = 0;
    }
}
