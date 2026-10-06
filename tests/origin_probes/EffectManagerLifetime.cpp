// Complete generic observation; no original effect-manager class is recovered.
#include "VC7GameContextPolicies.cpp"
struct EffectLifetimeObservation {
    unsigned fighter;
    std::deque<float> entries[4];
    void ClearOwned();
    ~EffectLifetimeObservation();
};
EffectLifetimeObservation::~EffectLifetimeObservation() { ClearOwned(); }
void DestroyEffectLifetime(EffectLifetimeObservation* value) {
    value->~EffectLifetimeObservation();
}
struct ImplicitEffectLifetimeObservation {
    unsigned fighter;
    std::deque<float> entries[4];
};
void DestroyImplicitEffectLifetime(ImplicitEffectLifetimeObservation* value) {
    value->~ImplicitEffectLifetimeObservation();
}
struct EmptyExplicitEffectLifetimeObservation {
    unsigned fighter;
    std::deque<float> entries[4];
    ~EmptyExplicitEffectLifetimeObservation();
};
EmptyExplicitEffectLifetimeObservation::~EmptyExplicitEffectLifetimeObservation() {}
extern const unsigned long EffectLifetimeObservationSizes[] = {
    sizeof(EffectLifetimeObservation),sizeof(ImplicitEffectLifetimeObservation),
    sizeof(EmptyExplicitEffectLifetimeObservation),sizeof(std::deque<float>)
};
