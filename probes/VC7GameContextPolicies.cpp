// Complete synthetic observations; no original game owner is instantiated.
#include <list>
#include <deque>

struct ListPolicyObservation {
    unsigned identifier;
    std::list<unsigned> entries;
    unsigned char mode;
    unsigned short flags;
    explicit ListPolicyObservation(unsigned value);
    void clear();
};
ListPolicyObservation::ListPolicyObservation(unsigned value) {
    identifier = value;
    flags = 15;
    mode = 5;
    clear();
}
void ListPolicyObservation::clear() { entries.clear(); }
struct ImplicitListObservation {
    unsigned identifier;
    std::list<unsigned> entries;
    unsigned char mode;
    unsigned short flags;
};
void ObserveLists(unsigned value) { ListPolicyObservation explicit_policy(value); ImplicitListObservation implicit_policy; }

struct ArrayPolicyObservation {
    unsigned identifier;
    std::deque<float> entries[4];
    ArrayPolicyObservation();
};
ArrayPolicyObservation::ArrayPolicyObservation() {
    for (int index = 0; index < 4; ++index)
        entries[index].clear();
}
struct ImplicitArrayObservation { unsigned identifier; std::deque<float> entries[4]; };
void ObserveArrays() { ArrayPolicyObservation explicit_policy; ImplicitArrayObservation implicit_policy; }

struct PointerPolicyObservation {
    std::deque<unsigned*> first;
    std::deque<unsigned*> second;
    void clearOwned();
};
void PointerPolicyObservation::clearOwned() {
    unsigned index;
    for (index = 0; index < first.size(); ++index)
        delete first.at(index);
    first.clear();
    for (index = 0; index < second.size(); ++index)
        delete second.at(index);
    second.clear();
}

// Full implicit-construction controls carry no original-owner size claim.
struct VirtualBaseObservation {
    VirtualBaseObservation();
    virtual void method();
};
struct ImplicitVirtualObservation : VirtualBaseObservation {};
void ObserveVirtual() { ImplicitVirtualObservation value; }

extern "C" const unsigned long GameContextLayout[] = {
    sizeof(ListPolicyObservation), sizeof(ImplicitListObservation),
    sizeof(ArrayPolicyObservation), sizeof(ImplicitArrayObservation),
    sizeof(PointerPolicyObservation), sizeof(VirtualBaseObservation),
    sizeof(ImplicitVirtualObservation), sizeof(std::list<unsigned>), sizeof(std::deque<float>)
};
