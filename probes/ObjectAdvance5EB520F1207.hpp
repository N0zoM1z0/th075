#pragma once

// Pointer-only views of observed receiver ABIs; neither is a complete layout.
class OwnerActor5EB520Draft {
public:
    void SpawnEffect(short, float, float, signed char, signed char);
};

class ObjectActor5EB520Draft {
public:
    void AdvanceAction();
    short AdvanceNestedFrame();
    void ResetSecondaryCounters(short);
    void SetPolarVelocity(float, float);
    void EnableTransform(float, float, float);
    int RecordedRange(int, int);
    void ClearField74();
    void PlaySharedSound(short);
};

float __cdecl AngleAt00483300(float, float);
