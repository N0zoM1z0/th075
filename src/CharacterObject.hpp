#ifndef TH075_CHARACTER_OBJECT_HPP
#define TH075_CHARACTER_OBJECT_HPP
#include "Fighter.hpp"

// Projectile or effect object owned by a fighter. Each character's object
// vtable (5 slots, e.g. Reimu 00659210) shares Actor's slots; slot 1,
// Advance, is that character's object state machine.
class CharacterObject : public Actor {
public:
    CharacterObject();                  // 0045B760; object vtables have no destructor slot
    void ClearFrameInfo();              // 0045B830
    void PlaySharedSound(short sound);    // 0045B860, native sound-bank forwarding
    void NoOpAt0045B850(int unused);    // 0045B850, observed native no-op RET 4
    void Render();                      // slot 2, 0040FC70

    ActionSequenceSlots* sequences;     // +0x0C4 the owner's sequence container (owner + 0x468)
    float field0C8;                     // +0x0C8
    float field0CC;                     // +0x0CC
    float field0D0;                     // +0x0D0
    unsigned char unknown0D4[0x0D8 - 0x0D4];
    short field0D8;                     // +0x0D8
    short field0DA;                     // +0x0DA
    short field0DC;                     // +0x0DC
    short field0DE;                     // +0x0DE
    short field0E0;                     // +0x0E0
    short field0E2;                     // +0x0E2
    Fighter* owner;                     // +0x0E4 fighter that spawned the object
};

// Each character's object class; its constructor takes the owning fighter.
class ReimuObject : public CharacterObject { public: ReimuObject(void* ownerFighter); };
class MarisaObject : public CharacterObject { public: MarisaObject(void* ownerFighter); };
class SakuyaObject : public CharacterObject {
public:
    SakuyaObject(void* ownerFighter);
    virtual void Advance();    // 004CA6E0, nonexact 42,511-byte parent
    void PlaySharedSound(short sound);
};
class AliceObject : public CharacterObject {
public:
    AliceObject(void* ownerFighter);
    virtual void Advance();   // 004EBDA0, whole nonexact research parent

    // Call-shape declarations from the giant research source; actual
    // implementations use the shared Actor and object helper addresses.
    void AdvanceProjectileBehavior(); // 004F4170, original native helper
    void PlaySharedSound(short sound);
};
class PatchouliObject : public CharacterObject {
public:
    PatchouliObject(void* ownerFighter);
    virtual void Advance();  // 0050A580; complete 81,539-byte nonexact parent
    void PlaySharedSound(short sound);
};
class YoumuObject : public CharacterObject {
public:
    YoumuObject(void* ownerFighter);
    virtual void Advance(); // 00536400, complete nonexact object state machine
    void PlaySharedSound(short sound);
};
class RemiliaObject : public CharacterObject {
public:
    RemiliaObject(void* ownerFighter);
    virtual void Advance();        // 0055AC80, nonexact complete research parent
    void PlaySharedSound(short sound);
};
class YuyukoObject : public CharacterObject {
public:
    YuyukoObject(void* ownerFighter);
    virtual void Advance();   // 0057D580; complete nonexact parent
    void PlaySharedSound(short sound);
};
class YukariObject : public CharacterObject {
public:
    YukariObject(void* ownerFighter);
    virtual void Advance();  // original 005A1600; complete, nonexact research parent
    void PlaySharedSound(short sound);
};
class SuikaObject : public CharacterObject {
public:
    SuikaObject(void* ownerFighter);
    virtual void Advance(); // native 005C9CC0, complete nonexact research parent
    void PlaySharedSound(short sound);
};
class MeilingObject : public CharacterObject {
public:
    MeilingObject(void* ownerFighter);
    virtual void Advance();  // 005EB520, whole nonexact research parent
    void PlaySharedSound(short sound);
};

typedef char CharacterObjectLayoutCheck[(
    offsetof(CharacterObject, field0C8) == 0x0C8 &&
    offsetof(CharacterObject, owner) == 0x0E4 &&
    sizeof(CharacterObject) == 0x0E8) ? 1 : -1];

#endif
