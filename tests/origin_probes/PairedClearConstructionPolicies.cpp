// Complete generic policy fixtures; original private owner declarations are unknown.
#include "VectorInsertionCarriers.cpp"
#include <deque>

struct ClearValue8 {
    unsigned long values[2];
    // Only the complete external destruction protocol is observed.
    ~ClearValue8();
};
struct ExplicitDequeClearOwner {
    std::deque<ClearValue8> values;
    ExplicitDequeClearOwner() { values.clear(); }
};
struct ImplicitDequeOwner { std::deque<ClearValue8> values; };
struct ExplicitVectorClearOwner {
    std::vector<InsertOwned16> values;
    ExplicitVectorClearOwner() { values.clear(); }
};
struct ImplicitVectorOwner { std::vector<InsertOwned16> values; };

void ObserveExplicitDequeClear(ExplicitDequeClearOwner* value) {
    new (value) ExplicitDequeClearOwner;
}
void ObserveImplicitDeque(ImplicitDequeOwner* value) {
    new (value) ImplicitDequeOwner;
}
void ObserveExplicitVectorClear(ExplicitVectorClearOwner* value) {
    new (value) ExplicitVectorClearOwner;
}
void ObserveImplicitVector(ImplicitVectorOwner* value) {
    new (value) ImplicitVectorOwner;
}

extern const unsigned long PairedClearConstructionLayout[] = {
    sizeof(ClearValue8), sizeof(ExplicitDequeClearOwner),
    sizeof(ImplicitDequeOwner), sizeof(ExplicitVectorClearOwner),
    sizeof(ImplicitVectorOwner)
};
