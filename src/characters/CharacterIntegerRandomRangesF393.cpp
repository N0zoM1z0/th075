#include "characters/CharacterAuxAction.hpp"
#include "battle/Fighter.hpp"

int CharacterAuxObject::ChooseIntegerRange(int minimum, int maximum)
{
    return (maximum - minimum) * rand() / 32768 + minimum;
}

int Fighter::ChooseIntegerRange(int minimum, int maximum)
{
    return (maximum - minimum) * rand() / 32768 + minimum;
}
