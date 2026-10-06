// Complete generic archive observations; no original private entry is recovered.
#include "VC7ArchiveListPolicies.cpp"
void ObserveArchiveIteratorOperations(ArchiveListObservation& entries) {
    ArchiveListObservation::iterator current = entries.begin();
    ArchiveListObservation::iterator last = entries.end();
    for (; current != last; current++) {
        current->bytes[0] = 1;
    }
}

// Whole ordinary spellings preserve source-family ambiguity of short bodies.
struct OrdinaryArchiveArrowObservation {
    void* node;
    ArchiveValueObservation& operator*() const;
    ArchiveValueObservation* operator->() const;
};
ArchiveValueObservation* OrdinaryArchiveArrowObservation::operator->() const {
    return &**this;
}
struct OrdinaryArchiveIteratorObservation {
    void* node;
    OrdinaryArchiveIteratorObservation& operator++();
    OrdinaryArchiveIteratorObservation operator++(int);
};
OrdinaryArchiveIteratorObservation OrdinaryArchiveIteratorObservation::operator++(int) {
    OrdinaryArchiveIteratorObservation previous = *this;
    ++*this;
    return previous;
}
extern const unsigned long ArchiveIteratorObservationSizes[] = {
    sizeof(ArchiveValueObservation),sizeof(ArchiveListObservation::iterator),
    sizeof(ArchiveListObservation::const_iterator),sizeof(OrdinaryArchiveArrowObservation),
    sizeof(OrdinaryArchiveIteratorObservation)
};
