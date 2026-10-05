// Natural complete generic controls for explicit prefix recovery and forwarding.
// These declarations do not recover an original SDK class or game layout.
#include <new>

class StorageObservation {
public:
    StorageObservation() : references(1), length(0), storage(0) {}
    virtual ~StorageObservation() { ::operator delete(storage); }
    virtual long initialize(unsigned count) {
        storage = static_cast<unsigned char*>(::operator new(count));
        return storage ? 0 : static_cast<long>(0x8007000eUL);
    }
protected:
    unsigned references;
    unsigned length;
    unsigned char* storage;
};

class PrefixStorageObservation : public StorageObservation {
public:
    ~PrefixStorageObservation() {
        if (storage) storage -= storage[-1];
    }
    long initialize(unsigned count) {
        length = count;
        long result = StorageObservation::initialize(count + 16);
        if (result >= 0) {
            unsigned char delta = static_cast<unsigned char>(
                16 - (reinterpret_cast<unsigned long>(storage) & 15));
            storage += delta;
            storage[-1] = delta;
        }
        return result;
    }
};

class DefaultStorageObservation : public StorageObservation {};
class EmptyStorageObservation : public StorageObservation {
public:
    ~EmptyStorageObservation() {}
};

void ObservePrefixLifetime(PrefixStorageObservation& value) {
    value.PrefixStorageObservation::~PrefixStorageObservation();
}
void ObserveDefaultLifetime(DefaultStorageObservation& value) {
    value.DefaultStorageObservation::~DefaultStorageObservation();
}
void ObserveEmptyLifetime(EmptyStorageObservation& value) {
    value.EmptyStorageObservation::~EmptyStorageObservation();
}
long ObservePrefixAllocation(PrefixStorageObservation& value, unsigned count) {
    return value.PrefixStorageObservation::initialize(count);
}

extern const unsigned long AlignedStorageObservationLayout[] = {
    sizeof(StorageObservation), sizeof(PrefixStorageObservation),
    sizeof(DefaultStorageObservation), sizeof(EmptyStorageObservation),
    sizeof(unsigned char*), sizeof(unsigned)
};
