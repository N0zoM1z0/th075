// F599: original PE-backed compiler-generation probe, not game source.
// A 116-byte observation reconstructed from the complete native field-copy
// instruction stream, not an assertion of original C++ names/types/ownership.
// The original 0x0045AAE0 assignment and 0x004591E0 EH copy constructor
// are compared in their entirety by verify-record116-implicit-copies-f599.py.
// Only genuine, semantically used fields; no asm or machine-byte patches.
#include <new>
struct FourWords {
    // Plain four-DWORD region at +0x44.
    unsigned a,b,c,d;
};
struct HeaderFourWords {
    // Nontrivial lifetime at +0, matching first constructor EH state.
    unsigned a,b,c,d;
    ~HeaderFourWords();
};
struct OwnedSixteen {
    // +0x54 and +0x64 have ordinary copy/assignment callees.
    unsigned a,b,c,d;
    OwnedSixteen(const OwnedSixteen&);
    ~OwnedSixteen();
    OwnedSixteen& operator=(const OwnedSixteen&);
};
struct Record116F599 {
    // Member names are provisional; sizes/offsets are native observations.
    HeaderFourWords header;
    short small10;
    unsigned count14;
    short small18,small1a,small1c,small1e,small20;
    short small22,small24,small26,small28,small2a;
    unsigned ptr2c,ptr30;
    short small34,small36;
    unsigned char flag38;
    unsigned ptr3c,ptr40;
    FourWords vector44;
    OwnedSixteen first54;
    OwnedSixteen second64;
};
void AssignmentWitness(Record116F599 &target, const Record116F599 &source) {
    target = source;
}
void ConstructionWitness(Record116F599 *target, const Record116F599 &source) {
    new (target) Record116F599(source);
}
// This is a compile-time extent guard, not an inert runtime field/pad.
typedef char Record116F599SizeGuard[(sizeof(Record116F599) == 116) ? 1 : -1];
