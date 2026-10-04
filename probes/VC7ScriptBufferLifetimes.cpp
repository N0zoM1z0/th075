// Complete synthetic controls for observed fields, not a recovered game record or owner.
#include <memory>
#include <new>
#include <stddef.h>

template<class T> struct GuardedArrayRecord {
    unsigned char kind;
    short argument;
    T* buffer;
    GuardedArrayRecord() : buffer(0) {}
    ~GuardedArrayRecord() { if (buffer) delete[] buffer; }
};
struct UnguardedArrayRecord {
    unsigned char kind;
    short argument;
    char* buffer;
    UnguardedArrayRecord() : buffer(0) {}
    ~UnguardedArrayRecord() { delete[] buffer; }
};
struct ScalarRecord {
    unsigned char kind;
    short argument;
    char* buffer;
    ScalarRecord() : buffer(0) {}
    ~ScalarRecord() { if (buffer) delete buffer; }
};
struct RawImplicitRecord {
    unsigned char kind;
    short argument;
    char* buffer;
};
struct AutoImplicitRecord {
    unsigned char kind;
    short argument;
    std::auto_ptr<char> buffer;
};
struct ArrayOwner {
    char* buffer;
    ArrayOwner() : buffer(0) {}
    ~ArrayOwner() { if (buffer) delete[] buffer; }
};
struct OwnedImplicitRecord {
    unsigned char kind;
    short argument;
    ArrayOwner owner;
};
#define RECORD_CONTROLS(T, N) \
    typedef T Record##N; \
    Record##N* Construct##N(void* storage) { return new(storage) Record##N; } \
    void Destroy##N(Record##N* value) { value->~Record##N(); }
RECORD_CONTROLS(GuardedArrayRecord<char>, CharArray)
RECORD_CONTROLS(GuardedArrayRecord<unsigned char>, ByteArray)
RECORD_CONTROLS(GuardedArrayRecord<short>, WordArray)
RECORD_CONTROLS(GuardedArrayRecord<long>, DwordArray)
RECORD_CONTROLS(UnguardedArrayRecord, Unguarded)
RECORD_CONTROLS(ScalarRecord, Scalar)
RECORD_CONTROLS(RawImplicitRecord, Raw)
RECORD_CONTROLS(AutoImplicitRecord, Auto)
RECORD_CONTROLS(OwnedImplicitRecord, Owned)
extern "C" const unsigned long ScriptBufferLayout[] = {
    sizeof(RecordCharArray), offsetof(RecordCharArray, buffer),
    sizeof(RecordRaw), offsetof(RecordRaw, buffer),
    sizeof(RecordAuto), offsetof(RecordAuto, buffer), sizeof(std::auto_ptr<char>),
    sizeof(RecordOwned), offsetof(RecordOwned, owner), sizeof(ArrayOwner)
};
