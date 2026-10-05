// Complete generic source fixtures for nested insertion and lifetime alternatives.
// Observed scalar widths and composition are not original private declarations.
#include "VectorInsertionCarriers.cpp"

struct NestedInsertionValue116 {
    InsertOwned16 first;
    unsigned short word0;
    unsigned long scalar0;
    unsigned short word1;
    unsigned short word2;
    unsigned short word3;
    unsigned short word4;
    unsigned short word5;
    unsigned short word6;
    unsigned short word7;
    unsigned short word8;
    unsigned short word9;
    unsigned short word10;
    unsigned long scalar1;
    unsigned long scalar2;
    unsigned short word11;
    unsigned short word12;
    unsigned char flag;
    unsigned long scalar3;
    unsigned long scalar4;
    InsertValue16 second;
    std::vector<InsertValue16> left;
    std::vector<InsertValue16> right;
    ~NestedInsertionValue116() { left.clear(); right.clear(); }
};

struct ImplicitNestedAlternative116 {
    InsertOwned16 first;
    unsigned short word0;
    unsigned long scalar0;
    unsigned short word1;
    unsigned short word2;
    unsigned short word3;
    unsigned short word4;
    unsigned short word5;
    unsigned short word6;
    unsigned short word7;
    unsigned short word8;
    unsigned short word9;
    unsigned short word10;
    unsigned long scalar1;
    unsigned long scalar2;
    unsigned short word11;
    unsigned short word12;
    unsigned char flag;
    unsigned long scalar3;
    unsigned long scalar4;
    InsertValue16 second;
    std::vector<InsertValue16> left;
    std::vector<InsertValue16> right;
};

void ObserveImplicitNestedDestroy(ImplicitNestedAlternative116& value) {
    value.~ImplicitNestedAlternative116();
}

void ObserveNestedInsert(std::vector<NestedInsertionValue116>& values,
                         unsigned count, const NestedInsertionValue116& value) {
    values.insert(values.begin(), count, value);
}

extern const unsigned long NestedInsertionLayout[] = {
    sizeof(NestedInsertionValue116),
    offsetof(NestedInsertionValue116, word0),
    offsetof(NestedInsertionValue116, scalar0),
    offsetof(NestedInsertionValue116, second),
    offsetof(NestedInsertionValue116, left),
    offsetof(NestedInsertionValue116, right)
};
