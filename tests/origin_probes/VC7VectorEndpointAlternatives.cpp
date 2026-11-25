// Complete SDK/ordinary observations do not recover original game declarations.
#include <vector>
#include <deque>

struct FirstVectorObservation {
    unsigned char bytes[4];
};
struct SecondVectorObservation {
    unsigned char bytes[4];
};
typedef std::vector<FirstVectorObservation> FirstVector;
typedef std::vector<SecondVectorObservation> SecondVector;

void AssignFirst(FirstVector& values, unsigned count, const FirstVectorObservation& value) {
    values.assign(count, value);
}
void AssignSecond(SecondVector& values, unsigned count, const SecondVectorObservation& value) {
    values.assign(count, value);
}
typedef std::deque<unsigned char> OffsetDeque;
OffsetDeque::iterator SubtractOffset(const OffsetDeque::iterator& position, int offset) {
    return position - offset;
}
OffsetDeque::iterator AddOffset(const OffsetDeque::iterator& position, int offset) {
    return position + offset;
}
struct FirstLifetimeObservation { unsigned char value; ~FirstLifetimeObservation(); };
struct SecondLifetimeObservation { unsigned char value; ~SecondLifetimeObservation(); };
void DestroyFirst(std::allocator<FirstLifetimeObservation>& allocator, FirstLifetimeObservation* value) {
    allocator.destroy(value);
}
void DestroySecond(std::allocator<SecondLifetimeObservation>& allocator, SecondLifetimeObservation* value) {
    allocator.destroy(value);
}

struct OrdinaryEmptyObservation {};
struct OrdinaryConstPointerObservation : OrdinaryEmptyObservation {
    FirstVectorObservation* pointer;
    explicit OrdinaryConstPointerObservation(FirstVectorObservation* value) { pointer = value; }
};
struct OrdinaryMutablePointerObservation : OrdinaryConstPointerObservation {
    explicit OrdinaryMutablePointerObservation(FirstVectorObservation* value)
        : OrdinaryConstPointerObservation(value) {}
};
OrdinaryMutablePointerObservation ObserveOrdinaryPointer(FirstVectorObservation* value) {
    return OrdinaryMutablePointerObservation(value);
}
struct OrdinaryVectorObservation {
    std::allocator<FirstVectorObservation> allocator;
    FirstVectorObservation* first;
    FirstVectorObservation* last;
    FirstVectorObservation* capacity_end;
    FirstVector::iterator begin() { return FirstVector::iterator(first); }
    FirstVector::iterator end() { return FirstVector::iterator(last); }
};
FirstVector::iterator ObserveOrdinaryBegin(OrdinaryVectorObservation& values) { return values.begin(); }
FirstVector::iterator ObserveOrdinaryEnd(OrdinaryVectorObservation& values) { return values.end(); }
void OrdinaryDestroyFirst(FirstLifetimeObservation* value) { value->~FirstLifetimeObservation(); }
void OrdinaryDestroySecond(SecondLifetimeObservation* value) { value->~SecondLifetimeObservation(); }

extern "C" const unsigned long VectorEndpointLayout[] = {
    sizeof(FirstVectorObservation), sizeof(SecondVectorObservation), sizeof(FirstVector), sizeof(SecondVector),
    sizeof(FirstVector::iterator), sizeof(SecondVector::iterator), sizeof(FirstVector::const_iterator),
    sizeof(SecondVector::const_iterator), sizeof(std::allocator<FirstVectorObservation>),
    sizeof(std::allocator<SecondVectorObservation>), sizeof(OrdinaryConstPointerObservation),
    sizeof(OrdinaryMutablePointerObservation), sizeof(OrdinaryVectorObservation), sizeof(OrdinaryEmptyObservation),
    sizeof(OffsetDeque::iterator), sizeof(FirstLifetimeObservation), sizeof(SecondLifetimeObservation)
};
