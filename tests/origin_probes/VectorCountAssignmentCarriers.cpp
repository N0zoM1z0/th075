// Original count-assignment and ordinary alternatives on complete generic values.
// The included payloads are observations, not recovered game declarations.
#include "VectorInsertionCarriers.cpp"

void ObserveAssignCleanup44(std::vector<InsertCleanup44>& values,
                            unsigned count, const InsertCleanup44& value) {
    values.assign(count, value);
}
void ObserveAssignOwned16(std::vector<InsertOwned16>& values,
                         unsigned count, const InsertOwned16& value) {
    values.assign(count, value);
}

template<class T> struct ManualCountAssignment : std::vector<T> {
    void assignValue(unsigned count, const T& value) {
        T temporary = value;
        this->erase(this->begin(), this->end());
        this->insert(this->begin(), count, temporary);
    }
};
void ObserveManualAssign44(ManualCountAssignment<InsertCleanup44>& values,
                           unsigned count, const InsertCleanup44& value) {
    values.assignValue(count, value);
}
void ObserveManualAssign16(ManualCountAssignment<InsertOwned16>& values,
                           unsigned count, const InsertOwned16& value) {
    values.assignValue(count, value);
}
void ObserveImplicitCopy44(InsertCleanup44& left, const InsertCleanup44& right) {
    left = right;
}
void ObserveImplicitCopy16(InsertOwned16& left, const InsertOwned16& right) {
    left = right;
}

extern const unsigned long VectorCountAssignmentLayout[] = {
    sizeof(InsertCleanup44), sizeof(InsertOwned16),
    sizeof(std::vector<InsertCleanup44>), sizeof(std::vector<InsertOwned16>),
    sizeof(ManualCountAssignment<InsertCleanup44>),
    sizeof(ManualCountAssignment<InsertOwned16>)
};
