#include <vector>
#include <cstring>
#include <cstddef>

// Complete generic fixtures for source-policy discrimination only. These are
// not recovered private TH075 declarations and are never instantiated by game code.
struct InitializationAllocation { unsigned long value; };
struct InitializationValue16 { unsigned long value[4]; };

struct InitializationPrefix16 {
    unsigned long identifier, length;
    InitializationAllocation* allocation;
    unsigned char flags;
    InitializationPrefix16() {
        std::memset(this, 0, sizeof(*this));
        allocation = 0;
        flags = 1;
    }
    ~InitializationPrefix16() { if (allocation) delete allocation; }
};

struct InitializationRecord116 : InitializationPrefix16 {
    unsigned short word0;
    unsigned long scalar0;
    unsigned short word1, word2, word3, word4, word5;
    unsigned short word6, word7, word8, word9, word10;
    unsigned long scalar1, scalar2;
    unsigned short word11, word12;
    unsigned char flag;
    unsigned long scalar3, scalar4;
    InitializationValue16 second;
    std::vector<InitializationValue16> left, right;
    InitializationRecord116() {
        std::memset(this, 0, sizeof(*this));
        left.clear();
        right.clear();
        allocation = 0;
    }
};

struct ImplicitInitializationAlternative116 : InitializationPrefix16 {
    unsigned short word0;
    unsigned long scalar0;
    unsigned short word1, word2, word3, word4, word5;
    unsigned short word6, word7, word8, word9, word10;
    unsigned long scalar1, scalar2;
    unsigned short word11, word12;
    unsigned char flag;
    unsigned long scalar3, scalar4;
    InitializationValue16 second;
    std::vector<InitializationValue16> left, right;
};

struct ImplicitPrefixAlternative16 {
    unsigned long identifier, length;
    InitializationAllocation* allocation;
    unsigned char flags;
};

void ObserveExplicitInitialization(InitializationRecord116* value) {
    new (value) InitializationRecord116;
}
void ObserveImplicitInitialization(ImplicitInitializationAlternative116* value) {
    new (value) ImplicitInitializationAlternative116;
}
void ObserveValueInitialization(ImplicitPrefixAlternative16* value) {
    new (value) ImplicitPrefixAlternative16();
}
void ObserveExplicitPrefixInitialization(InitializationPrefix16* value) {
    new (value) InitializationPrefix16;
}

extern const unsigned long NestedInitializationLayout[] = {
    sizeof(InitializationPrefix16), offsetof(InitializationPrefix16, flags),
    sizeof(InitializationRecord116), offsetof(InitializationRecord116, word0),
    offsetof(InitializationRecord116, scalar0), offsetof(InitializationRecord116, second),
    offsetof(InitializationRecord116, left), offsetof(InitializationRecord116, right),
    sizeof(ImplicitInitializationAlternative116), sizeof(ImplicitPrefixAlternative16)
};
