// Complete compact observation owners, independent of private game layouts.
struct ReverseCycleObservation {
    int counter;
    void Advance();
};
void ReverseCycleObservation::Advance() {
    --counter;
    if (counter < 0) counter = 3840;
}
struct ReverseCopyObservation { int counter; };
ReverseCopyObservation CopyReverseCounter(const ReverseCopyObservation& source) { return source; }
extern const unsigned long BackgroundReverseCycleLayout[] = {
    sizeof(ReverseCycleObservation), sizeof(ReverseCopyObservation), sizeof(int)
};
