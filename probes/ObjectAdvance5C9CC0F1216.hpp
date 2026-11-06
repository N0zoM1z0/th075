#pragma once

// Borrowed receiver interfaces only. The exact 005C9C20 constructor installs
// vtable 00659F14 and writes the owner pointer at E4h. These declarations do
// not establish the enclosing object layout; never instantiate or embed them.
class OwnerActor5C9CC0F1216 {
public:
    void SpawnEffect(short, float, float, signed char, signed char);
    void PlaySoundAt00453D40(short);
    void PlaySharedSoundAt00453D60(short);
    void SetCameraShakeAt00453E60(float);
};

class ObjectActor5C9CC0F1216 {
public:
    virtual void BindAnimationAt0045B880();
    virtual void AdvanceAction();
    short AdvanceNestedFrame();
    void ResetPrimaryCounters(short);
    void ResetSecondaryCounters(short);
    void SetPolarVelocity(float, float);
    void EnableTransform(float, float, float);
    int RecordedRange(int, int);
    void ClearField74();
    void PlaySharedSound(short);
    // Native 0045B850 is an empty receiver call with RET 4; the observed
    // callers pass integer constants. Its original typedef is unknown.
    void UnknownAt0045B850(int);
};

float __cdecl AngleAt00483300(float, float);
float __cdecl AbsFloatAt00412D90(float);

// Same one-float/ST0 contract as the existing exact opening call sites.
// The scalar helper's original name and origin remain unproved.
float __cdecl ScalarAt00428D20(float);
