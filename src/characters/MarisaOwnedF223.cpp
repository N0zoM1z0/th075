#include "characters/CharacterObject.hpp"
#include "characters/MarisaFighter.hpp"

typedef char MarisaObjectFactorySizeCheck[(sizeof(MarisaObject) == 0xE8) ? 1 : -1];

void MarisaFighter::CreateOwnedObject(CharacterObject** output)
{
    *output = new MarisaObject(this);
}
