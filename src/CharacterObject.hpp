#ifndef TH075_CHARACTER_OBJECT_HPP
#define TH075_CHARACTER_OBJECT_HPP
#include "Fighter.hpp"

// Projectile or effect object owned by a fighter. Each character's object
// vtable (5 slots, e.g. Reimu 00659210) shares Actor's slots; slot 1,
// Advance, is that character's object state machine.
class CharacterObject : public Actor {
public:
    unsigned char unknown0A8[0x0C8 - 0x0A8];
    float field0C8;                     // +0x0C8
    float field0CC;                     // +0x0CC
    float field0D0;                     // +0x0D0
    unsigned char unknown0D4[0x0D8 - 0x0D4];
    short field0D8;                     // +0x0D8
    short field0DA;                     // +0x0DA
    short field0DC;                     // +0x0DC
    short field0DE;                     // +0x0DE
    short field0E0;                     // +0x0E0
    unsigned char unknown0E2[0x0E4 - 0x0E2];
    Fighter* owner;                     // +0x0E4 fighter that spawned the object
};

typedef char CharacterObjectLayoutCheck[(
    offsetof(CharacterObject, field0C8) == 0x0C8 &&
    offsetof(CharacterObject, owner) == 0x0E4 &&
    sizeof(CharacterObject) == 0x0E8) ? 1 : -1];

#endif
