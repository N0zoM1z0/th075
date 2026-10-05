// Complete original list controls; the carrier does not recover game element types.
#include <list>
struct ListPolicyValue16 { unsigned words[4]; };
void ObserveListConstruction() { std::list<ListPolicyValue16> values; }
void ObserveListPopFront(std::list<ListPolicyValue16>* values) { values->pop_front(); }
void ObserveListErase(std::list<ListPolicyValue16>* values,
                      std::list<ListPolicyValue16>::iterator position) {
    values->erase(position);
}
void ObserveListPushBack(std::list<ListPolicyValue16>* values,
                         const ListPolicyValue16& item) {
    values->push_back(item);
}
extern const unsigned long ListPolicyLayout[] = {
    sizeof(ListPolicyValue16), sizeof(std::list<ListPolicyValue16>),
    sizeof(std::list<ListPolicyValue16>::iterator),
    sizeof(std::list<ListPolicyValue16>::const_iterator)
};
