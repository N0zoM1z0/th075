// Natural representation alternatives; no original game type or owner is declared.
extern unsigned ObservedSharedWord;
extern float ObservedSharedFloat;
struct SharedValueObservation {
    void SetWord(unsigned value);
    void SetFloat(float value);
};
void SharedValueObservation::SetWord(unsigned value) { ObservedSharedWord = value; }
void SharedValueObservation::SetFloat(float value) { ObservedSharedFloat = value; }
struct CopyObservation { unsigned value; };
CopyObservation CopyObservedValue(const CopyObservation& source) { return source; }
extern const unsigned long SharedValueLayout[] = {
    sizeof(SharedValueObservation), sizeof(CopyObservation), sizeof(float)
};
