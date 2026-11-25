#include "characters/CharacterObject.hpp"
#include "characters/YoumuFighter.hpp"

typedef char YoumuObjectFactorySizeCheck[(sizeof(YoumuObject) == 0xE8) ? 1 : -1];

void YoumuFighter::CreateOwnedObject(CharacterObject** output)
{
    *output = new YoumuObject(this);
}
