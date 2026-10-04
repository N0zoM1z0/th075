// Retain the complete existing observation and compare a natural empty constructor.
#include "VC7IndexedOwnerPolicies.cpp"
struct OrdinaryEmptyAllocatorObservation {
    OrdinaryEmptyAllocatorObservation() {}
};
void ConstructOrdinaryEmptyAllocatorObservation(OrdinaryEmptyAllocatorObservation* p) {
    new (p) OrdinaryEmptyAllocatorObservation;
}
extern "C" const unsigned long ListConstructionAlternativeLayout[] = {
    sizeof(OrdinaryEmptyAllocatorObservation),
    sizeof(std::allocator<IndexedArchiveEntryObservation>),
    sizeof(IndexedArchiveListObservation)
};
