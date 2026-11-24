#include "CharacterObject.hpp"
#include "MeilingFighter.hpp"
#include "SuikaFighter.hpp"
#include "YukariFighter.hpp"
#include "YuyukoFighter.hpp"
#include "RemiliaFighter.hpp"
#include "PatchouliFighter.hpp"
#include "SakuyaFighter.hpp"

typedef char SakuyaObjectFactorySizeCheck[(sizeof(SakuyaObject) == 0xE8) ? 1 : -1];

void SakuyaFighter::CreateOwnedObject(CharacterObject** out)
{
    *out = new SakuyaObject(this);
}

typedef char PatchouliObjectFactorySizeCheck[(sizeof(PatchouliObject) == 0xE8) ? 1 : -1];

void PatchouliFighter::CreateOwnedObject(CharacterObject** out)
{
    *out = new PatchouliObject(this);
}

typedef char RemiliaObjectFactorySizeCheck[(sizeof(RemiliaObject) == 0xE8) ? 1 : -1];

void RemiliaFighter::CreateOwnedObject(CharacterObject** out)
{
    *out = new RemiliaObject(this);
}

typedef char YuyukoObjectFactorySizeCheck[(sizeof(YuyukoObject) == 0xE8) ? 1 : -1];

void YuyukoFighter::CreateOwnedObject(CharacterObject** out)
{
    *out = new YuyukoObject(this);
}

typedef char YukariObjectFactorySizeCheck[(sizeof(YukariObject) == 0xE8) ? 1 : -1];

void YukariFighter::CreateOwnedObject(CharacterObject** out)
{
    *out = new YukariObject(this);
}

typedef char SuikaObjectFactorySizeCheck[(sizeof(SuikaObject) == 0xE8) ? 1 : -1];

void SuikaFighter::CreateOwnedObject(CharacterObject** out)
{
    *out = new SuikaObject(this);
}

typedef char MeilingObjectFactorySizeCheck[(sizeof(MeilingObject) == 0xE8) ? 1 : -1];

void MeilingFighter::CreateOwnedObject(CharacterObject** out)
{
    *out = new MeilingObject(this);
}
