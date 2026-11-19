#pragma once
#include "CharacterObject.hpp"
#include "YoumuFighter.hpp"

// Borrowed 16-byte history payload, independently consumed at 005365FF.
// The coordinates retain their observed DWORD bit transport. Natural member
// alignment accounts for the byte before counterAt0E; no filler is declared.
// Never use this view to instantiate or size the enclosing list or owner.
struct ObjectHistoryEntryF1211 {
    short actionAt00;
    short stageAt02;
    unsigned int xBitsAt04;
    unsigned int yBitsAt08;
    signed char facingAt0C;
    short counterAt0E;
};

class ObjectHistoryListF1211 {
public:
    ObjectHistoryEntryF1211& FrontAt00540220();
};

// The owner gauge timer is the inherited Fighter method at 0046D000.

float __cdecl AngleAt00483300(float, float);

float __cdecl AbsFloatAt00412D90(float);
