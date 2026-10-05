// Original public iterators and complete generic intrusive-node alternatives.
// These observations do not declare or map private target nodes or payloads.
#include <list>
#include <stddef.h>

struct NodeValue4 { unsigned long value; };
struct NodeValue16 { unsigned long values[4]; };

const NodeValue4& ObserveListValue4(const std::list<NodeValue4>::const_iterator& p) { return *p; }
const NodeValue16& ObserveListValue16(const std::list<NodeValue16>::const_iterator& p) { return *p; }
void ObserveListNext4(std::list<NodeValue4>::const_iterator& p) { ++p; }
void ObserveListNext16(std::list<NodeValue16>::const_iterator& p) { ++p; }
void ObserveListPrevious4(std::list<NodeValue4>::const_iterator& p) { --p; }
void ObserveListPrevious16(std::list<NodeValue16>::const_iterator& p) { --p; }

template<class Value> struct IntrusiveNode {
    IntrusiveNode* next;
    IntrusiveNode* previous;
    Value value;
};
template<class Value> struct IntrusiveAccess {
    static IntrusiveNode<Value>*& next(IntrusiveNode<Value>* p) { return p->next; }
    static IntrusiveNode<Value>*& previous(IntrusiveNode<Value>* p) { return p->previous; }
    static Value& value(IntrusiveNode<Value>* p) { return p->value; }
};

IntrusiveNode<NodeValue4>*& ObserveOrdinaryNext4(IntrusiveNode<NodeValue4>* p) { return IntrusiveAccess<NodeValue4>::next(p); }
IntrusiveNode<NodeValue16>*& ObserveOrdinaryNext16(IntrusiveNode<NodeValue16>* p) { return IntrusiveAccess<NodeValue16>::next(p); }
IntrusiveNode<NodeValue4>*& ObserveOrdinaryPrevious4(IntrusiveNode<NodeValue4>* p) { return IntrusiveAccess<NodeValue4>::previous(p); }
IntrusiveNode<NodeValue16>*& ObserveOrdinaryPrevious16(IntrusiveNode<NodeValue16>* p) { return IntrusiveAccess<NodeValue16>::previous(p); }
NodeValue4& ObserveOrdinaryValue4(IntrusiveNode<NodeValue4>* p) { return IntrusiveAccess<NodeValue4>::value(p); }
NodeValue16& ObserveOrdinaryValue16(IntrusiveNode<NodeValue16>* p) { return IntrusiveAccess<NodeValue16>::value(p); }

extern const unsigned long ListNodeLinkLayout[] = {
    sizeof(NodeValue4), sizeof(NodeValue16),
    sizeof(std::list<NodeValue4>::const_iterator), sizeof(std::list<NodeValue16>::const_iterator),
    sizeof(IntrusiveNode<NodeValue4>), sizeof(IntrusiveNode<NodeValue16>),
    offsetof(IntrusiveNode<NodeValue4>, next), offsetof(IntrusiveNode<NodeValue4>, previous),
    offsetof(IntrusiveNode<NodeValue4>, value)
};
