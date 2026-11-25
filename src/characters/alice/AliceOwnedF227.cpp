#include "characters/CharacterObject.hpp"
#include "characters/alice/AliceFighter.hpp"

typedef char AliceObjectFactorySizeCheck[(sizeof(AliceObject) == 0xE8) ? 1 : -1];

void AliceFighter::CreateOwnedObject(CharacterObject** output)
{
    *output = new AliceObject(this);
}
