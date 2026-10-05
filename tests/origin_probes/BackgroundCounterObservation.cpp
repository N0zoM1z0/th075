// Complete generic controls; neither class declares a private game layout.
class CounterObservation {
public:
    virtual void Advance();
    unsigned counter;
};
void CounterObservation::Advance() { ++counter; }

class ReferenceCounterObservation {
public:
    virtual void IncrementReference();
    unsigned counter;
};
void ReferenceCounterObservation::IncrementReference() { ++counter; }

void InvokeCounter(CounterObservation* object) { object->Advance(); }
extern const unsigned long BackgroundCounterLayout[] = {
    sizeof(CounterObservation), sizeof(ReferenceCounterObservation), sizeof(unsigned)
};
