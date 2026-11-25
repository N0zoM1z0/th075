// Complete observations retain prior source; no original game type is instantiated.
#include "VC7GameContextPolicies.cpp"

struct ListValueObservation { unsigned char bytes[164]; };
struct ListOwnerObservation {
    unsigned identifier;
    std::list<ListValueObservation> entries;
    unsigned char mode;
    unsigned short flags;
    explicit ListOwnerObservation(unsigned value);
    void clear();
};
ListOwnerObservation::ListOwnerObservation(unsigned value) {
    identifier = value;
    flags = 15;
    mode = 5;
    clear();
}
void ListOwnerObservation::clear() { entries.clear(); }
void ObserveListOwner(unsigned value) { ListOwnerObservation owner(value); }

// Ordinary delegation/destruction can share complete SDK-shaped bytes.
struct OrdinaryTidyObservation { void tidy(); ~OrdinaryTidyObservation(); };
OrdinaryTidyObservation::~OrdinaryTidyObservation() { tidy(); }
void ObserveOrdinaryTidy() { OrdinaryTidyObservation value; }
struct ImplicitClearObservation { unsigned identifier; std::list<ListValueObservation> entries; };
void ObserveImplicitClear() { ImplicitClearObservation value; }

extern "C" const unsigned long ListDependencyLayout[] = {
    sizeof(ListValueObservation), sizeof(ListOwnerObservation),
    sizeof(std::list<ListValueObservation>), sizeof(OrdinaryTidyObservation),
    sizeof(ImplicitClearObservation)
};
