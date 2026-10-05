// Complete generic source controls only; no original private declarations.
#include "NestedVectorInsertionCarriers.cpp"
#include <cstring>

struct NeighborAllocation36 { unsigned long values[9]; };
struct NeighborAllocationOwner16 {
    unsigned long identifier, length;
    NeighborAllocation36* allocation;
    unsigned char flags;
    void resetAllocation() {
        flags = 0;
        if (!allocation) allocation = new NeighborAllocation36;
        std::memset(allocation, 0, sizeof(*allocation));
    }
};

struct NeighborRecord20 {
    std::vector<NestedInsertionValue116> values;
    unsigned short first, second;
    NeighborRecord20() {
        values.clear();
        first = 0;
        second = 0;
    }
};
struct ImplicitNeighborAlternative20 {
    std::vector<NestedInsertionValue116> values;
    unsigned short first, second;
};
struct ZeroMemberNeighborAlternative20 {
    std::vector<NestedInsertionValue116> values;
    unsigned short first, second;
    ZeroMemberNeighborAlternative20() : first(0), second(0) {}
};

void ObserveNeighborAllocationReset(NeighborAllocationOwner16& value) {
    value.resetAllocation();
}
void ObserveNeighborInitialization(NeighborRecord20* value) {
    new (value) NeighborRecord20;
}
void ObserveImplicitNeighborInitialization(ImplicitNeighborAlternative20* value) {
    new (value) ImplicitNeighborAlternative20;
}
void ObserveZeroMemberNeighborInitialization(ZeroMemberNeighborAlternative20* value) {
    new (value) ZeroMemberNeighborAlternative20;
}
std::vector<NestedInsertionValue116>::iterator ObserveNeighborSingleInsert(
    std::vector<NestedInsertionValue116>& values,
    std::vector<NestedInsertionValue116>::iterator position,
    const NestedInsertionValue116& value) {
    return values.insert(position, value);
}
void ObserveNeighborAssignment(std::vector<NestedInsertionValue116>& values,
                               unsigned count, const NestedInsertionValue116& value) {
    values.assign(count, value);
}

extern const unsigned long NeighborPolicyLayout[] = {
    sizeof(NeighborAllocation36), sizeof(NeighborAllocationOwner16),
    offsetof(NeighborAllocationOwner16, allocation),
    offsetof(NeighborAllocationOwner16, flags), sizeof(NeighborRecord20),
    offsetof(NeighborRecord20, first), offsetof(NeighborRecord20, second),
    sizeof(ImplicitNeighborAlternative20)
};
