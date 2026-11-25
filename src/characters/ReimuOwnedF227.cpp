#include "characters/CharacterObject.hpp"
#include "characters/ReimuFighter.hpp"

typedef char ReimuObjectFactorySizeCheck[(sizeof(ReimuObject) == 0xE8) ? 1 : -1];

void ReimuFighter::CreateOwnedObject(CharacterObject** output)
{
    *output = new ReimuObject(this);
}
