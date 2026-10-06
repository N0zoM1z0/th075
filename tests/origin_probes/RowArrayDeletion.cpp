#include <new>
// Complete generic storage lifetime; no original SDK private type is declared.
struct RowStorageObservation {
    void* storage;
    unsigned count;
    unsigned capacity;
    RowStorageObservation() : storage(0),count(0),capacity(0) {}
    ~RowStorageObservation() { ::operator delete(storage); }
};
RowStorageObservation* CreateRows(unsigned count) {
    return new RowStorageObservation[count];
}
void DeleteRows(RowStorageObservation* rows) { delete [] rows; }
void DeleteRow(RowStorageObservation* row) { delete row; }
extern const unsigned RowStorageObservationSizes[] = {
    sizeof(RowStorageObservation),sizeof(void*)
};
