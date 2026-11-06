#pragma once

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

class OwnerActor536400F1211 {
public:
    void SpawnEffect(short, float, float, signed char, signed char);
    void UpdateGaugeAt0046D000(int);
};

// Native vtable 006599D4, installed by the exact 00536360 constructor.
// Only its first two virtual slots are exposed. All receiver interfaces here
// are incomplete: never instantiate or embed them.
class ObjectActor536400F1211 {
public:
    virtual void BindAnimationAt0045B880();
    virtual void AdvanceAction();
    short AdvanceNestedFrame();
    void ResetPrimaryCounters(short);
    void ResetSecondaryCounters(short);
    void ResetAnimationCountersAt0040FB00(short, short, short);
    void SetPolarVelocity(float, float);
    void EnableTransform(float, float, float);
    int RecordedRange(int, int);
    void ClearField74();
    void PlaySharedSound(short);
};

float __cdecl AngleAt00483300(float, float);
