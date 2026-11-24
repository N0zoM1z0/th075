#include "CharacterAuxAction.hpp"
#include "Fighter.hpp"

int CharacterAuxObject::ChooseIntegerRange(int minimum, int maximum)
{
    return (maximum - minimum) * rand() / 32768 + minimum;
}

int Fighter::ChooseIntegerRange(int minimum, int maximum)
{
    return (maximum - minimum) * rand() / 32768 + minimum;
}
