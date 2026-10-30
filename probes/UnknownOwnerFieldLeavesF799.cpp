// F799: two independently bounded unknown-origin original native leaf
// codegen observations, NOT accepted historical authored game source.
// The data before actual observed members and any later class members
// are UNKNOWN. These are borrowed source-compatible receiver views;
// never construct or embed either class as an asserted historical owner.
class NativeOwnerSetterF799 {
    unsigned char observedBefore1C[0x1C];
    int firstAt1C;
    int secondAt20;
    unsigned char modeAt24;
public:
    void Configure(unsigned char mode, int first, int second);
};

struct BorrowedStatusF799 {
    unsigned char observedBefore3C[0x3C];
    unsigned int flagsAt3C;
};

class NativeOwnerFlagF799 {
    unsigned char observedBefore74[0x74];
    BorrowedStatusF799* statusAt74;
public:
    bool HasActiveFlag();
};

// Physical original PE 004135F0: 40 complete CODE B, 16 native x86;
// 3 real formal parameters, RET 0Ch, zero original relocation fields.
void NativeOwnerSetterF799::Configure(unsigned char mode, int first, int second) {
    modeAt24 = mode;
    firstAt1C = first;
    secondAt20 = second;
}

// Physical original PE 00454F70: 31 complete CODE B, 15 native x86.
// Actual original boolean sequence after AND flags&20h is:
// XOR EAX,EAX / CMP EAX,EDX / SBB EAX,EAX / NEG EAX.
// A normal unsigned greater-than-zero predicate reproduces it.
// The equivalent !=0 or !! syntax DOES NOT emit the original x86.
bool NativeOwnerFlagF799::HasActiveFlag() {
    return 0 < (statusAt74->flagsAt3C & 0x20);
}
