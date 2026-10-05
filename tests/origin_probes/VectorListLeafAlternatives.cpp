// Generic source alternatives; no private game type or target mapping.
#include <vector>
#include <list>

struct LeafValue4 { unsigned long value; };
struct LeafValue16 { unsigned long values[4]; };

const LeafValue4& ObserveVectorLeaf4(const std::vector<LeafValue4>::const_iterator& p) { return *p; }
const LeafValue16& ObserveVectorLeaf16(const std::vector<LeafValue16>::const_iterator& p) { return *p; }
void* ObserveListNode4(const std::list<LeafValue4>::const_iterator& p) { return p._Mynode(); }
void* ObserveListNode16(const std::list<LeafValue16>::const_iterator& p) { return p._Mynode(); }

struct OrdinaryPointerLeaf {
    void* pointer;
    void* get() const { return pointer; }
};
struct OrdinaryReferenceLeaf {
    LeafValue4* pointer;
    const LeafValue4& get() const { return *pointer; }
};

void* ObserveOrdinaryPointerLeaf(const OrdinaryPointerLeaf& p) { return p.get(); }
const LeafValue4& ObserveOrdinaryReferenceLeaf(const OrdinaryReferenceLeaf& p) { return p.get(); }

extern const unsigned long VectorListLeafLayout[] = {
    sizeof(LeafValue4), sizeof(LeafValue16),
    sizeof(std::vector<LeafValue4>::const_iterator),
    sizeof(std::vector<LeafValue16>::const_iterator),
    sizeof(std::list<LeafValue4>::const_iterator),
    sizeof(std::list<LeafValue16>::const_iterator),
    sizeof(OrdinaryPointerLeaf), sizeof(OrdinaryReferenceLeaf)
};
