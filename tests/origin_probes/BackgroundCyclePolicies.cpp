// Natural ordinary policies and compiler-generated copy alternatives.
// These compact owners do not reconstruct any private TH075 layout.
struct CycleState {
    int counter;
    int frame;
    void AdvanceDegrees();
    void AdvanceLongCycle();
    void AdvanceTextureCycle();
    void AdvancePair();
};
void CycleState::AdvanceDegrees() {
    ++counter;
    if (counter > 360) counter = 0;
}
void CycleState::AdvanceLongCycle() {
    ++counter;
    if (counter > 2500.0) counter = 0;
}
void CycleState::AdvanceTextureCycle() {
    ++counter;
    if (counter >= 15360.0) counter = 0;
}
void CycleState::AdvancePair() {
    ++counter;
    ++frame;
    if (frame > 71) frame = 0;
}
struct CopyState {
    int counter;
    int frame;
};
CopyState* CopyCounterState(CopyState* destination, const CopyState* source) {
    *destination = *source;
    return destination;
}
// Ordinary implicit copy construction is emitted without placement allocation
// or a claim that CopyState matches a game owner.
CopyState ReturnCounterCopy(const CopyState& source) { return source; }
extern const unsigned long CyclePolicyLayout[] = {
    sizeof(CycleState), sizeof(CopyState), sizeof(int), sizeof(double)
};
