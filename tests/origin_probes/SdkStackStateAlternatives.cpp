// Complete ordinary observation owners; no private SDK class is declared.
#include <new>
#include <stddef.h>

struct PlainStackState {
    unsigned long *values;
    unsigned long count;
    unsigned long capacity;
    long error;
};

struct ExplicitStackObservation {
    PlainStackState state;
    ExplicitStackObservation();
    ~ExplicitStackObservation();
    long ReadAndResetError();
};

ExplicitStackObservation::ExplicitStackObservation()
{
    state.values = 0;
    state.count = 0;
    state.capacity = 0;
    state.error = 0;
}

ExplicitStackObservation::~ExplicitStackObservation()
{
    if (state.values) ::operator delete(state.values);
}

long ExplicitStackObservation::ReadAndResetError()
{
    long result = state.error;
    state.error = 0;
    return result;
}

struct OwnedStackState {
    unsigned long *values;
    unsigned long count;
    unsigned long capacity;
    long error;
    OwnedStackState() : values(0), count(0), capacity(0), error(0) {}
    ~OwnedStackState() { if (values) ::operator delete(values); }
};

struct ImplicitStackObservation {
    OwnedStackState state;
    long ReadAndResetError();
};

long ImplicitStackObservation::ReadAndResetError()
{
    long result = state.error;
    state.error = 0;
    return result;
}

void ConstructImplicitStack(void *storage)
{
    new (storage) ImplicitStackObservation;
}

void DestroyImplicitStack(ImplicitStackObservation *owner)
{
    owner->~ImplicitStackObservation();
}

extern const unsigned long StackObservationLayout[] = {
    sizeof(unsigned long *), sizeof(long), sizeof(PlainStackState),
    sizeof(ExplicitStackObservation), sizeof(OwnedStackState),
    sizeof(ImplicitStackObservation), offsetof(PlainStackState, error),
    offsetof(OwnedStackState, error)
};
