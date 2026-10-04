// Complete source observations for a shared lookup table and a small counter owner.
// The counter observer does not declare an original game owner or its layout.
#include <math.h>
#include <stdlib.h>

extern float MathLookupObservation[3600];

void BuildMathLookupObservation() {
    for (int index = 0; index < 3600; ++index)
        MathLookupObservation[index] = static_cast<float>(
            cos(index / 10.0 * 3.1415926535 / 180.0));
}

float ReadMathLookupObservation(float angle) {
    return MathLookupObservation[abs(static_cast<int>(angle * 10.0f)) % 3600];
}

float ReadPhaseMathLookupObservation(float angle) {
    return MathLookupObservation[abs(static_cast<int>(angle * 10.0f - 900.0f)) % 3600];
}

float ReadRatioMathLookupObservation(float angle) {
    if (ReadMathLookupObservation(angle) == 0.0f)
        return 0.0f;
    float phase;
    phase = ReadPhaseMathLookupObservation(angle);
    return phase / ReadMathLookupObservation(angle);
}

struct MathCounterBankObservation {
    unsigned short values[3];
};

struct MathCounterOwnerObservation {
    signed char bank;
    MathCounterBankObservation banks[2];
    void increment(signed char index) { ++banks[bank].values[index]; }
};

void IncrementMathCounterObservation(MathCounterOwnerObservation* owner, signed char index) {
    owner->increment(index);
}

extern "C" const unsigned long MathTablePolicyLayout[] = {
    sizeof(MathLookupObservation), sizeof(float), sizeof(MathCounterBankObservation),
    sizeof(MathCounterOwnerObservation)
};
