// Complete observers retain the accepted list graph; original payload is unknown.
#include "VC7ListPolicyDependencies.cpp"

typedef std::list<ListValueObservation> IteratorList;
void ObserveListIteration(IteratorList& entries, const ListValueObservation& value) {
    if (entries.size()) entries.pop_front();
    entries.push_back(value);
    IteratorList::iterator current = entries.begin();
    IteratorList::iterator last = entries.end();
    for (; current != last; current++) {
        current->bytes[0] = 1;
    }
}
extern "C" const unsigned long ListIteratorLayout[] = {
    sizeof(IteratorList::iterator), sizeof(IteratorList::const_iterator)
};

// Whole ordinary alternatives demonstrate that short shapes do not identify owners.
struct OrdinaryListSizeObservation {
    unsigned identifier;
    void* sentinel;
    unsigned count;
    unsigned size() const;
};
unsigned OrdinaryListSizeObservation::size() const { return count; }
struct OrdinaryListArrowObservation {
    ListValueObservation& operator*() const;
    ListValueObservation* operator->() const;
};
ListValueObservation* OrdinaryListArrowObservation::operator->() const { return &**this; }
struct OrdinaryListIteratorObservation {
    void* node;
    OrdinaryListIteratorObservation& operator++();
    OrdinaryListIteratorObservation operator++(int);
};
OrdinaryListIteratorObservation OrdinaryListIteratorObservation::operator++(int) {
    OrdinaryListIteratorObservation previous = *this;
    ++*this;
    return previous;
}
extern "C" const unsigned long OrdinaryListIteratorLayout[] = {
    sizeof(OrdinaryListSizeObservation), sizeof(OrdinaryListArrowObservation),
    sizeof(OrdinaryListIteratorObservation)
};
