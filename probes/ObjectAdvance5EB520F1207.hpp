#pragma once
#include "CharacterObject.hpp"
#include "MeilingFighter.hpp"

// Pointer-only views of observed receiver ABIs; neither is a complete layout.
class OwnerActor5EB520Draft {
public:
    void SpawnEffect(short, float, float, signed char, signed char);
};

class ObjectActor5EB520Draft : public CharacterObject {
public:
    // Original vtable 0065A04C, stored by constructor 005EB490:
    // slot 0 is 0045B880, slot 1 is 005EB520. This is a borrowed
    // virtual prefix, not a complete owner; never instantiate or embed it.
    void BindAnimation();
    void Advance();
    int RecordedRange(int, int);
    void PlaySharedSound(short);
};

float __cdecl AngleAt00483300(float, float);
