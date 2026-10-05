// Whole original public insertion carriers for independent generic alternatives.
// Payload sizes and source types are observations, not private target declarations.
#include <vector>

struct InsertValue4 { unsigned long value; };
struct InsertValue16 { unsigned long values[4]; };
struct InsertByte16 { unsigned char values[16]; };
struct InsertCleanup44 {
    unsigned long values[11];
    void dispose();
    ~InsertCleanup44() { dispose(); }
};
struct GenericAllocation { unsigned long value; };
struct InsertOwned16 {
    unsigned long identifier;
    unsigned long length;
    GenericAllocation* allocation;
    unsigned long flags;
    ~InsertOwned16() { if (allocation) delete allocation; }
};

struct DirectDeleteAlternative {
    unsigned long identifier;
    unsigned long length;
    GenericAllocation* allocation;
    unsigned long flags;
    ~DirectDeleteAlternative() { delete allocation; }
};

void ObserveDirectDelete(DirectDeleteAlternative& value) {
    value.~DirectDeleteAlternative();
}

void OrdinaryDestroyCleanup44(InsertCleanup44* value) { value->~InsertCleanup44(); }
void OrdinaryDestroyOwned16(InsertOwned16* value) { value->~InsertOwned16(); }
void OrdinaryDestroyTrivial(InsertValue16*) {}

void ObserveInsert4(std::vector<InsertValue4>& p, unsigned count, const InsertValue4& value) {
    p.insert(p.begin(), count, value);
}
void ObserveInsert16(std::vector<InsertValue16>& p, unsigned count, const InsertValue16& value) {
    p.insert(p.begin(), count, value);
}
void ObserveInsertBytes16(std::vector<InsertByte16>& p, unsigned count, const InsertByte16& value) {
    p.insert(p.begin(), count, value);
}
void ObserveInsertDword(std::vector<unsigned long>& p, unsigned count, const unsigned long& value) {
    p.insert(p.begin(), count, value);
}
void ObserveInsertPointer(std::vector<void*>& p, unsigned count, void* const& value) {
    p.insert(p.begin(), count, value);
}
std::vector<InsertValue16>::iterator ObserveInsertOne16(std::vector<InsertValue16>& p, const InsertValue16& value) {
    return p.insert(p.begin(), value);
}
void ObserveInsertCleanup44(std::vector<InsertCleanup44>& p, unsigned count, const InsertCleanup44& value) {
    p.insert(p.begin(), count, value);
}
void ObserveInsertOwned16(std::vector<InsertOwned16>& p, unsigned count, const InsertOwned16& value) {
    p.insert(p.begin(), count, value);
}

extern const unsigned long VectorInsertionLayout[] = {
    sizeof(InsertValue4), sizeof(InsertValue16), sizeof(InsertByte16),
    sizeof(unsigned long), sizeof(void*), sizeof(std::vector<InsertValue4>),
    sizeof(std::vector<InsertValue16>), sizeof(std::vector<void*>),
    sizeof(InsertCleanup44), sizeof(InsertOwned16)
};
